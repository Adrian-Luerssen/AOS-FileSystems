//
// Created by adril on 13/04/2023.
//

#include "FAT.h"

bool isFat(int fd){
    lseek(fd, BS_FILSYSTYPE_OFFSET, SEEK_SET);
    char buffer[BS_FILSYSTYPE_SIZE];
    read(fd, buffer, BS_FILSYSTYPE_SIZE);
    return strcmp(buffer, FAT12_TYPE_STRING) == 0 || strcmp(buffer, FAT16_TYPE_STRING) == 0 || strcmp(buffer, FAT_TYPE_STRING) == 0;
}

char* getFatType(int fd){
    lseek(fd, BS_FILSYSTYPE_OFFSET, SEEK_SET);
    char buffer[BS_FILSYSTYPE_SIZE];
    read(fd, buffer, BS_FILSYSTYPE_SIZE);
    // TODO: if not one of the three types, check the FAT32 type
    if (strcmp(buffer, FAT12_TYPE_STRING) == 0){
        return FAT12_TYPE_STRING;
    } else if (strcmp(buffer, FAT16_TYPE_STRING) == 0){
        return FAT16_TYPE_STRING;
    } else if (strcmp(buffer, FAT_TYPE_STRING) == 0){
        return FAT_TYPE_STRING;
    }else {
        return FAT32_TYPE_STRING;
    }

}
void initFatInfo(FatInfo* fatinfo){
    strcpy(fatinfo->name, "");
    strcpy(fatinfo->label, "");
    fatinfo->sectorSize = 0;
    fatinfo->sectorsPerCluster = 0;
    fatinfo->reservedSectors = 0;
    fatinfo->numFat = 0;
    fatinfo->rootEntries = 0;
    fatinfo->sectorsPerFat = 0;
}
FatInfo getFatFSInfo(int fd){
    FatInfo fatInfo;
    initFatInfo(&fatInfo);
    lseek(fd, BS_OEMNAME_OFFSET, SEEK_SET);
    read(fd, fatInfo.name, BS_OEMNAME_SIZE);

    lseek(fd, BPB_BYTSPERSEC_OFFSET, SEEK_SET);
    read(fd, &fatInfo.sectorSize, BPB_BYTSPERSEC_SIZE);

    lseek(fd, BPB_SECPERCLUS_OFFSET, SEEK_SET);
    read(fd, &fatInfo.sectorsPerCluster, BPB_SECPERCLUS_SIZE);

    lseek(fd, BPB_RSVDSECCNT_OFFSET, SEEK_SET);
    read(fd, &fatInfo.reservedSectors, BPB_RSVDSECCNT_SIZE);

    lseek(fd, BPB_NUMFATS_OFFSET, SEEK_SET);
    read(fd, &fatInfo.numFat, BPB_NUMFATS_SIZE);

    lseek(fd, BPB_ROOTENTCNT_OFFSET, SEEK_SET);
    read(fd, &fatInfo.rootEntries, BPB_ROOTENTCNT_SIZE);

    lseek(fd, BPB_FATSZ16_OFFSET, SEEK_SET);
    read(fd, &fatInfo.sectorsPerFat, BPB_FATSZ16_SIZE);

    lseek(fd, BS_VOLLAB_OFFSET, SEEK_SET);
    read(fd, fatInfo.label, BS_VOLLAB_SIZE);
    if (fatInfo.sectorsPerFat == 0){
        lseek(fd, FAT32_BPB_FATSZ32_OFFSET, SEEK_SET);
        read(fd, &fatInfo.sectorsPerFat, FAT32_BPB_FATSZ32_SIZE);
        lseek(fd, FAT32_BS_VOLLAB_OFFSET, SEEK_SET);
        read(fd, fatInfo.label, FAT32_BS_VOLLAB_SIZE);
    }
    fatInfo.label[BS_VOLLAB_SIZE] = '\0';
    fatInfo.name[BS_OEMNAME_SIZE] = '\0';

    return fatInfo;
}

void showFatInfo(int fd){
    FatInfo fatInfo = getFatFSInfo(fd);
    printf(SYS_NAME_STR, fatInfo.name);
    printf(SEC_SIZE_STR, fatInfo.sectorSize);
    printf(SEC_PER_CLUS_STR, fatInfo.sectorsPerCluster);
    printf(RES_SEC_STR, fatInfo.reservedSectors);
    printf(NUM_FAT_STR, fatInfo.numFat);
    printf(ROOT_ENT_STR, fatInfo.rootEntries);
    printf(SEC_PER_FAT_STR, fatInfo.sectorsPerFat);
    printf(LABEL_STR, fatInfo.label);

}


DirInfo readFatDirInfo(int fd, int dirOffset){
    DirInfo dirInfo;
    lseek(fd, dirOffset+FAT_DIR_NAME_OFFSET, SEEK_SET);
    read(fd, &dirInfo.shortName, FAT_DIR_NAME_SIZE);

    lseek(fd, dirOffset+FAT_DIR_ATTR_OFFSET, SEEK_SET);
    read(fd, &dirInfo.attributes, FAT_DIR_ATTR_SIZE);

    lseek(fd, dirOffset+FAT_DIR_FSTCLUSHI_OFFSET, SEEK_SET);
    read(fd, &dirInfo.firstClusterHigh, FAT_DIR_FSTCLUSHI_SIZE);

    lseek(fd, dirOffset+FAT_DIR_FSTCLUSLO_OFFSET, SEEK_SET);
    read(fd, &dirInfo.firstClusterLow, FAT_DIR_FSTCLUSLO_SIZE);

    lseek(fd, dirOffset+FAT_DIR_FILESIZE_OFFSET, SEEK_SET);
    read(fd, &dirInfo.fileSize, FAT_DIR_FILESIZE_SIZE);
    return dirInfo;
}

char* fat_to_normal(char* fat_name,int isDir){
    int i, j = 0;
    char normal_name[13];

    // Copy first part of name (8 characters)
    for (i = 0; i < 8 && fat_name[i] != ' ' && fat_name[i] != '\n' && fat_name[i] != '\0'; i++) {
        normal_name[j++] = fat_name[i];
    }

    // Skip over unused characters
    while (i < 8) {
        i++;
    }

    // Copy extension (3 characters)
    if (!isDir){
        if (fat_name[8] != ' ') {
            normal_name[j++] = '.';
            for (i = 8; i < 11 && fat_name[i] != ' '; i++) {
                normal_name[j++] = fat_name[i];
            }
        }
    }


    // Null-terminate the string
    normal_name[j] = '\0';

    // Return the normal name
    return strdup(normal_name);
}

void getFatTreeRecursive(int startSector, int level, int fd,char* path,int rootDirSector){
    unsigned short rootEntries;
    lseek(fd, BPB_ROOTENTCNT_OFFSET, SEEK_SET);
    read(fd, &rootEntries, BPB_ROOTENTCNT_SIZE);
    if (level != 0) printFileorDir(path, level,1);

    for (int i = 0; i < rootEntries; i++){
        //printf("i: %d level %d\n", i,level);
        DirInfo dirInfo = readFatDirInfo(fd, startSector + i*32);


        //printf("dirInfo.shortName: %s + %d + %x - %x\n", dirInfo.shortName, dirInfo.attributes==0x10, dirInfo.attributes, dirInfo.shortName[0]);
        //printf("name: '%s' exit if '%s' or '%s'\n", dirInfo.shortName,".", "..");
        if (dirInfo.shortName[0] == 0x00 || dirInfo.shortName[0] ==(char)0xE5){
            break;
        }
        int isDir = dirInfo.attributes == 0x10;

        char* new = fat_to_normal(dirInfo.shortName, isDir);
        //
        if (dirInfo.attributes == 0x0F || strlen(new) == 0 ||strcmp(new, ".") == 0 || strcmp(new, "..") == 0 || dirInfo.attributes == 0x08){
            free(new);
            continue;
        }


        if (!isDir) {
            printFileorDir(new, level+1, isDir);
            free(new);
        }
        else {
            FatInfo fatInfo = getFatFSInfo(fd);
            //FirstRootDirSecNum = BPB_ResvdSecCnt + (BPB_NumFATs * BPB_FATSz16);
            int index = ((dirInfo.firstClusterLow-2)*fatInfo.sectorsPerCluster)*fatInfo.sectorSize + rootDirSector + rootEntries*32;

            /*printf("firstClusterLow: %d\n", dirInfo.firstClusterLow);
            //printf("fullCluster: %h\n", (dirInfo.firstClusterLow* fatInfo.reservedSectors * fatInfo.sectorSize + startSector));
            printf("rootDirSector: %d\n", rootDirSector);
            printf("startSector: %d\n", startSector);
            // print calculation
            printf("((%d * %d) + %d) * %d + %d + %d\n", dirInfo.firstClusterLow, fatInfo.sectorsPerCluster, fatInfo.reservedSectors, fatInfo.sectorSize, startSector, rootDirSector);
            //break;*/
            //printf("index: %x\n", index);
            getFatTreeRecursive(index, level+1, fd,new,rootDirSector);
            free(new);
            //printf("\nback\n");
        }

    }
}

void getFatTree(int fd){

    //RootDirSectors = ((BPB_RootEntCnt * 32) + (BPB_BytsPerSec – 1)) / BPB_BytsPerSec;
    //FirstDataSector = BPB_ResvdSecCnt + (BPB_NumFATs * FATSz) + RootDirSectors;
    //FirstSectorofCluster = ((N – 2) * BPB_SecPerClus) + FirstDataSector;

    FatInfo fatInfo = getFatFSInfo(fd);

    //FirstRootDirSecNum = BPB_ResvdSecCnt + (BPB_NumFATs * BPB_FATSz16);
    int rootDirSector = (fatInfo.reservedSectors + (fatInfo.numFat * fatInfo.sectorsPerFat))*fatInfo.sectorSize;

    getFatTreeRecursive(rootDirSector, 0, fd,"root",rootDirSector);

}
void printFatFileContents(DirInfo dirInfo, int fd,int rootDirSector,int rootEntries){
    FatInfo fatInfo = getFatFSInfo(fd);
    int startSector = ((dirInfo.firstClusterLow-2)*fatInfo.sectorsPerCluster)*fatInfo.sectorSize + rootDirSector + rootEntries*32;
    int size = dirInfo.fileSize;
    //printf("size: %d\n", size);
    //printf("startSector: %d\n", startSector);
    char buffer;
    int bytesRead = 0;
    lseek(fd, startSector, SEEK_SET);
    while (bytesRead < size){
        read(fd, &buffer, 1);
        printf("%c", buffer);
        //printf("\n%d read %d remaining", bytesRead, size - bytesRead);
        bytesRead++;
    }
}

int searchFatRecursive(int startSector, int fd,int rootDirSector, char* pathToFind){
    unsigned short rootEntries;
    lseek(fd, BPB_ROOTENTCNT_OFFSET, SEEK_SET);
    read(fd, &rootEntries, BPB_ROOTENTCNT_SIZE);

    for (int i = 0; i < rootEntries; i++){
        DirInfo dirInfo = readFatDirInfo(fd, startSector + i*32);
        if (dirInfo.shortName[0] == 0x00 || dirInfo.shortName[0] ==(char)0xE5){
            break;
        }
        int isDir = dirInfo.attributes == 0x10;
        char* new = fat_to_normal(dirInfo.shortName, isDir);
        //
        if (dirInfo.attributes == 0x0F || strlen(new) == 0 ||strcmp(new, ".") == 0 || strcmp(new, "..") == 0 || dirInfo.attributes == 0x08){
            free(new);
            continue;
        }


        if (!isDir && strncasecmp(new, pathToFind, (strlen(pathToFind)>strlen(new))?strlen(pathToFind):strlen(new)) == 0) {
            printFatFileContents(dirInfo,fd,rootDirSector,rootEntries);
            free(new);
            return 1;
        }
        free(new);
        if (isDir) {
            FatInfo fatInfo = getFatFSInfo(fd);
            int index = ((dirInfo.firstClusterLow-2)*fatInfo.sectorsPerCluster)*fatInfo.sectorSize + rootDirSector + rootEntries*32;

            int a = searchFatRecursive(index, fd,rootDirSector,pathToFind);
            if (a == 1){
                return 1;
            }
        }

    }
    return 0;
}


void getFatFileContents(int fd, char* filename){
    FatInfo fatInfo = getFatFSInfo(fd);

    //FirstRootDirSecNum = BPB_ResvdSecCnt + (BPB_NumFATs * BPB_FATSz16);
    int rootDirSector = (fatInfo.reservedSectors + (fatInfo.numFat * fatInfo.sectorsPerFat))*fatInfo.sectorSize;

    if(!searchFatRecursive(rootDirSector, fd,rootDirSector,filename)){
        printf("File not found\n");
    }
}