//
// Created by adril on 13/04/2023.
//

#include "EXT.h"

bool isExt(int fd) {
    // ext2_xattr_header
    // first 4 bytes =  EXT2_XATTR_MAGIC = 0xEA020000
    lseek(fd, EXT2_S_MAGIC_OFFSET_TRUE, SEEK_SET);
    int val;
    read(fd, &val, EXT2_S_MAGIC_SIZE);
    return val == EXT2_SUPER_MAGIC;
}

InodeInfo getInodeInfo(int fd) {
    InodeInfo inodeInfo;

    lseek(fd, EXT2_S_INODES_COUNT_OFFSET_TRUE, SEEK_SET);
    read(fd, &inodeInfo.count, EXT2_S_INODES_COUNT_SIZE);

    lseek(fd, EXT2_S_FREE_INODES_COUNT_OFFSET_TRUE, SEEK_SET);
    read(fd, &inodeInfo.free, EXT2_S_INODES_COUNT_SIZE);

    lseek(fd, EXT2_S_INODES_PER_GROUP_OFFSET_TRUE, SEEK_SET);
    read(fd, &inodeInfo.group, EXT2_S_INODES_PER_GROUP_SIZE);

    lseek(fd, EXT2_S_FIRST_INO_OFFSET_TRUE, SEEK_SET);
    read(fd, &inodeInfo.first, EXT2_S_FIRST_INO_SIZE);

    lseek(fd, EXT2_S_INODE_SIZE_OFFSET_TRUE, SEEK_SET);
    read(fd, &inodeInfo.size, EXT2_S_INODE_SIZE_SIZE);

    return inodeInfo;
}

void showInodeInfo(int fd) {
    InodeInfo inodeInfo = getInodeInfo(fd);
    printf(INODE_HEADER);
    printf(INODE_SIZE_STR, inodeInfo.size);
    printf(INODE_NUM_STR, inodeInfo.count);
    printf(INODE_FIRST_STR, inodeInfo.first);
    printf(INODE_GROUP_STR, inodeInfo.group);
    printf(INODE_FREE_STR, inodeInfo.free);
}

BlockInfo getBlockInfo(int fd) {
    BlockInfo blockInfo;
    int val;
    lseek(fd, EXT2_S_LOG_BLOCK_SIZE_OFFSET_TRUE, SEEK_SET);
    read(fd, &val, EXT2_S_LOG_BLOCK_SIZE_SIZE);
    blockInfo.size = 1024 << val;

    lseek(fd, EXT2_S_BLOCKS_COUNT_OFFSET_TRUE, SEEK_SET);
    read(fd, &blockInfo.total, EXT2_S_BLOCKS_COUNT_SIZE);

    lseek(fd, EXT2_S_FREE_BLOCKS_COUNT_OFFSET_TRUE, SEEK_SET);
    read(fd, &blockInfo.free, EXT2_S_FREE_BLOCKS_COUNT_SIZE);

    lseek(fd, EXT2_S_BLOCKS_PER_GROUP_OFFSET_TRUE, SEEK_SET);
    read(fd, &blockInfo.group, EXT2_S_BLOCKS_PER_GROUP_SIZE);

    lseek(fd, EXT2_S_R_BLOCKS_COUNT_OFFSET_TRUE, SEEK_SET);
    read(fd, &blockInfo.reserved, EXT2_S_R_BLOCKS_COUNT_SIZE);

    lseek(fd, EXT2_S_FRAGS_PER_GROUP_OFFSET_TRUE, SEEK_SET);
    read(fd, &blockInfo.frags, EXT2_S_FRAGS_PER_GROUP_SIZE);

    lseek(fd, EXT2_S_FIRST_DATA_BLOCK_OFFSET_TRUE, SEEK_SET);
    read(fd, &blockInfo.first, EXT2_S_FIRST_DATA_BLOCK_SIZE);

    return blockInfo;
}

void showBlockInfo(int fd) {
    BlockInfo blockInfo = getBlockInfo(fd);
    printf(BLOCK_HEADER);
    printf(BLOCK_SIZE_STR, blockInfo.size);
    printf(BLOCK_RES_STR, blockInfo.reserved);
    printf(BLOCK_FREE_STR, blockInfo.free);
    printf(BLOCK_TOTAL_STR, blockInfo.total);
    printf(BLOCK_FIRST_STR, blockInfo.first);
    printf(BLOCK_GROUP_STR, blockInfo.group);
    printf(BLOCK_FRAG_STR, blockInfo.frags);
}

VolumeInfo getVolumeInfo(int fd) {
    VolumeInfo volumeInfo;
    lseek(fd, EXT2_S_VOLUME_NAME_OFFSET_TRUE, SEEK_SET);
    read(fd, &volumeInfo.name, EXT2_S_VOLUME_NAME_SIZE);

    lseek(fd, EXT2_S_MTIME_OFFSET_TRUE, SEEK_SET);
    read(fd, &volumeInfo.lastMounted, EXT2_S_MTIME_SIZE);

    lseek(fd, EXT2_S_WTIME_OFFSET_TRUE, SEEK_SET);
    read(fd, &volumeInfo.lastWritten, EXT2_S_WTIME_SIZE);

    lseek(fd, EXT2_S_LAST_CHECK_TIME_OFFSET_TRUE, SEEK_SET);
    read(fd, &volumeInfo.lastChecked, EXT2_S_LAST_CHECK_TIME_SIZE);

    return volumeInfo;
}

char *getPOSIXTime(time_t time) {
    char *posixTime;
    posixTime = malloc(100);
    strftime(posixTime, 100, TIME_FORMAT, localtime(&time));
    return posixTime;
}

void showVolumeInfo(int fd) {
    VolumeInfo volumeInfo = getVolumeInfo(fd);
    printf(VOLUME_HEADER);
    printf(VOLUME_NAME_STR, volumeInfo.name);
    printf(VOLUME_CHECKED_STR, getPOSIXTime(volumeInfo.lastChecked));
    printf(VOLUME_MOUNTED_STR, getPOSIXTime(volumeInfo.lastMounted));
    printf(VOLUME_WRITTEN_STR, getPOSIXTime(volumeInfo.lastWritten));
}


InodeTable getInodeTable(int fd, void *inode_in) {
    int inode = (inode_in == NULL) ? EXT2_ROOT_INO : *(int *) inode_in;
    BlockInfo blocks = getBlockInfo(fd);
    InodeInfo inodes = getInodeInfo(fd);
    /*
     * Directories are stored as data block and referenced by an inode.
     * They can be identified by the file type EXT2_S_IFDIR stored in the i_mode field
     * of the inode structure.
     *
     * The second entry of the Inode table contains the inode pointing to the data of the root directory;
     * as defined by the EXT2_ROOT_INO constant.
     */
    // (1024 + (blockSize *4)) : the Inode table starts on the 5th block

    /*
     * block group = (inode - 1) / s_inodes_per_group
     * Once the block is identified, the local inode index for the local inode table can be identified using:
     * local inode index = (inode - 1) % s_inodes_per_group
     *
     */
    unsigned int pos;
    lseek(fd, EXT2_BG_INODE_TABLE_OFFSET_TRUE, SEEK_SET);
    read(fd, &pos, EXT2_BG_INODE_TABLE_SIZE);

    long blockGroup = (inode - 1) / inodes.group;
    long localInodeIndex = (inode - 1) % inodes.group;

    long inodeTablePos =
            (pos * blocks.size) + (localInodeIndex * inodes.size) + (blockGroup * blocks.size * blocks.group);
    InodeTable inodeTable;
    lseek(fd, inodeTablePos + EXT2_I_SIZE_OFFSET, SEEK_SET);
    read(fd, &inodeTable.length, EXT2_I_SIZE_SIZE);

    lseek(fd, inodeTablePos + EXT2_I_BLOCKS_OFFSET, SEEK_SET);
    read(fd, &inodeTable.num_blocks, EXT2_I_BLOCKS_SIZE);

    lseek(fd, inodeTablePos + EXT2_I_BLOCK_OFFSET, SEEK_SET);
    read(fd, &inodeTable.blocks, EXT2_I_BLOCK_SIZE * EXT2_N_BLOCKS);

    //printf("inodeTablePos: %ld\n", inodeTablePos);
    //printf("calc = (%d * %d) + (%ld * %d) + (%ld * %d * %d)", pos, blocks.size, localInodeIndex, inodes.size, blockGroup, blocks.size, blocks.group);
    return inodeTable;
}

void printExtTree(ExtTree *extTree) {
    //printf("%d", (*extTree).name_len);
    printf("%s", (*extTree).name);
}

ExtTree getDirInfo(int fd, long pos, int *offset) {
    ExtTree extTree;

    lseek(fd, pos + (*offset), SEEK_SET);
    //printf("read pos: %ld\n", pos + (*offset));

    read(fd, &extTree.inode, EXT2_DIR_INODE_SIZE);

    read(fd, &extTree.rec_len, EXT2_DIR_REC_LEN_SIZE);

    read(fd, &extTree.name_len, EXT2_DIR_NAME_LEN_SIZE);

    read(fd, &extTree.file_type, EXT2_DIR_FILE_TYPE_SIZE);

    read(fd, &extTree.name, extTree.name_len);

    extTree.name[(int) extTree.name_len] = '\0';

    /*printf("inode: %d\n", extTree.inode);
    printf("rec_len: %d\n", extTree.rec_len);
    printf("name_len: %d\n", extTree.name_len);
    printf("file_type: %d\n", extTree.file_type);
    printf("name: %s\n", extTree.name);*/
    (*offset) += extTree.rec_len;
    return extTree;
}

int isDir(ExtTree child) {
    return child.file_type == EXT2_FT_DIR && strcmp(child.name, "..") != 0 &&
           strcmp(child.name, ".") != 0 && strlen(child.name) > 0;
}
int isFile(ExtTree child) {
    return child.file_type == EXT2_FT_REG_FILE && strlen(child.name) > 0;
}

void printFileorDir(char* name, int level, int isDir){
    // Print the path tree
    if (isDir){
        for (int i = 0; i < level; i++) {
            printf("|   "); // Indentation for each level with lines
        }
        printf("\n");
    }

    for (int i = 0; i < level-1; i++) {
        printf("|   "); // Indentation for each level with lines
    }
    printf("|---%s\n", name); // Print the current path with lines
}


void buildExtTree(int fd, int inode, char *path, int level) {

    int offset = 0;
    InodeTable inodeTable = getInodeTable(fd, &inode);
    ExtTree extTreeChild;
    extTreeChild.file_type = -1;


    if (level != 0) printFileorDir(path, level,1);

    for (int block = 0; block < EXT2_N_BLOCKS && offset < inodeTable.length; block++) {
        //printf("\nBlock %d\n", i);
        if (inodeTable.blocks[block] != 0) {
            while (offset < inodeTable.length && extTreeChild.file_type != 0) {
                //printf("\t\tOffset %d > %d\n", offset, inodeTable.length);
                extTreeChild = getDirInfo(fd, inodeTable.blocks[block] * getBlockInfo(fd).size, &offset);

                if (isDir(extTreeChild)) buildExtTree(fd, extTreeChild.inode, extTreeChild.name, level + 1);


                if (isFile(extTreeChild)) printFileorDir(extTreeChild.name, level+1, 0);

            }
        }
    }


}

void getExtTree(int fd) {
    buildExtTree(fd, EXT2_ROOT_INO, "/", 0);
}