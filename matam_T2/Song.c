/*
    This modules encapsulates a song info. Information is retrieved from files that must be in this format:
   Line 1: song name
   Line 2: empty
   Line 3-end: song lyrics  
*/
#include "Song.h"
#include "misc.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>



//   *********   //

struct Song {
    // SongName() and SongLyrics return char*, therefore I've decided the most sensible thing would be to store both the same way:
   char* sName;
   char* sLyrics;   
   unsigned int lines;
   unsigned int words;
   unsigned int chars;
};

//   *********   //


/* Song constructor */
Song SongCreate(const char* song_path) {
    
    FILE *song_file = fopen(song_path, "r");
    if (!song_file) {
        fprintf(stderr, "Error in %s: failed to open file %s for reading, aborting\n", __func__, song_path);
        exit(1);
    }
    
    //  Instantiating a new song:
    //   *********   //

    Song new_song = (Song)malloc(sizeof(struct Song));
    // if (!new_song) {
    //     fprintf(stderr, "Error in %s: failed to allocate %lu bytes, aborting\n", __func__, sizeof(struct Song));
    //     exit(3);
    // }
    alloc_tester(new_song, sizeof(struct Song), __func__);

    new_song->sName = NULL;
    new_song->sLyrics = NULL; 
    new_song->lines = 0;
    new_song->words = 0;
    new_song->chars = 0;

    //   *********   //


    char* buffer = NULL;    //  
    size_t buffer_size = 0;
    

    //  1. First Line:
    size_t first_size = my_getline(&buffer, &buffer_size, song_file);    /* updated buffer and its size, first_size < buffer_size always. */
    // if (firstline == (size_t)(-1)) {
    //     fprintf(stderr, "Error in %s: file %s is corrupted\n", __func__, song_path);
    //     exit(6);
    // } // casting -1 to unsigned (size_t) by the 2's complement method therefore it'll be: 1111111...1 (base 2)
    getline_tester(first_size, song_path, __func__);
    
    if (first_size > 0 && buffer[first_size - 1] == '\n') {    //   for a non empty first line, we replace '\n' with '\0' for a clean string 
        buffer[first_size - 1] = '\0';     //  example: "Here Comes The Sun\n" → "Here Comes The Sun" .
    }
    
    if (!buffer) {  // we want to strdup buffer for sName, but without checking if NULL here instead of inside the strdup, we can't tell if the rturned NULL is because of failed memory alloc or NULL pointer given....
        fprintf(stderr, "Error in %s: NULL pointer found, aborting\n", __func__);
        exit(4);
    }
    new_song->sName = strdup(buffer);
    alloc_tester(new_song->sName, first_size, __func__);  //   no need for strlen() here because the firstline always replaces '\n' with '/0' in our format.


    //  2. Empty Line:
    size_t second_size = my_getline(&buffer, &buffer_size, song_file);
    getline_tester(second_size, song_path, __func__);

    for (int i = 0; buffer[i] !='\0'; i++) {    //  iterate through the string in this line
        if (!isspace(buffer[i])) {  //  check if we found a char that doesn't belong to this set of non-characters: {'\n', '\t', ' ', ...}
            fprintf(stderr, "Error in %s: file %s is corrupted\n", __func__, song_path);
            exit(6);    //  in that case, the second line in our txt is not empty..
        }
    }


    //  3. Lyrics:
    size_t alloc_bytes = 256; //  assuming the shortest of song lyrics will still be more than 128 chars, בחירה שרירותית
    new_song->sLyrics = (char*)malloc(alloc_bytes * sizeof(char));
    alloc_tester(new_song->sLyrics, alloc_bytes * sizeof(char), __func__);

    size_t line_size = 0;
    while ((line_size = my_getline(&buffer, &buffer_size, song_file)) != -1) {    // until EOF returning -1.
        new_song->lines++;      //  another line
        
        int c = 1;     // char tracer for words:
        for (int j = 0; j < line_size; j++) {   //  iterating through the line, excluding '/0' (no +1)
            //if (!isalnum(buffer[j]) && !isgraph(buffer[j])) {  
            //   two words will be seperated by a non-AlphaNumeric char likes spaces or dots ↓ (I've found that one tricky song with dots)
            //   we count aba...cde as 2 words, dots are seperators just like spaces.

            // above method has been abandoned, transitioning to isspace checking. chaged initialization of c from c=0 to c=1 to count the first word.
            if (!isspace(buffer[j])) {
                c = 0;
            } else {
                c++;    //  char is alpha-numeric, therefore is a part of a word.
            }
            
            if (c == 1) {   // alpha-numeric char is the start of a new word. (aba, 1aba, aba1, 123, 12ab12, ...)
                new_song->words++;
            }
        }   // end of a line
        
        if (new_song->chars + line_size + 1 > alloc_bytes) {    // str length + length of our about-to-be-added line + '\0' , must not occupy more memory than alloacted
            while (new_song->chars + line_size + 1 > alloc_bytes) {
                alloc_bytes *= 2;   //  Multiply by 2 rule-of-thumb for realloc
            }
            char* temp = (char*)realloc(new_song->sLyrics, alloc_bytes * sizeof(char));
            alloc_tester(temp, alloc_bytes * sizeof(char), __func__);
            new_song->sLyrics = temp;
        }
        
        // append everything from the buffer into nLyrics:
        strcpy(new_song->sLyrics +  new_song->chars ,buffer);   // pointer arithmetic: move the amount of chars we've counted, and copying into the resulting address: 
        // therefore sLyrics[chars] = '\0' of our previous line (+ 0 for the first time).
        // that way we overwrite the previous '\0' and concatenate our string to the current sLyrics. (for the record it took a hot minute to figure this and include string.h)


        new_song->chars += line_size;    //  size of char is 1 byte so this is a neat 1 to 1 mapping between size and chars per line. (getline doesn't count '\0')
    }


    //  buffer may go rest now, it is our responsibility to free the hard working guy
    if (buffer != NULL) {
        free(buffer);
    }

    //  at last, it is "the rising of a new sun"
    fclose(song_file);
    return new_song;

}


/* Song destructor. Does nothing if song is NULL */
void SongDestroy(Song song) {
    if (!song) {
        return;
    }
    
    if ((song->sName) != NULL) {
        free(song->sName);
    }
    if ((song->sLyrics) != NULL) {
        free(song->sLyrics);
    }

    free(song);
}


/* Returns a dynamically allocated string with the song name, without \n in the end */
char* SongName(Song song) {
    if (!song) {
        fprintf(stderr, "Error in %s: NULL pointer found, aborting\n", __func__);
        exit(4);
    }

    char* copy = strdup(song->sName);   //   ↓ for '\0' !
    alloc_tester(copy, strlen(song->sName) + 1, __func__);
    return copy;
}


/* Returns a dynamically allocated string with the song lyrics. Read the lyrics line by line.
 * Include the \n in the file to separate lines */
char* SongLyrics(Song song) {
    if (!song) {
        fprintf(stderr, "Error in %s: NULL pointer found, aborting\n", __func__);
        exit(4);
    }

    char* copy = strdup(song->sLyrics);
    alloc_tester(copy, strlen(song->sLyrics) + 1, __func__);
    return copy;
}


/* Print to fout the information about the song's number of lines, words and characters in the format 
   <song-name>\t<number-of-lines>\t<number-of-words>\t<number-of-characters>\n */
void SongWC(Song song, FILE* fout) {
    if (!song || !fout) {
        fprintf(stderr, "Error in %s: NULL pointer found, aborting\n", __func__);
        exit(4);
    }

    fprintf(fout, "%s\t%u\t%u\t%u\n", song->sName, song->lines, song->words, song->chars);
}
