#include <stdio.h>
#include <string.h>
#include "FAT.h"
#include "FileSystem.h"
#include "EXT.h"


int main(int argc, char** argv) {
    if (argc != 3){
        printf("not enough arguments");
        return 1;
    }


    for (int i = 0; i < argc; i++) {
        //printf("\nargv[%d] = %s", i, argv[i]);
        if (strcmp(argv[i],"--info") == 0 && i+1 <= argc){
            int fd = openFS(argv[i+1]);
            if (fd < 0) {
                return 1;
            }

            if (isFat(fd)){
                getFatInfo(fd);
            } else if (isExt(fd)){
                getExtInfo(fd);
            } else {
                printf("Unknown");
                return 1;
            }
        } else if (strcmp(argv[i],"--tree") == 0 && i+1 <= argc){
            int fd = openFS(argv[i+1]);
            if (fd < 0) {
                return 1;
            }

            getFSTree(fd);
        }
    }
    return 0;
}
