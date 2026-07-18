#ifndef ARRAY_H
#define ARRAY_H

typedef struct Array* Array;
typedef void* Element;

// Create an empty array with no cells
Array ArrCreate(Element (*cpy)(Element), void (*fre)(Element));

// destroy an array
void ArrDestroy(Array arr);

// Get Array size
unsigned int ArrSize(Array arr);

// Change the size of the Array
void ArrResize(Array arr, unsigned int new_size);

// Insert an element to position pos in arr
Element ArrPut(Array arr, unsigned int pos, Element e);

// Get the element in position pos but leave it in the Array
Element ArrAt(Array arr, unsigned int pos);

// Get the element in position pos and remove it from the Array
Element ArrGet(Array arr, unsigned int pos);


#endif // ARRAY_H