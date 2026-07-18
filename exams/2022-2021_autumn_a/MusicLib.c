#include "MusicLib.h"
#include "Set.h"	// has <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct MusicLib {
	Set songs;
	char* (*get_song_name)(const char*);
	char* (*get_song_lyrics)(const char*);
};


Element name_cpy(Element e) {
	return (Element) strdup((const char*) e);
}

// strcmp returns int 0 for equals, the Set module requires bool so we narrow the method result from ternary to binary.
bool name_cmp(Element e1, Element e2) {
	return !strcmp((const char*) e1, (const char*) e2);
}


MusicLib MLCreate(char* (*get_song_name)(const char*), char* (*get_song_lyrics)(const char*)) {
	
	MusicLib ml = (MusicLib)malloc(sizeof(struct MusicLib));
	
	ml->songs = SetCreate(name_cpy, free, name_cmp);
	ml->get_song_name = get_song_name;
	ml->get_song_lyrics = get_song_lyrics;
	
	return ml;
}


//void		MLPrintLyrics(MusicLib ml, const char* filename) {
//	if (!ml || !filename) return;
//	
//	const char* name = ml->get_song_name(filename);
//	if (SetFind(ml->songs, name) == NULL) return;
//	free(name);
//	
//	char* lyrics = ml->get_song_lyrics(filename);
//	
//	printf("%s\n", lyrics);
//}


void PrintFix(MusicLib ml, const char* song) {
	if (!ml || !filename) return;
	
	Element songf;
	for (songf = SetFirst(ml->songs); songf; songf = SetNext(ml->songs)) {
		
		const char* current = ml->get_song_name((const char*) songf);
		
		if (!strcmp(song, current)) {
			const char* lyrics = (const char*)ml->get_song_lyrics(current);
			printf("%s\n", lyrics);
			free(lyrics);
			free(current);
			return;
		}
		free(current);
	}
	
}
