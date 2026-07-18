#include "SongLibrary.h"
#include "misc.h"
#include <stdlib.h>
#include <string.h>


//   *********   //

struct SongLibrary {
   Song* songArr;
   unsigned int count;
   char* performer;
};

//   *********   //


/* Goes over the files in library_dir, creates a Song object for each one, keeps all
   Songs in an array inside the SongLibrary object. Returns the object */
SongLibrary SongLibraryCreate(const char* library_dir, const char* performer) {

   if (!library_dir || !performer) {
      fprintf(stderr, "Error in %s: NULL pointer found, aborting\n", __func__);
      exit(4);
   }

   //  Instantiating a new song library:
   //   *********   //
   
   SongLibrary new_lib = malloc(sizeof(struct SongLibrary));
   alloc_tester(new_lib, sizeof(struct SongLibrary), __func__);

   new_lib->songArr = NULL;
   new_lib->performer = strdup(performer);
   alloc_tester(new_lib->performer, strlen(performer) * sizeof(char*) + 1, __func__);

   char** songtxt_arr = NULL;
   /* Takes a path of a directory and a pointer to {an array of strings → songtxt_arr} (which is assumed to be NULL when passed → indeed is).
   * Fills files with the complete paths of all the files in {dir_path → library_dir} that end with .txt. Returns the size of {files → new_lib->count : also the amount of songs that we've accumulated}.
   * Generates the proper error messages and exits with the proper error code if an error occurs  */
   new_lib->count = glob_txt_files(library_dir, &songtxt_arr);

   if (!songtxt_arr) {
      fprintf(stderr, "Error in %s: NULL pointer found, aborting\n", __func__);
      exit(4);
   }
   if (new_lib->count == 0) {    // safety check in case songtxt_arr is not NULL and count is somehow 0.
      fprintf(stderr, "Error in %s: given directory is has no <.txt> files, no song library is instantiated, aborting\n", __func__);   // we don't want songArr to be NULL or malloc(0) to occur.
      exit(9);
   }

   //   *********   //

   new_lib->songArr = (Song*)malloc(new_lib->count * sizeof(Song));
   alloc_tester(new_lib->songArr, new_lib->count, __func__);

   for (unsigned int i = 0; i < new_lib->count; i++) {
      new_lib->songArr[i] = SongCreate(songtxt_arr[i]);  //    if calculated correctly, both arrays should be of the same length.
      free(songtxt_arr[i]);   // free char* (string of txt file name) at index i, we don't need it anymore.
   }
   
   // may go to rest
   free(songtxt_arr);

   // (finally)
   return new_lib;
}

/* Destructor for SongLibrary */
void SongLibraryDestroy(SongLibrary sl) {
   if (!sl) {
      fprintf(stderr, "Error in %s: NULL pointer found, aborting\n",__func__);
      exit(4);
   }

   if (sl->songArr != NULL) {
      for(unsigned int i = 0; i<sl->count; i++) {
         SongDestroy(sl->songArr[i]);
      }
      free(sl->songArr);
   }

   if (sl->performer != NULL) {
      free(sl->performer);
   }

   free(sl);
}


/* Returns a dynamically allocated string with the song performer */
const char* SongPerformer(SongLibrary sl) {
   if (!sl || !sl->performer) {
      fprintf(stderr, "Error in %s: NULL pointer found, aborting\n",__func__);
      exit(4);
   }

   return strdup(sl->performer);   // I've found that if our return value is "const char*" it is essentially redudant to strdup(), but considering it is clearly requested as 
}                                  // a dynamically allocated string, I will assume it should be "char*" returning a deep-copy, which is up to the user to free... (if possible with const?)


/* Returns the number of songs in the library */
unsigned int SongLibraryNumSongs(SongLibrary sl) {
   if (!sl) {
      fprintf(stderr, "Error in %s: NULL pointer found, aborting\n",__func__);
      exit(4);    // "NULL pointer received when otherwise expected" though, if not for this clear specification in the pdf, I think I'd choose to return 0 instead of shutting down
                  // considering the program could continue operating just fine and alongside returning 0 print a report to the user that this library is nonexistant to differentiate from empty librarys.
   }

   return sl->count;
}


/* Returns song in index i. i must be between 0 to SongLibraryNumSongs(sl)-1. 
   Returns NULL for illegal index */
Song SongLibraryGetSongByIndex(SongLibrary sl, unsigned int i) {
   
   if (!sl) {
      fprintf(stderr, "Error in %s: NULL pointer found, aborting\n",__func__);
      exit(4);
   }
   if (i >= sl->count) {   // index must be lesser than the song array size, which is the value of our song counter.
      return NULL;
   }

   return sl->songArr[i];
}


/* Returns song by name. Returns NULL if song does not exist */
Song SongLibraryGetSongByName(SongLibrary sl, const char* song_name) {

   if (!sl || !song_name) {
      fprintf(stderr, "Error in %s: NULL pointer found, aborting\n",__func__);
      exit(4);
   }

   for (unsigned int i = 0; i < sl->count; i++) {

      char* current_name = SongName(sl->songArr[i]);
      //                      ↑
      /* Returns a dynamically allocated string with the song name, without \n in the end 
       * Therefore we are responsible to free(); and need current_name pointer (I almost sent it as an argument to strcmp which would cause mem leaks) */

      if (strcmp(current_name, song_name) == 0) {
         free(current_name);
         return sl->songArr[i];
      }

      free(current_name);
   }

   // if we got here, song_name wasn't found in sl.
   return NULL;
}
