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


bool isExt(int fd);
#endif //AOS_FILESYSTEMS_EXT_H
