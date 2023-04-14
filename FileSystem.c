//
// Created by adril on 13/04/2023.
//

#include "FileSystem.h"
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int openFS(const char *path) {
    int fd = open(path, O_RDONLY);
    if (fd < 0) {
        printf("Error opening file");
        return -1;
    }
    //char buffer[1];
    //int rd = read(fd, buffer, 1);
    /*while(rd > 0){
        printf("%c", buffer[0]);
        rd = read(fd, buffer, 1);
    }*/
    return fd;
}

void getFatInfo(int fd){
    printf(FS_HEADER);
    printf("File System: %s\n",getFatType(fd));
}

void getExtInfo(int fd){
    printf(FS_HEADER);
    printf("File System: %s\n\n","EXT2");
    showInodeInfo(fd);
    showBlockInfo(fd);
    //showVolumeInfo(fd);
}