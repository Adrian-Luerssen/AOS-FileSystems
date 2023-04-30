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
    char name[BS_OEMNAME_SIZE];
    unsigned short sectorSize;
    char sectorsPerCluster;
    unsigned short reservedSectors;
    char numFat;
    unsigned short rootEntries;
    unsigned short sectorsPerFat;
    char label[BS_VOLLAB_SIZE];
} FatInfo;

typedef struct {
    char shortName[FAT_DIR_NAME_SIZE];
    char attributes;
    char creationTimeTenth;
    int creationTime;
    int creationDate;
    int lastAccessDate;
    int firstClusterHigh;
    int lastWriteTime;
    int lastWriteDate;
    unsigned short firstClusterLow;
    int fileSize;
} DirInfo;

bool isFat(int fd);
char* getFatType(int fd);
void showFatInfo(int fd);

void getFatTree(int fd);
void getFatFileContents(int fd, char* fileName);
#endif //AOS_FILESYSTEMS_FAT_H
