//
// Created by adril on 13/04/2023.
//

#ifndef AOS_FILESYSTEMS_FAT_H
#define AOS_FILESYSTEMS_FAT_H
#include <stdbool.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "FAT_INFO.h"
#include "printer.h"

#define SYS_NAME_STR "System Name: %s\n"
#define SEC_SIZE_STR "Sector Size: %d\n"
#define SEC_PER_CLUS_STR "Sectors Per Cluster: %d\n"
#define RES_SEC_STR "Reserved Sectors: %d\n"
#define NUM_FAT_STR "# of FATs: %d\n"
#define ROOT_ENT_STR "Root Entries: %d\n"
#define SEC_PER_FAT_STR "Sectors Per FAT: %d\n"
#define LABEL_STR "Label: %s\n"

typedef struct {
    char name[BS_OEMNAME_SIZE+1];
    uint16_t sectorSize;
    char sectorsPerCluster;
    uint16_t reservedSectors;
    char numFat;
    uint16_t rootEntries;
    uint32_t sectorsPerFat;
    char label[BS_VOLLAB_SIZE+1];
} FatInfo;

typedef struct {
    char shortName[FAT_DIR_NAME_SIZE];
    char attributes;
    char creationTimeTenth;
    uint32_t creationTime;
    uint32_t creationDate;
    uint32_t lastAccessDate;
    uint32_t firstClusterHigh;
    uint32_t lastWriteTime;
    uint32_t lastWriteDate;
    uint16_t firstClusterLow;
    uint32_t fileSize;
} DirInfo;

bool isFat(int fd);
char* getFatType(int fd);
void showFatInfo(int fd);

void getFatTree(int fd);
void getFatFileContents(int fd, char* fileName);
#endif //AOS_FILESYSTEMS_FAT_H
