GCC = gcc -march=native

all: main

run: main
	clear
	./fsutils --info lolext



check_leaks: main
	valgrind  --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes -s --track-fds=yes --show-reachable=yes ./fsutils --info lolext


main: main.c ext fat fsys
	$(GCC) main.c -o  fsutils -lpthread -lm -Wextra -Wall EXT.o FAT.o FileSystem.o

ext: EXT.c EXT.h
	$(GCC) -c EXT.c -o EXT.o -Wextra -Wall
fat: FAT.c FAT.h
	$(GCC) -c FAT.c -o FAT.o -Wextra -Wall
fsys: FileSystem.c FileSystem.h
	$(GCC) -c FileSystem.c -o FileSystem.o -Wextra -Wall
clean:
	rm -fr fsutils *.o
