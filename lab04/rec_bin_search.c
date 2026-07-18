#include <stdio.h>

int* recursive_bsearch(int* begin, int* end, int* target) {

    if (begin >= end) {
      return NULL;
    }

    int* middle = begin + ((end-begin)/2);

    if (*middle == *target) {
      return middle;
    } else if (*middle < *target) {
      return recursive_bsearch(middle + 1, end, target);
    } else {
      return recursive_bsearch(begin, middle, target);
    }
}

