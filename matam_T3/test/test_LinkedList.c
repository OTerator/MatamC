#include "../unity/unity.h"
#include "../src/LinkedList.h"


/* Define a handle for the list used in tests */
LinkedList list;

/* * Setup: Called before every test.
 * Creates a fresh empty list to ensure test isolation.
 */
void setUp(void) {
    list = LLCreate();
}

/* * Teardown: Called after every test.
 * Destroys the list to prevent memory leaks between tests.
 */
void tearDown(void) {
    LLDestroy(list);
}

/* ======================================================
 * Tests for Creation and Size
 * ====================================================== */

void test_LLCreate_Should_ReturnNonNullAndZeroSize(void) {
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL_UINT(0, LLSize(list));
}

/* ======================================================
 * Tests for Adding Elements
 * ====================================================== */

void test_LLAdd_Should_IncreaseSize(void) {
    int val1 = 10;
    LLAdd(list, 0, &val1);
    TEST_ASSERT_EQUAL_UINT(1, LLSize(list));

    int val2 = 20;
    LLAdd(list, 1, &val2);
    TEST_ASSERT_EQUAL_UINT(2, LLSize(list));
}

void test_LLAdd_AtZero_Should_PrependToFront(void) {
    /* Add "First" */
    char* e1 = "First";
    LLAdd(list, 0, e1);

    /* Add "NewFirst" at index 0 */
    char* e2 = "NewFirst";
    LLAdd(list, 0, e2);

    /* Verify size */
    TEST_ASSERT_EQUAL_UINT(2, LLSize(list));

    /* Verify order using LLFirst (assuming LLFirst works, which we test later) */
    TEST_ASSERT_EQUAL_PTR(e2, LLFirst(list));
}

void test_LLAdd_AtSize_Should_AppendToBack(void) {
    char* e1 = "Start";
    char* e2 = "End";

    LLAdd(list, 0, e1);
    LLAdd(list, LLSize(list), e2); /* Add at current size (index 1) */

    TEST_ASSERT_EQUAL_UINT(2, LLSize(list));
    
    /* Verify "Start" is still first */
    TEST_ASSERT_EQUAL_PTR(e1, LLFirst(list));
    /* Verify "End" is next */
    TEST_ASSERT_EQUAL_PTR(e2, LLNext(list));
}

void test_LLAdd_InMiddle_Should_InsertCorrectly(void) {
    int v1 = 1, v2 = 2, v3 = 3;

    /* Create List: 1, 3 */
    LLAdd(list, 0, &v1);
    LLAdd(list, 1, &v3);

    /* Insert 2 at index 1. Result should be: 1, 2, 3 */
    LLAdd(list, 1, &v2);

    TEST_ASSERT_EQUAL_UINT(3, LLSize(list));
    
    /* Verify Order */
    TEST_ASSERT_EQUAL_PTR(&v1, LLFirst(list));
    TEST_ASSERT_EQUAL_PTR(&v2, LLNext(list));
    TEST_ASSERT_EQUAL_PTR(&v3, LLNext(list));
}

/* ======================================================
 * Tests for Removing Elements
 * ====================================================== */

void test_LLRemove_Should_ReturnElement_And_DecreaseSize(void) {
    int val = 99;
    LLAdd(list, 0, &val);

    Element removed = LLRemove(list, 0);

    TEST_ASSERT_EQUAL_PTR(&val, removed);
    TEST_ASSERT_EQUAL_UINT(0, LLSize(list));
}

void test_LLRemove_FromMiddle_Should_MaintainLinks(void) {
    /* List: A, B, C */
    char *a = "A", *b = "B", *c = "C";
    LLAdd(list, 0, a);
    LLAdd(list, 1, b);
    LLAdd(list, 2, c);

    /* Remove index 1 (B) */
    Element removed = LLRemove(list, 1);

    TEST_ASSERT_EQUAL_PTR(b, removed);
    TEST_ASSERT_EQUAL_UINT(2, LLSize(list));

    /* Check remaining structure is A -> C */
    TEST_ASSERT_EQUAL_PTR(a, LLFirst(list));
    TEST_ASSERT_EQUAL_PTR(c, LLNext(list));
}

void test_LLRemove_FromFront(void) {
    int v1 = 10, v2 = 20;
    LLAdd(list, 0, &v1);
    LLAdd(list, 1, &v2);

    Element removed = LLRemove(list, 0);
    
    TEST_ASSERT_EQUAL_PTR(&v1, removed);
    TEST_ASSERT_EQUAL_UINT(1, LLSize(list));
    TEST_ASSERT_EQUAL_PTR(&v2, LLFirst(list));
}

/* ======================================================
 * Tests for Iteration (LLFirst / LLNext)
 * ====================================================== */

void test_LLFirst_OnEmptyList_Should_ReturnNull(void) {
    TEST_ASSERT_NULL(LLFirst(list));
}

void test_LLNext_OnEmptyList_Should_ReturnNull(void) {
    /* Note: Calling LLNext without calling LLFirst is strictly undefined behavior 
       in many implementations, but typically returns NULL on empty lists. */
    /* If your implementation relies on LLFirst being called first to set internal state,
       this test might fail depending on implementation specifics. 
       Standard usage implies LLFirst is called at least once. */
    TEST_ASSERT_NULL(LLFirst(list)); 
    TEST_ASSERT_NULL(LLNext(list));
}

void test_Iteration_Should_TraverseAllElements(void) {
    int data[] = {100, 200, 300, 400};
    int num_elements = 4;

    /* Fill list */
    for (int i = 0; i < num_elements; i++) {
        LLAdd(list, i, &data[i]);
    }

    /* Iterate */
    int count = 0;
    Element e;
    for (e = LLFirst(list); e != NULL; e = LLNext(list)) {
        /* Verify we get the pointer to the exact element we put in */
        TEST_ASSERT_EQUAL_PTR(&data[count], e);
        count++;
    }

    TEST_ASSERT_EQUAL_INT(num_elements, count);
}

void test_Iteration_Reset_With_LLFirst(void) {
    int v1 = 1, v2 = 2;
    LLAdd(list, 0, &v1);
    LLAdd(list, 1, &v2);

    /* Move cursor to end */
    LLFirst(list);
    LLNext(list); 

    /* Call LLFirst again, it should reset to start */
    TEST_ASSERT_EQUAL_PTR(&v1, LLFirst(list));
    TEST_ASSERT_EQUAL_PTR(&v2, LLNext(list));
}

/* ======================================================
 * Main Runner
 * ====================================================== */

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_LLCreate_Should_ReturnNonNullAndZeroSize);
    
    RUN_TEST(test_LLAdd_Should_IncreaseSize);
    RUN_TEST(test_LLAdd_AtZero_Should_PrependToFront);
    RUN_TEST(test_LLAdd_AtSize_Should_AppendToBack);
    RUN_TEST(test_LLAdd_InMiddle_Should_InsertCorrectly);
    
    RUN_TEST(test_LLRemove_Should_ReturnElement_And_DecreaseSize);
    RUN_TEST(test_LLRemove_FromMiddle_Should_MaintainLinks);
    RUN_TEST(test_LLRemove_FromFront);
    
    RUN_TEST(test_LLFirst_OnEmptyList_Should_ReturnNull);
    RUN_TEST(test_LLNext_OnEmptyList_Should_ReturnNull);
    RUN_TEST(test_Iteration_Should_TraverseAllElements);
    RUN_TEST(test_Iteration_Reset_With_LLFirst);

    return UNITY_END();
}