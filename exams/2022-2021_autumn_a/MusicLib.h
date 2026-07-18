#ifndef MUSICLIB_H
#define MUSICLIB_H
#include <stdlib.h>

typedef struct MusicLib* MusicLib;

MusicLib	MLCreate(char* (*get_song_name)(const char*), char* (*get_song_lyrics)(const char*));
void		MLDestroy(MusicLib ml);
void		MLAdd(MusicLib ml, const char* filename);
void 		MLRemove(MusicLib ml, const char* filename);
void		MLPrintLyrics(MusicLib ml, const char* filename);
void 		MLPrintSongNames(MusicLib ml);

#endif