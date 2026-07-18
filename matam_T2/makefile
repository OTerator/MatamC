prog:	main.o misc.o Song.o SongLibrary.o
	gcc -Wall -Werror -g -std=c99 -o prog main.o misc.o Song.o SongLibrary.o

main.o: main.c	Song.h SongLibrary.h
	gcc -Wall -Werror -g -std=c99 -c main.c

misc.o: misc.c misc.h
	gcc -Wall -Werror -g -std=c99 -c misc.c

Song.o: Song.c	misc.h Song.h
	gcc -Wall -Werror -g -std=c99 -c Song.c

SongLibrary.o:	SongLibrary.c misc.h SongLibrary.h
	gcc -Wall -Werror -g -std=c99 -c SongLibrary.c
