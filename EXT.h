//
// Created by adril on 13/04/2023.
//

#ifndef AOS_FILESYSTEMS_EXT_H
#define AOS_FILESYSTEMS_EXT_H
#include <stdbool.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "EXT_INFO.h"

#define INODE_HEADER    "INODE INFO\n"
#define INODE_SIZE_STR  "\tSize: %d\n"
#define INODE_NUM_STR   "\tNum Inodes: %d\n"
#define INODE_FIRST_STR "\tFirst Inode: %d\n"
#define INODE_GROUP_STR "\tInodes Group: %d\n"
#define INODE_FREE_STR  "\tFree Inodes: %d\n"

#define BLOCK_HEADER    "INFO BLOCK\n"
#define BLOCK_SIZE_STR  "\tBlock Size: %d\n"
#define BLOCK_RES_STR   "\tReserved Blocks: %d\n"
#define BLOCK_FREE_STR  "\tFree Blocks: %d\n"
#define BLOCK_TOTAL_STR "\tTotal Blocks: %d\n"
#define BLOCK_FIRST_STR "\tFirst Block: %d\n"
#define BLOCK_GROUP_STR "\tGroup Blocks: %d\n"
#define BLOCK_FLAG_STR  "\tGroup Flags: %d\n"

#define VOLUME_HEADER   "INFO VOLUME\n"
#define VOLUME_NAME_STR "\tVolume Name: %s\n"
#define VOLUME_LAST_CHECKED_STR "\tLast Checked: %s %s %d %d:%d:%d %d\n"
#define VOLUME_MOUNTED_STR "\tLast Mounted: %s %s %d %d:%d:%d %d\n"
#define VOLUME_WRITTEN_STR "\tLast Written: %s %s %d %d:%d:%d %d\n"

typedef struct{
    int count;
    int size;
    int first;
    int group;
    int free;
} InodeInfo;

typedef struct{
    int size;
    int reserved;
    int free;
    int total;
    int first;
    int group;
} BlockInfo;

typedef struct{
    char name[16];
    int lastChecked;
    int lastMounted;
    int lastWritten;
} VolumeInfo;

bool isExt(int fd);
void showInodeInfo(int fd);
void showBlockInfo(int fd);
void showVolumeInfo(int fd);
#endif //AOS_FILESYSTEMS_EXT_H
