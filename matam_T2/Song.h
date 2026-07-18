#ifndef SONG_H
#define SONG_H
/*
    This modules encapsulates a song info. Information is retrieved from files that must be in this format:
   Line 1: song name
   Line 2: empty
   Line 3-end: song lyrics  
*/
#include <stdio.h>

typedef struct Song* Song;

/* Song constructor */
Song SongCreate(const char* song_path);

/* Song destructor. Does nothing if song is NULL */
void SongDestroy(Song song);

/* Returns a dynamically allocated string with the song name, without \n in the end */
char* SongName(Song song);

/* Returns a dynamically allocated string with the song lyrics. Read the lyrics line by line. Include the \n in the file to separate lines */
char* SongLyrics(Song song);

/* Print to fout the information about the song's number of lines, words and characters in the format 
   <song-name>\t<number-of-lines>\t<number-of-words>\t<number-of-characters>\n */
void SongWC(Song song, FILE* fout);

#endif