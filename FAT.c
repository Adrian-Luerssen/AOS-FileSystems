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