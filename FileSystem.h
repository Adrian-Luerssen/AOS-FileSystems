//
// Created by adril on 13/04/2023.
//

#ifndef AOS_FILESYSTEMS_FILESYSTEM_H
#define AOS_FILESYSTEMS_FILESYSTEM_H
#include "EXT.h"
#include "FAT.h"
#define FS_HEADER "----- Filesystem Information -----\n\n"


int openFS(const char *path);
void getFatInfo(int fd);
void getExtInfo(int fd);
void getFSTree(int fd);
void catFile(int fd, char* file);
#endif //AOS_FILESYSTEMS_FILESYSTEM_H
