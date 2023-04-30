GCC = gcc -march=native

all: main

run: main
	clear
	./fsutils --info lolext



check_leaks: main
	valgrind  --leak-check=full --show-leak-kinds=all --track-origins=yes -s --track-fds=yes --show-reachable=yes ./fsutils --cat lolext popstars


main: main.c ext fat fsys printer
	$(GCC) main.c -o  fsutils -lpthread -lm -Wextra -Wall EXT.o FAT.o FileSystem.o printer.o

ext: EXT.c EXT.h
	$(GCC) -c EXT.c -o EXT.o -Wextra -Wall
fat: FAT.c FAT.h
	$(GCC) -c FAT.c -o FAT.o -Wextra -Wall
fsys: FileSystem.c FileSystem.h fat ext
	$(GCC) -c FileSystem.c -o FileSystem.o -Wextra -Wall
printer: printer.c printer.h
	$(GCC) -c printer.c -o printer.o -Wextra -Wall
clean:
	rm -fr fsutils *.o
