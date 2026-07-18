/*******************************************************************************/
/*    HashTable Module by @author Ori Almog

   This module is responsible for:
      - allocating memory and creating new copies for both keys and values given.
      - freeing the memory of mentioned keys, values upon table destruction/pair removal.
      - providing more usful functions to manipulate the data in the table.

   if a memory allocation is failed inside the module, NULL is returned. (for main to handle with MEM_ALLOCATION_ERROR)
   
   - For refrence, The terms "Item" and "Pair" (pair of a key, value) are equivalent.
*/
/*******************************************************************************/

#ifndef HASHTABLE_H
#define HASHTABLE_H
#define MEM_ALLOCATION_ERROR 1


typedef void*  Key;
typedef void*  Value;
typedef struct HashTable* HashTable;

/*******************************************************************************/
/*    Constructor of a new (Generic) HashTable:
   Recieves: 
      + size of the bucket array - which is also the amount of LinkedLists contained.
      + Pointers to essential functions to handle Generic types:
         - Hash function
         - Keys comparison function
         - copy & free functions for both keys and values.

   Returns the new HashTable (pointer). if mem alloc fails, NULL is returned.
*/
HashTable         HTCreate(unsigned int num_buckets, unsigned int (*hash)(Key), int (*keyCmp)(Key, Key),
                            Key (*keyCpy)(Key), Value (*valCpy)(Value), void (*keyFre)(Key), void (*valFre)(Value));
/*******************************************************************************/
/*    HashTable Destructor:
   recieves a HashTable and proceeds to free it according to its struct. 
   all pair copies it held are being freed, then finally, the whole table.  
*/
void              HTDestroy(HashTable ht);
/*******************************************************************************/
/*    HashTable Size:
   returns the count of how many (key, value) items the table has at the moment.
*/
unsigned int      HTSize(HashTable ht);
/*******************************************************************************/
/*    Item Insert:
   adds a new key-value to the HT
   if the key is already taken with a value, they are overwritten with a new pair.
*/
void              HTInsert(HashTable ht, Key key, Value val);
/*******************************************************************************/
/*    Item Remove:
   removes a given key with its value.
   returns the value, and NULL if the key doesn't belong to the set of keys.
   Note: The returned Value is a pointer. The caller of this function is responsible for freeing this Value if necessary, 
   The Key and the internal Node are freed by the table.
*/
Value             HTRemove(HashTable ht, Key key);
/*******************************************************************************/
/*    Item Search:
   search for the pair of a given key.
   returns the value, and NULL if the key doesn't belong to the set of keys.
*/
Value             HTSearch(HashTable ht, Key key);
/*******************************************************************************/


#endif