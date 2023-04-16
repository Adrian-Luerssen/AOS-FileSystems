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

void getFatTree(int fd){
    printf("%d - not implemented yet", fd);
}
