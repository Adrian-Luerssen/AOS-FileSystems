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
InodeInfo getInodeInfo(int fd){
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

void showInodeInfo(int fd){
    InodeInfo inodeInfo = getInodeInfo(fd);
    printf(INODE_HEADER);
    printf(INODE_SIZE_STR, inodeInfo.size);
    printf(INODE_NUM_STR, inodeInfo.count);
    printf(INODE_FIRST_STR, inodeInfo.first);
    printf(INODE_GROUP_STR, inodeInfo.group);
    printf(INODE_FREE_STR, inodeInfo.free);
}

BlockInfo getBlockInfo(int fd){
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

void showBlockInfo(int fd){
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

/*VolumeInfo getVolumeInfo (int fd) {

}
void showVOLUMEInfo(int fd) {

}*/