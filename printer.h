//
// Created by adril on 27/04/2023.
//

#ifndef AOS_FILESYSTEMS_PRINTER_H
#define AOS_FILESYSTEMS_PRINTER_H
#include <stdio.h>

#define COLOR_RED 0
#define COLOR_GREEN 1
#define COLOR_PINK 2

#define BOLD    "\033[1m"
#define BOLDGREEN "\033[1m\033[32m"
#define BOLDRED   "\033[1m\033[31m"
#define BOLDMAGENTA "\e[1;35m"
#define RESET     "\033[0m"
void printFileorDir(char* name, int level, int isDir);

void printc(char *message, int color);

#endif //AOS_FILESYSTEMS_PRINTER_H
