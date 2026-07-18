ortp(int *arr, unsigned int n) {
//     /* selection sort by repeatedly placing the maximum at position i,
//        using only pointer variables (no extra non-pointer variables)
//        and no if / if..else statements. */

//     /* pointer to last element (precondition: n >= 1) */
//     int *last = arr + (int)n - 1;

//     /* i runs from last down to arr+1 (we stop when i == h) */
//     for (int *i = last; i > arr; --i) {
//         int *max = arr;             /* pointer to current maximum in [h..i] */
//         for (int *p = arr; p <= i; ++p) {
//             /* choose the pointer that points to the larger value;
//                ternary operator used instead of if. */
//             max = (*p > *max) ? p : max;
//         }
//         /* swap the value found at max with the value at i */
//         swap(max, i);
//     }
// }