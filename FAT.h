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
#include "FAT_INFO.h"
bool isFat(int fd);

#endif //AOS_FILESYSTEMS_FAT_H
