//
// Created by adril on 27/04/2023.
//

#include "printer.h"
void printFileorDir(char* name, int level, int isDir){
    // Print the path tree
    if (isDir){
        for (int i = 0; i < level; i++) {
            printf("|   "); // Indentation for each level with lines
        }
        printf("\n");
    }

    for (int i = 0; i < level-1; i++) {
        printf("|   "); // Indentation for each level with lines
    }
    printf("|---%s\n", name); // Print the current path with lines
}