GCC = gcc -march=native

all: main

run: main
	clear
	./fsutils --info lolext


check_leaks: main
	valgrind  --leak-check=full --show-leak-kinds=all --track-origins=yes -s --track-fds=yes --show-reachable=yes ./fsutils --tree libfat


main: main.c ext fat fsys printer
	$(GCC) main.c -o  fsutils -lpthread -lm -Wextra -Wall out/EXT.o out/FAT.o out/FileSystem.o out/printer.o

ext: EXT.c EXT.h
	$(GCC) -c EXT.c -o out/EXT.o -Wextra -Wall
fat: FAT.c FAT.h
	$(GCC) -c FAT.c -o out/FAT.o -Wextra -Wall
fsys: FileSystem.c FileSystem.h fat ext
	$(GCC) -c FileSystem.c -o out/FileSystem.o -Wextra -Wall
printer: printer.c printer.h
	$(GCC) -c printer.c -o out/printer.o -Wextra -Wall
clean:
	rm -fr fsutils out/*.o *.o
