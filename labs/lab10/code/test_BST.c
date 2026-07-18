#include "unity.h"
#include "BST.h"
#include <stdlib.h>
#include <string.h>

// --- Helper Functions for String Elements ---
Element copyString(Element e) {
    if (!e) return NULL;
    char* src = (char*)e;
    char* dest = malloc(strlen(src) + 1);
    if (dest) strcpy(dest, src);
    return (Element)dest;
}

void freeString(Element e) {
    free(e);
}

int compareStrings(Element a, Element b) {
    return strcmp((char*)a, (char*)b);
}

// --- Test Setup ---
Tree tree = NULL;

void setUp(void) {
    // Called before every test
    tree = BSTCreate(copyString, freeString, compareStrings);
}

void tearDown(void) {
    // Called after every test
    BSTDestroy(tree);
}

// --- Tests ---

void test_BST_Create_Should_ReturnEmptyTree(void) {
    TEST_ASSERT_NOT_NULL(tree);
    TEST_ASSERT_EQUAL_UINT(0, BSTNumNodes(tree));
    TEST_ASSERT_EQUAL_UINT(0, BSTHeight(tree));
}

void test_BST_Add_Should_IncreaseCount(void) {
    BSTAdd(tree, "Apple");
    TEST_ASSERT_EQUAL_UINT(1, BSTNumNodes(tree));
    
    BSTAdd(tree, "Banana");
    TEST_ASSERT_EQUAL_UINT(2, BSTNumNodes(tree));
}

void test_BST_Search_Should_FindAddedElements(void) {
    BSTAdd(tree, "Apple");
    BSTAdd(tree, "Banana");
    
    TEST_ASSERT_TRUE(BSTSearch(tree, "Apple"));
    TEST_ASSERT_TRUE(BSTSearch(tree, "Banana"));
    TEST_ASSERT_FALSE(BSTSearch(tree, "Cherry"));
}

void test_BST_Height_Should_CalculateCorrectly(void) {
    // Root only
    BSTAdd(tree, "M"); 
    TEST_ASSERT_EQUAL_UINT(0, BSTHeight(tree));
    
    // M -> L
    BSTAdd(tree, "L");
    TEST_ASSERT_EQUAL_UINT(1, BSTHeight(tree));
    
    // M -> R
    BSTAdd(tree, "R");
    TEST_ASSERT_EQUAL_UINT(1, BSTHeight(tree));
    
    // M -> L -> A (Height 2)
    BSTAdd(tree, "A");
    TEST_ASSERT_EQUAL_UINT(2, BSTHeight(tree));
}

void test_BST_Remove_Leaf_Should_Work(void) {
    BSTAdd(tree, "M");
    BSTAdd(tree, "L");
    BSTAdd(tree, "R");
    
    BSTRemove(tree, "L"); // Leaf
    TEST_ASSERT_FALSE(BSTSearch(tree, "L"));
    TEST_ASSERT_EQUAL_UINT(2, BSTNumNodes(tree));
}

void test_BST_Remove_TwoChildren_Should_Work(void) {
    // This tests the critical bug fix in BSTRemove
    BSTAdd(tree, "M");
    BSTAdd(tree, "L");
    BSTAdd(tree, "R");
    BSTAdd(tree, "S"); // R has child S
    
    // Remove M (Root with 2 children)
    BSTRemove(tree, "M");
    
    TEST_ASSERT_FALSE(BSTSearch(tree, "M"));
    TEST_ASSERT_TRUE(BSTSearch(tree, "R"));
    TEST_ASSERT_TRUE(BSTSearch(tree, "L"));
    TEST_ASSERT_EQUAL_UINT(3, BSTNumNodes(tree));
}

void test_BST_Clone_Should_CreateIndependentCopy(void) {
    BSTAdd(tree, "A");
    BSTAdd(tree, "B");
    
    Tree dupe = BSTClone(tree);
    
    TEST_ASSERT_NOT_NULL(dupe);
    TEST_ASSERT_EQUAL_UINT(BSTNumNodes(tree), BSTNumNodes(dupe));
    TEST_ASSERT_TRUE(BSTSearch(dupe, "A"));
    
    // Modify Original
    BSTRemove(tree, "A");
    
    // Assert Clone is untouched (Deep Copy Check)
    TEST_ASSERT_FALSE(BSTSearch(tree, "A"));
    TEST_ASSERT_TRUE(BSTSearch(dupe, "A"));
    
    BSTDestroy(dupe);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_BST_Create_Should_ReturnEmptyTree);
    RUN_TEST(test_BST_Add_Should_IncreaseCount);
    RUN_TEST(test_BST_Search_Should_FindAddedElements);
    RUN_TEST(test_BST_Height_Should_CalculateCorrectly);
    RUN_TEST(test_BST_Remove_Leaf_Should_Work);
    RUN_TEST(test_BST_Remove_TwoChildren_Should_Work);
    RUN_TEST(test_BST_Clone_Should_CreateIndependentCopy);
    return UNITY_END();
}