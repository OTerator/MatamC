#include "../unity/unity.h"
#include "../src/HashTable.h"
#include <stdlib.h>
#include <string.h>

/* ========================================================================= */
/* HELPER FUNCTIONS                             */
/* ========================================================================= */

/* --- Integer Helpers --- */
unsigned int hashInt(Key k) {
    unsigned int x = *(int*)k;
    // Simple hash: just the number itself.
    // This allows us to predict collisions easily (e.g. 1 and 11 collide in size 10)
    return x;
}

int cmpInt(Key k1, Key k2) {
    return (*(int*)k1 - *(int*)k2);
}

Key copyInt(Key k) {
    int* newInt = malloc(sizeof(int));
    if (newInt) *newInt = *(int*)k;
    return newInt;
}

void freeInt(Key k) {
    free(k);
}

Value copyValInt(Value v) {
    return copyInt(v); // Value is same logic as Key for ints
}

void freeValInt(Value v) {
    freeInt(v);
}

/* --- String Helpers --- */
unsigned int hashString(Key k) {
    char* str = (char*)k;
    unsigned int hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

int cmpString(Key k1, Key k2) {
    return strcmp((char*)k1, (char*)k2);
}

Key copyString(Key k) {
    char* s = (char*)k;
    
    // strdup is not C99 standard, so we implement the logic manually:
    char* copy = malloc(strlen(s) + 1);
    if (copy) {
        strcpy(copy, s);
    }
    return copy;
}

void freeString(Key k) {
    free(k);
}

/* ========================================================================= */
/* TESTS                                   */
/* ========================================================================= */

HashTable ht = NULL;

void setUp(void) {
    // We will initialize HT in specific tests to allow different configurations
    ht = NULL;
}

void tearDown(void) {
    if (ht != NULL) {
        HTDestroy(ht);
        ht = NULL;
    }
}

/* 1. Test Creation and Destruction
   Verifies that the table is created not NULL and size is 0.
*/
void test_CreateAndDestroy(void) {
    ht = HTCreate(10, hashInt, cmpInt, copyInt, copyValInt, freeInt, freeValInt);
    TEST_ASSERT_NOT_NULL_MESSAGE(ht, "HashTable should be created successfully");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, HTSize(ht), "New HashTable should be empty");
}

/* 2. Test Basic Insertion and Search (Integers)
   Verifies that we can add an element and find it back.
*/
void test_InsertAndSearch_Integers(void) {
    ht = HTCreate(10, hashInt, cmpInt, copyInt, copyValInt, freeInt, freeValInt);
    
    int k = 42;
    int v = 100;

    HTInsert(ht, &k, &v);

    TEST_ASSERT_EQUAL_INT(1, HTSize(ht));
    
    int* res = (int*)HTSearch(ht, &k);
    TEST_ASSERT_NOT_NULL(res);
    TEST_ASSERT_EQUAL_INT(100, *res);
}

/* 3. Test Search Missing Key
   Verifies that searching for a non-existent key returns NULL.
*/
void test_Search_Missing_Key(void) {
    ht = HTCreate(10, hashInt, cmpInt, copyInt, copyValInt, freeInt, freeValInt);
    int k = 5;
    int v = 50;
    HTInsert(ht, &k, &v);

    int missing = 99;
    Value res = HTSearch(ht, &missing);
    TEST_ASSERT_NULL_MESSAGE(res, "Search should return NULL for missing keys");
}

/* 4. Test Update Existing Key [cite: 157]
   Verifies that inserting a key that already exists updates the value
   and does not increase the size.
*/
void test_Update_Existing_Key(void) {
    ht = HTCreate(10, hashInt, cmpInt, copyInt, copyValInt, freeInt, freeValInt);
    
    int k = 10;
    int v1 = 100;
    int v2 = 200;

    HTInsert(ht, &k, &v1);
    TEST_ASSERT_EQUAL_INT(1, HTSize(ht));
    
    // Insert same key, new value
    HTInsert(ht, &k, &v2); 
    TEST_ASSERT_EQUAL_INT(1, HTSize(ht)); // Size should stay 1

    int* res = (int*)HTSearch(ht, &k);
    TEST_ASSERT_NOT_NULL(res);
    TEST_ASSERT_EQUAL_INT(200, *res); // Value should be updated
}

/* 5. Test Remove [cite: 232, 233]
   Verifies removing an element returns the value, reduces size, 
   and makes the key unsearchable.
*/
void test_Remove(void) {
    ht = HTCreate(10, hashInt, cmpInt, copyInt, copyValInt, freeInt, freeValInt);
    int k = 7;
    int v = 77;

    HTInsert(ht, &k, &v);
    
    // Remove existing
    int* removedVal = (int*)HTRemove(ht, &k);
    TEST_ASSERT_NOT_NULL(removedVal);
    TEST_ASSERT_EQUAL_INT(77, *removedVal);
    TEST_ASSERT_EQUAL_INT(0, HTSize(ht));
    
    // Caller is responsible for freeing the value returned by Remove 
    // (since our copyValInt mallocs)
    free(removedVal);

    // Try to search/remove again
    TEST_ASSERT_NULL(HTSearch(ht, &k));
    TEST_ASSERT_NULL(HTRemove(ht, &k));
}

/* 6. Test Collision Handling
   Verifies that two keys hashing to the same bucket are both stored 
   and retrieved correctly.
   With bucket size 10: 1 % 10 = 1, 11 % 10 = 1.
*/
void test_Collision_Handling(void) {
    ht = HTCreate(10, hashInt, cmpInt, copyInt, copyValInt, freeInt, freeValInt);
    
    int k1 = 1;  int v1 = 10;
    int k2 = 11; int v2 = 110;

    HTInsert(ht, &k1, &v1);
    HTInsert(ht, &k2, &v2);

    TEST_ASSERT_EQUAL_INT(2, HTSize(ht));

    int* r1 = (int*)HTSearch(ht, &k1);
    int* r2 = (int*)HTSearch(ht, &k2);

    TEST_ASSERT_NOT_NULL(r1);
    TEST_ASSERT_NOT_NULL(r2);
    TEST_ASSERT_EQUAL_INT(10, *r1);
    TEST_ASSERT_EQUAL_INT(110, *r2);
}

/* 7. Test Generic Strings [cite: 220]
   Verifies the table works with String keys and Integer values.
*/
void test_Strings_Keys(void) {
    // Strings as keys, Ints as values
    ht = HTCreate(5, hashString, cmpString, copyString, copyValInt, freeString, freeValInt);

    char* k1 = "Hello";
    int v1 = 1;
    char* k2 = "World";
    int v2 = 2;

    HTInsert(ht, k1, &v1);
    HTInsert(ht, k2, &v2);

    TEST_ASSERT_EQUAL_INT(2, HTSize(ht));
    
    int* r1 = (int*)HTSearch(ht, k1);
    TEST_ASSERT_EQUAL_INT(1, *r1);

    // Remove "Hello"
    int* removed = (int*)HTRemove(ht, k1);
    TEST_ASSERT_EQUAL_INT(1, *removed);
    free(removed);

    TEST_ASSERT_EQUAL_INT(1, HTSize(ht));
    TEST_ASSERT_NULL(HTSearch(ht, k1));
}

/* ========================================================================= */
/* MAIN RUNNER                                */
/* ========================================================================= */

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_CreateAndDestroy);
    RUN_TEST(test_InsertAndSearch_Integers);
    RUN_TEST(test_Search_Missing_Key);
    RUN_TEST(test_Update_Existing_Key);
    RUN_TEST(test_Remove);
    RUN_TEST(test_Collision_Handling);
    RUN_TEST(test_Strings_Keys);
    return UNITY_END();
}