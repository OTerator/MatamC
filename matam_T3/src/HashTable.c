#include "HashTable.h"
#include "LinkedList.h"
#include <stdlib.h>
#include <stdio.h>


/*******************************************************************************/


typedef struct {
   Key key;
   Value value;
} Pair;


struct HashTable {

   // fields:
   LinkedList* buckets;
   unsigned int num_buckets;
   unsigned int size;

   // functions:
   unsigned int (*hash)(Key);
   int          (*keyCmp)(Key, Key);
   Key          (*keyCpy)(Key);
   void         (*keyFre)(Key);
   Value        (*valCpy)(Value);
   void         (*valFre)(Value);

};


/*******************************************************************************/
/*    Constructor of a new (Generic) HashTable:
   Recieves: 
      - size of the bucket array - which is also the amount of LinkedLists contained.
      - pointer to a hash function
      - 
   Returns the new HashTable (pointer).
*/
HashTable HTCreate(unsigned int num_buckets, unsigned int (*hash)(Key), int (*keyCmp)(Key, Key), Key (*keyCpy)(Key), Value (*valCpy)(Value), void (*keyFre)(Key), void (*valFre)(Value)) {

   HashTable ht = (HashTable)malloc(sizeof(struct HashTable));
   if (!ht) {
      fprintf(stderr, "%s/%u: failed to allocate %zu bytes\n", __FILE__, __LINE__, sizeof(struct HashTable));
      return NULL;   // main handles.
   }

   ht->buckets = (LinkedList*)calloc(num_buckets, sizeof(LinkedList));
   if (!ht->buckets) {
      fprintf(stderr, "%s/%u: failed to allocate %zu bytes\n", __FILE__, __LINE__, sizeof(struct HashTable));
      free(ht);
      return NULL;   // main handles.
   }

   for (unsigned int i = 0; i < num_buckets; i++) {
      ht->buckets[i] = LLCreate();
      if (!ht->buckets[i]) {  // LLCreate already printed a mem alloc error, (NULL was returned).
         // abort:
         for (unsigned int j = 0; j < i; j++) {
            LLDestroy(ht->buckets[j]);
         }
         free(ht->buckets);
         free(ht);
         return NULL;   // main handles, case where LLCreate failed to allocate memory.
      }
   }


   ht->num_buckets = num_buckets;   // bucket arr size.
   ht->size = 0;                    // Empty table
   ht->hash = hash;                 // function pointers.
   ht->keyCmp = keyCmp;
   ht->keyCpy = keyCpy;
   ht->keyFre = keyFre;
   ht->valCpy = valCpy;
   ht->valFre = valFre;

   return ht;
}

/*******************************************************************************/
/*    HashTable Destructor:
   recieves a HashTable and proceeds to free it according to its struct. 
   all pair copies it held are being freed, then finally, the whole table.  
*/
void              HTDestroy(HashTable ht) {
   // first we want to free each bucket from its contents, which means:
   // free the (key, value) of each Pair,                                    1.
   // then the pair itself, and after all pairs are freed:                   2.
   // free each bucket.                                                      3.
   // once that process is done: we may free the array of buckets            4.
   // and any other allocated structs of HT (if any exist) before:                     
   // freeing the whole HT                                                   5.
   if (!ht) {
      return;
   }

   for (unsigned int i = 0; i < ht->num_buckets; i++) {
      LinkedList pairs = ht->buckets[i];

      unsigned int num_pairs = LLSize(pairs);
      for (unsigned int j = 0; j < num_pairs; j++) {
         // remove the first element each time, num_pairs times to empty the current bucket
         Pair* pair = (Pair*)LLRemove(pairs, 0);
         if (pair) { // if not NULL already, free the contents of the pair    1.
            ht->keyFre(pair->key);
            ht->valFre(pair->value);
            free(pair);    //                                                 2.
         }
      }  // all pairs of the current bucket have been destroyed
      // the current bucket is now empty and may be freed.                    3.
      LLDestroy(pairs);
   }

   free(ht->buckets);   // empty arr                                          4.
   free(ht);            // empty struct                                       5.
}

/*******************************************************************************/
/*    HashTable Size:
   returns the count of how many (key, value) items the table has at the moment.
*/
unsigned int      HTSize(HashTable ht) {
   if (!ht) {
      return 0;
   }
   return ht->size;
}

/*******************************************************************************/
/*    Item Insert:
   adds a new key-value to the HT
   if the key is already taken with a value, they are overwritten with a new pair.
*/
void              HTInsert(HashTable ht, Key key, Value val) {
   if (!ht) {
      return;
   }

   // mapping of a key to its corresponding bucket via the hash function
   // if the returned hash value is out of range, we will take it in (mod num_buckets) which is equivalent to (mod arr_size), 
   // hence all of the hash images are narrowed into the range of array indexes.
   unsigned int index = ht->hash(key) % ht->num_buckets;
   LinkedList bucket = ht->buckets[index];

   // next, we must check if the key already exists in the LinkedList (the bucket is a pointer to it):
   Pair* pair = (Pair*)LLFirst(bucket);   // returns the first element, and sets the iterative current tracker to the head of the list 
   while (pair) { // while "hasNext()" : 
      if (ht->keyCmp(pair->key, key) == 0) { // checks if the current pair's key is the same as the given one:
         // if we're here the given key is already in the bucket. therefore, we replace the already existing value:
         ht->keyFre(pair->value);
         pair->value = ht->valCpy(val);
         return;
      }
      // if here, the key has not been found yet in the LL, and we need to check the next pair:
      pair = (Pair*)LLNext(bucket);
   }
   // if here, we have iterated over the entire LL and the given pair's key has not been found therefore:
   // it is a new key that requires a new pair to be added, and the size of the bucket is increased by 1.

   Pair* newPair = (Pair*)malloc(sizeof(Pair));
   if (!newPair) {
      fprintf(stderr, "%s/%u: failed to allocate %zu bytes\n", __FILE__, __LINE__, sizeof(Pair));
      // no other memory was allocated before this fail, and we may abort and return safetly. the error message will be printed to the error output.
      exit(MEM_ALLOCATION_ERROR);   // this function returns void, so there was no choice but to put this macro here aswell. all other cases are NULLs that get captured by the user in main, following the requested return types of the pdf.
   }

   newPair->key = ht->keyCpy(key);
   newPair->value = ht->valCpy(val);
   // new pair is added to the start of the LL.
   LLAdd(bucket, 0, newPair);
   ht->size++;
}

/*******************************************************************************/
/*    Item Remove:
   removes a given key with its value.
   returns the value, and NULL if the key doesn't belong to the set of keys.
   Note: The returned Value is a pointer. The caller of this function is responsible for freeing this Value if necessary, 
   The Key and the internal Node are freed by the table.
*/
Value             HTRemove(HashTable ht, Key key) {
   if (!ht) {  // you can't lose what you never had.
      return NULL;
   }

   unsigned int index = ht->hash(key) % ht->num_buckets;
   LinkedList bucket = ht->buckets[index];

   // we have to iterate over the entire LL-bucket until we find the target else return NULL.
   // this index will be used for for LLRemove if a pair with the key is found:
   unsigned int indexLL = 0;
   Pair* pair = (Pair*)LLFirst(bucket);

   while (pair) {
      if (ht->keyCmp(pair->key, key) == 0) {
         Pair* removed = (Pair*)LLRemove(bucket, indexLL);
         
         if (removed) {
            // we need to keep a pointer to the value before removing the wrapping pair struct.
            Value rmVal = removed->value;
            
            ht->keyFre(removed->key);  // free key
            free(removed); // free the pair struct
            
            ht->size--;
            // returns the value of the removed pair.
            return rmVal;
         }
      }
      // not found, check the next element (pair):
      pair = (Pair*)LLNext(bucket);
      indexLL++;
   }
   
   return NULL;
}

/*******************************************************************************/
/*    Item Search:
   search for the pair of a given key.
   returns the value, and NULL if the key doesn't belong to the set of keys.
*/
Value             HTSearch(HashTable ht, Key key) {
   if (!ht) {
      return NULL;
   }

   unsigned int index = ht->hash(key) % ht->num_buckets;    // had the thought of implementing a getPair() function for this reptitive pair checking process, chose not to this time.
   LinkedList bucket = ht->buckets[index];

   Pair* pair = (Pair*)LLFirst(bucket);
   while (pair) { // iterator-hasNext()
      if (ht->keyCmp(pair->key, key) == 0) {
         return pair->value;  // found
      }  // else
      pair = (Pair*)LLNext(bucket); // iterator-next();
   }

   // a pair with the given key was not found.
   return NULL;
}

/*******************************************************************************/
