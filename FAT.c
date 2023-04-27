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

FatInfo getFatFSInfo(int fd){
    FatInfo fatInfo;

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
DirInfo getFatDirInfo(int fd, int dirOffset){
    lseek(fd, dirOffset, SEEK_SET);
    DirInfo dirInfo;
    read(fd, &dirInfo, sizeof(DirInfo));
    if (dirInfo.attributes == 0x10){
        printf("%s\tDIRECTORY\n", dirInfo.shortName);
    }
    return dirInfo;
}

DirInfo readFatDirInfo(int fd, int dirOffset){
    DirInfo dirInfo;
    lseek(fd, dirOffset+FAT_DIR_NAME_OFFSET, SEEK_SET);
    read(fd, &dirInfo.shortName, FAT_DIR_NAME_SIZE);

    lseek(fd, dirOffset+FAT_DIR_ATTR_OFFSET, SEEK_SET);
    read(fd, &dirInfo.attributes, FAT_DIR_ATTR_SIZE);
    return dirInfo;
}



void getFatTreeRecursive(int startSector, int level, int fd,char* path){
    int rootEntries;
    lseek(fd, BPB_ROOTENTCNT_OFFSET, SEEK_SET);
    read(fd, &rootEntries, BPB_ROOTENTCNT_SIZE);
    if (level != 0) printFileorDir(path, level,1);
    for (int i = 0; i < rootEntries; i++){
        DirInfo dirInfo = readFatDirInfo(fd, startSector + i*64);
        if (dirInfo.shortName[0] == 0x00 ){
            break;
        }
        if (dirInfo.attributes == 0x0F || strcmp(dirInfo.shortName, ".") == 0 || strcmp(dirInfo.shortName, "..") == 0 || dirInfo.attributes == 0x08){
            continue;
        }

        int isDir = dirInfo.attributes == 0x10;
        printFileorDir(dirInfo.shortName, level, isDir);

    }
}

void getFatTree(int fd){

    //RootDirSectors = ((BPB_RootEntCnt * 32) + (BPB_BytsPerSec – 1)) / BPB_BytsPerSec;
    //FirstDataSector = BPB_ResvdSecCnt + (BPB_NumFATs * FATSz) + RootDirSectors;
    //FirstSectorofCluster = ((N – 2) * BPB_SecPerClus) + FirstDataSector;

    FatInfo fatInfo = getFatFSInfo(fd);

    //FirstRootDirSecNum = BPB_ResvdSecCnt + (BPB_NumFATs * BPB_FATSz16);
    int rootDirSector = (fatInfo.reservedSectors + (fatInfo.numFat * fatInfo.sectorsPerFat))*fatInfo.sectorSize;

    getFatTreeRecursive(rootDirSector, 0, fd,"root");

}
