#include "../unity/unity.h"
#include "../src/DNASeq.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void setUp() {}
void tearDown() {}



/*********************************************/
//                Tests:
/*********************************************/
/**
 * I've written tests for most of the header functions,
 * DSLength and DSDestroy are rather trivial, so instead of having their own tests, they are integrated within all others.
 */

// DSCreate + DSGet:
void test_DSCreate_and_DSGet() {

   // Test String constructor + len getter
   DNASeq ds = DSCreate("acGTAt");    // substring GTA was not intended actually

   TEST_ASSERT_NOT_NULL(ds);
   TEST_ASSERT_EQUAL_INT(6, DSLength(ds));

   // Test getter
   TEST_ASSERT_EQUAL_INT(A, DSGet(ds, 0));
   TEST_ASSERT_EQUAL_INT(C, DSGet(ds, 1));
   TEST_ASSERT_EQUAL_INT(G, DSGet(ds, 2));
   TEST_ASSERT_EQUAL_INT(T, DSGet(ds, 3));
   TEST_ASSERT_EQUAL_INT(A, DSGet(ds, 4));
   TEST_ASSERT_EQUAL_INT(T, DSGet(ds, 5));

   DSDestroy(ds);

   // NULL test
   DNASeq nds = DSCreate(NULL);
   TEST_ASSERT_NULL(nds);

}


// Test DSSet:
void test_DSSet() {
   DNASeq ds = DSCreate("AAAAA");
   TEST_ASSERT_NOT_NULL(ds);

   // ATAAA
   DSSet(ds, 1, T);
   TEST_ASSERT_EQUAL_INT(T, DSGet(ds, 1));

   // ATAAG
   DSSet(ds, 4, G);
   TEST_ASSERT_EQUAL_INT(G, DSGet(ds, 4));

   TEST_ASSERT_EQUAL_INT(A, DSGet(ds, 0));
   TEST_ASSERT_EQUAL_INT(A, DSGet(ds, 2));
   TEST_ASSERT_EQUAL_INT(A, DSGet(ds, 3));


   DSDestroy(ds);
}


// Test DSCopy:
void test_DSCopy() {
   DNASeq ds = DSCreate("ACGTATGAGAT");
   DNASeq dup = DSCopy(ds);

   TEST_ASSERT_NOT_NULL(ds);
   TEST_ASSERT_NOT_NULL(dup); 

   DSSet(dup, 0, T);

   TEST_ASSERT_EQUAL_INT(DSLength(ds), DSLength(dup));
   TEST_ASSERT_EQUAL_INT(A, DSGet(ds, 0));
   TEST_ASSERT_EQUAL_INT(T, DSGet(dup, 0));

   DSDestroy(ds); 
   DSDestroy(dup);
}


// Test the toString:
void test_DSToString() {
   const char* str = "ACGTAC";
   DNASeq ds = DSCreate(str);
   TEST_ASSERT_NOT_NULL(ds);

   char* result = DSToString(ds);
   TEST_ASSERT_NOT_NULL(result);

   TEST_ASSERT_EQUAL_STRING(str, result);

   free(result);
   DSDestroy(ds);
}


// Test File Constructor:
void test_DSCreateFromFile() {
   const char* filename = "test_dna_sequence.txt";
   const char* data = "ACGTACGT\n";

   // setup:
   FILE* fp = fopen(filename, "w");
   if (!fp) TEST_FAIL_MESSAGE("Testing file creation failed");
   fputs(data, fp);
   fclose(fp);


   DNASeq ds = DSCreateFromFile(filename);
   TEST_ASSERT_NOT_NULL(ds);
   TEST_ASSERT_EQUAL_INT(8, DSLength(ds));

   char* res = DSToString(ds);
   TEST_ASSERT_EQUAL_STRING("ACGTACGT", res);

   free(res);
   DSDestroy(ds);
   remove(filename);
}


// Complement test:
void test_DSReverseComplement() {

   DNASeq ds1 = DSCreate("ACGT");
   DNASeq comp1 = DSReverseComplement(ds1);

   char* str1 = DSToString(comp1);
   TEST_ASSERT_EQUAL_STRING("ACGT", str1);
   free(str1);
   DSDestroy(ds1);
   DSDestroy(comp1);



   DNASeq ds2 = DSCreate("AAC");
   DNASeq comp2 = DSReverseComplement(ds2);
   char* str2 = DSToString(comp2);
   TEST_ASSERT_EQUAL_STRING("GTT", str2); // Verify result
    
   // Verify Deep Copy (Original shouldn't change)
   char* original_str = DSToString(ds2);
   TEST_ASSERT_EQUAL_STRING("AAC", original_str);

   free(str2);
   free(original_str);
   DSDestroy(ds2);
   DSDestroy(comp2);
}



int main() {
   UNITY_BEGIN();

   printf("DNASeq.c Unity Tests:\n");
   RUN_TEST(test_DSCreate_and_DSGet);
   RUN_TEST(test_DSSet);
   RUN_TEST(test_DSCopy);
   RUN_TEST(test_DSToString);
   RUN_TEST(test_DSCreateFromFile);
   RUN_TEST(test_DSReverseComplement);

   UNITY_END();
   return 0;
}
