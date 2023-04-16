//
// Created by adril on 13/04/2023.
//

#ifndef AOS_FILESYSTEMS_FAT_H
#define AOS_FILESYSTEMS_FAT_H
#include <stdbool.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "FAT_INFO.h"

#define SYS_NAME_STR "System Name: %s\n"
#define SEC_SIZE_STR "Sector Size: %d\n"
#define SEC_PER_CLUS_STR "Sectors Per Cluster: %d\n"
#define RES_SEC_STR "Reserved Sectors: %d\n"
#define NUM_FAT_STR "# of FATs: %d\n"
#define ROOT_ENT_STR "Root Entries: %d\n"
#define SEC_PER_FAT_STR "Sectors Per FAT: %d\n"
#define LABEL_STR "Label: %s\n"

typedef struct {
    char name[BS_OEMNAME_SIZE];
    int sectorSize;
    int sectorsPerCluster;
    char reservedSectors;
    char numFat;
    int rootEntries;
    int sectorsPerFat;
    char label[BS_VOLLAB_SIZE];
} FatInfo;
bool isFat(int fd);
char* getFatType(int fd);
void showFatInfo(int fd);

void getFatTree(int fd);
#endif //AOS_FILESYSTEMS_FAT_H
