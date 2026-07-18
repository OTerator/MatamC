#include "Song.h"
#include "SongLibrary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char* argv[]) {
    if(argc < 4) {
        fprintf(stderr, "\nUsage: %s <prog> <songs-dir> <performer> [OPTIONS]\n\n", argv[0]);
        return 8;
    }

    SongLibrary sl = SongLibraryCreate(argv[2], argv[3]);

    if(!strcmp(argv[1], "wc")) {
        if(argc != 5 && argc != 6) {
            fprintf(stderr, "\nUsage: %s wc <songs-dir> <performer> {-n <song-name>|-i <song-index>|-a}\n\n", argv[0]);
            SongLibraryDestroy(sl);
            return 8;
        }
        Song s = NULL;
        if(!strcmp(argv[4], "-n")) {
            s = SongLibraryGetSongByName(sl, argv[5]);
        } else if(!strcmp(argv[4], "-i")) {
            s = SongLibraryGetSongByIndex(sl, atoi(argv[5]));
        } else if(!strcmp(argv[4], "-a")) {
            for(unsigned int i=0; i<SongLibraryNumSongs(sl); i++)
                SongWC(SongLibraryGetSongByIndex(sl, i), stdout);
            SongLibraryDestroy(sl);
            return 0;
        }
        else {
            fprintf(stderr, "\nUsage: %s wc <songs-dir> <performer> {-n <song-name>|-i <song-index>|-a}\n\n", argv[0]);
            SongLibraryDestroy(sl);
            return 8;
        }
        if(s) {
            SongWC(s, stdout);
        } else {
            printf("Song not found\n");
        }

    }
    else if(!strcmp(argv[1], "lyrics")) {
        if(argc != 5 && argc != 6) {
            fprintf(stderr, "\nUsage: %s lyrics <songs-dir> <performer> {-n <song-name>|-i <song-index>}\n\n", argv[0]);
            SongLibraryDestroy(sl);
            return 8;
        }

        Song s = NULL;
        if(!strcmp(argv[4], "-n")) {
            s = SongLibraryGetSongByName(sl, argv[5]);
        } else if(!strcmp(argv[4], "-i")) {
            s = SongLibraryGetSongByIndex(sl, atoi(argv[5]));
        } else {
            fprintf(stderr, "\nUsage: %s lyrics <songs-dir> <performer> {-n <song-name>|-i <song-index>}\n\n", argv[0]);
            SongLibraryDestroy(sl);
            return 8;
        }

        if(s) {
            char* song_name = SongName(s);
            char* song_lyrics = SongLyrics(s);

            printf("%s\n%s\n", song_name, song_lyrics);

            free(song_name);
            free(song_lyrics);
        }
        else {
            printf("Song not found\n");
        }
    }
    else if(!strcmp(argv[1], "num")) {
        if(argc != 4) {
            fprintf(stderr, "\nUsage: %s num <songs-dir> <performer>\n\n", argv[0]);
            SongLibraryDestroy(sl);
            return 8;
        }
        printf("%u songs\n", SongLibraryNumSongs(sl));
    }

    SongLibraryDestroy(sl);

    return 0;
}
#ifdef KUKU
/***********************************************************************************************************************
 * Do not use functions from string.h
 **********************************************************************************************************************/
char* create_path(const char* dir, const char* file) {
    char* path = NULL;
    int len_dir, len_file, i;

    for(len_dir=0; dir[len_dir] != '\0'; len_dir++)
        ;
    for(len_file=0; file[len_file] != '\0'; len_file++)
        ;
    path = malloc(len_dir + len_file + 2);
    if(path == NULL) {
        fprintf(stderr, "Failed to allocate %d bytes in create_path\n\n", len_dir + len_file + 2);
        exit(1);
    }

    for(i=0; i<len_dir; i++) {
        path[i] = dir[i];
    }
    path[i] = '/';
    for(i=0; i<len_file; i++) {
        path[i+len_dir+1] = file[i];
    }
    path[i+len_dir+1] = '\0';

    return path;
}

/***********************************************************************************************************************
 * First line contains the name of the song and ends with \n
 * If cannot open file - return NULL
 * Do not use functions from string.h
 **********************************************************************************************************************/
char* get_song_name(const char* file_path) {
    char *buf = NULL;
    size_t bufsize = 0;
    FILE* fp = fopen(file_path, "r");

    if(fp == NULL) {
        return NULL;
    }
    // Ignore the first two lines
    getline(&buf, &bufsize, fp);
    fclose(fp);
    strip(buf);

    return buf;
}

/***********************************************************************************************************************
 * If memory allocation fails - report and exit
 * Remember that each line ends with \n - need to remove it from the file name
 **********************************************************************************************************************/
unsigned int get_all_song_names(const char* root_dir, char*** song_names) {
    unsigned int song_names_size = 0;
    const char* file_paths = create_path(root_dir, "filenames.txt");
    const char* curr_file = NULL;
    char* buf = NULL;
    size_t bufsize = 0;

    FILE* fp = fopen(file_paths, "r");

    if(fp == NULL) {
        fprintf(stderr, "Failed to open file %s\n\n", file_paths);
        exit(-1);
    }

    while(getline(&buf, &bufsize, fp) > 0) {
        strip(buf);
        curr_file = create_path(root_dir, buf);
        *song_names = (char**) realloc(*song_names, (++song_names_size)*sizeof(char*));
        if(*song_names == NULL) {
            fprintf(stderr, "Error: failed to allocate %d char*\n", song_names_size);
            exit(1);
        }
        (*song_names)[song_names_size-1] = get_song_name(curr_file);
        free(curr_file);
    }
    free(buf);
    return song_names_size;
 }

/***********************************************************************************************************************
* If memory allocation fails - report and exit
* Remember that each line ends with \n - need to remove it from the file name
**********************************************************************************************************************/
int main(int argc, const char* argv[]) {
    if(argc != 3) {
        printf("\nUsage: %s <beatles-directory> <output-file>\n", argv[0]);
        return 1;
    }

    const char* dir_path = argv[1];
    const char* out_path = argv[2];
    const char* song_paths = create_path(dir_path, "filenames.txt");
    char** song_names = NULL;
    unsigned int num_songs = get_all_song_names(dir_path, &song_names);
    if(num_songs == 0) {
        fprintf(stderr, "Error: read 0 songs\n\n");
        return 1;
    }
    FILE *fp = fopen(song_paths, "r"), *fout;
    char* buf = NULL;
    size_t bufsize = 0;
    int i = 0;

    fout = fopen(out_path, "w   ");
    if(!fout) {
        fprintf(stderr, "Failed to write to %s\n", out_path);
        return 1;
    }

    while(getline(&buf, &bufsize, fp) > 0) {
        strip(buf);
        unsigned int nlines, nwords, nchars;
        const char* curr_file = create_path(dir_path, buf);
        if(!wc(curr_file, &nlines, &nwords, &nchars)) {
            printf("Fatal error: failed to treat file %s\n\n", buf);
            free(buf);
            for(i=0; i<num_songs; i++)
                free(song_names[i]);
            free(song_names);
            free(curr_file);
            fclose(fp);
            fclose(fout);
            return 1;
        }
        fprintf(fout, "%u\t%u\t%u\t%s\n", nlines, nwords, nchars, song_names[i]);
        i++;
        free(curr_file);
    }

    free(buf);
    for(i=0; i<num_songs; i++)
        free(song_names[i]);

    free(song_names);
    fclose(fp);
    fclose(fout);

    return 0;
}
#endif