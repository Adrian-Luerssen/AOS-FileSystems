//
// Created by adril on 13/04/2023.
//

#include "EXT.h"
bool isExt(int fd) {
    // ext2_xattr_header
    // first 4 bytes =  EXT2_XATTR_MAGIC = 0xEA020000
    lseek(fd, EXT2_S_MAGIC_OFFSET_TRUE, SEEK_SET);
    int val;
    read(fd, &val, EXT2_S_MAGIC_SIZE);
    return val == EXT2_SUPER_MAGIC;
}