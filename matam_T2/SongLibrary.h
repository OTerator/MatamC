#ifndef SONGLIBRARY_H
#define SONGLIBRARY_H
#include "Song.h"

typedef struct SongLibrary* SongLibrary;

/* Goes over the files in library_dir, creates a Song object for each one, keeps all
   Songs in an array inside the SongLibrary object. Returns the object */
SongLibrary SongLibraryCreate(const char* library_dir, const char* performer);

/* Destructor for SongLibrary */
void SongLibraryDestroy(SongLibrary sl);

/* Returns a dynamically allocated string with the song performer */
const char* SongPerformer(SongLibrary sl);

/* Returns the number of songs in the library */
unsigned int SongLibraryNumSongs(SongLibrary sl);

/* Returns song in index i. i must be between 0 to SongLibraryNumSongs(sl)-1. 
   Returns NULL for illegal index */
Song SongLibraryGetSongByIndex(SongLibrary sl, unsigned int i);

/* Returns song by name. Returns NULL if song does not exist */
Song SongLibraryGetSongByName(SongLibrary sl, const char* song_name);

#endif