
/*************************************************************************
 * 																							 *
 * 					DNA Sequence Module by Ori Almog								 *
 * 																							 *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>	// toupper()
#include <string.h>
#include "DNASeq.h"

//========================================================================
//							  Structs, Fields and Macros:
//========================================================================

// Macros:
#define ERR_BASE(baseChar)	{fprintf(stderr, "Error at %s, %u: Invalid DNA Sequence: contains '%c', allowed bases are: {A, C, G, T}.", __FILE__, __LINE__, baseChar); exit(1);}
#define ERR_ALLOC(bytes)	{fprintf(stderr, "Error at %s, %u: Failed to allocate %zu bytes.", __FILE__, __LINE__, bytes); exit(2);}
#define ERR_RANGE(index)	{fprintf(stderr, "Error at %s, %u: ERROR Index (%u) out of bounds.", __FILE__, __LINE__, index); exit(3);}
#define ERR_READF(path) 	{fprintf(stderr, "Error at %s, %u: ERROR in reading %s file.", __FILE__, __LINE__, path); exit(4);}


/**	Struct DNASeq has:
 * 
 * 		- 	data: 	Dynamically allocated unsigned char array data, to store the sequence using bits.
 * 		- 	bytes:	Size of data in bytes, which is also the length of the data arr because sizeof(unsigned char) = 1.
 * 		- 	len:		Original length of the str.
 */
struct DNASeq {
	unsigned char* data;
	size_t bytes;
	unsigned int len;
};


/**
 * module-private arr used for a Base → char representation mapping.
 * used in the validation process of a Sequence and toString convertion.
 */
static const char charBase[] = {'A', 'C', 'G', 'T'};


//========================================================================
//										Helpers:
//========================================================================

/** DSAlloc - Constructor helper function
 * 	made to significantly reduce code duplication.
 */
static DNASeq DSAlloc(unsigned int len) {
	DNASeq ds = (DNASeq)malloc(sizeof(struct DNASeq));
	if (!ds) {
		fflush(NULL);		// close any open FILE* streams.
		ERR_ALLOC(sizeof(struct DNASeq));
   }

	// num bytes = num_bits/8 = len/4 + extraByte: extraByte = len (mod 4) == 0 ? 0, 1; compensates for the extra needed byte.
	size_t num_bytes = len/4 + (len%4 != 0);		// Data length.

	ds->data = (unsigned char*)calloc(num_bytes, sizeof(unsigned char));	// sizeof(unsigned char) == 1 byte;
	if (!ds->data) {
		free(ds);
		fflush(NULL);		// close any open FILE* streams.
		ERR_ALLOC(num_bytes);
	}
	
	// Apply:
	ds->bytes = num_bytes;
	ds->len = len;
	return ds;
}

//========================================================================

/**  Appender made for both String and File Constructors, allowing significant code reuse.
 * Recieves:
 * 	unsigned char* address: a block for the data sequence arr, used to hold 4 pairs of bits. 
 * 	a char of a base (from a string of the sequence or a buffer reading from a file)
 * 	
 * Examines the given char base and exits if invalid.
 * then, proceeds to append the bits into the given memory block.
 **/
static void baseAppend(unsigned char* block, char ch_base) {
	
	Base base = Illegal_NA; 

	for (unsigned char i=0; i<4; i++) {
		if (charBase[i] == toupper(ch_base)) {
			base = (Base)(i);	// Base casting on i.
		}
	}

	if (base == Illegal_NA) {
		ERR_BASE(base);		// exits. all allocated memory should be freed by the OS.
	}	// after this check we know char is valid and may be appened.
		
	*block >>= 2;	// pull the previous values by 2
	*block |= ((unsigned char)(base)) << 6;	// at a mask push the base's integers forward by 6 for the last 2 index, then OR.
} 





//========================================================================
//										Constructors:
//========================================================================

/** Constructor from String */
DNASeq DSCreate(const char* str){
	if (!str) return NULL;

	// 1. Initialization:
	DNASeq ds = DSAlloc(strlen(str));	// will exit if fails.
	
	// 2. Validation + Data appending
	unsigned char* curr_byte = ds->data;
	for (unsigned int i = 1; *str; i++, str++) {		// while *str != '\0'

		baseAppend(curr_byte, *str);		// append the next char into its relative block.

		if (!(i % 4)) curr_byte++; 		// after every 4 chars, move to the next block.
	}

	//	make sure any leftover bits get pushed from MSB to LSB, in case it is not full. 
	if (ds->len % 4) {		// len%4 != 0
		*curr_byte >>= ((4 - (ds->len%4)) * 2);		 
	}


	return ds;
}

//========================================================================

/** Constructor from file:
 * 
 * 	I've concluded that reading the entire sequence into a char* str and returning DSCreate(str); somewhat defeats the purpose this light memory efficient implementation.
 * 	Hence to why this function scans the file to retrieve the length, then proceeds to allocate data memory and put the Bases one by one, buffer style.
 */ 
DNASeq DSCreateFromFile(const char* file_path) {

	FILE* fp = fopen(file_path, "r");
	if (!fp) ERR_READF(file_path);
	
	// 1. Setup: Scan for len calculation + Allocate memory:
	unsigned int len = 0;
	char c;
	for (; ((c = fgetc(fp)) != EOF) && (c != '\n'); len++)
	;

	DNASeq ds = DSAlloc(len);		// exits and flushes if fails.


	// 2. Validation + Data appending:
	rewind(fp);
	unsigned char* curr_byte = ds->data;

	for (unsigned int i = 1; ((c = fgetc(fp)) != EOF) && (c != '\n'); i++) {

		baseAppend(curr_byte, c);			// append the next char into its relative block.

		if (!(i % 4)) curr_byte++; 		// after every 4 chars, move to the next block.
	}
	
	//	make sure any leftover bits get pushed from MSB to LSB, in case it is not full. 
	if (ds->len % 4) {		// len%4 != 0
		*curr_byte >>= ((4 - (ds->len%4)) * 2);		 
	}


	fclose(fp);
	return ds;
}

//========================================================================

/** Copy constructor 
 * 	recieves a DNA Sequence and returns a new duplicate.
 */
DNASeq DSCopy(DNASeq ds) {
	if (!ds) return NULL;
	
	//	Duplicate:
	DNASeq dup = DSAlloc(ds->len);		// exits upon alloc failure
	
	for (unsigned int i=0; i<ds->bytes; i++) {
		*(dup->data + i) = *(ds->data + i);
	}
	dup->bytes = ds->bytes;
	dup->len = ds->len;

	return dup;
}

//========================================================================

/** Destructor */
void DSDestroy(DNASeq ds) {
	if (!ds) return;

	if (ds->data) free(ds->data);
	free(ds);
}



//========================================================================
//										Functions:
//========================================================================

// Accessors and mutators:

/** DSGet
 * 	Base getter, recieves a sequence and a location and returns the base stored there.
 * 	location is determined according to the char* index (!)
 * 	example: ACGTGA, ibdex with range [0; 5] → 3210,XX54 indexing of bit pairs at data.
 */
Base DSGet(DNASeq ds, unsigned int loc) {
	if (!ds) return Illegal_NA;
	
	if (loc >= (ds->len)) ERR_RANGE(loc);	// exits

	unsigned char extracted = *(ds->data + loc/4);	// extract the block accordingly
	extracted >>= (loc % 4)*2; 							// shift twice for each 
	return (extracted & 3);
}
/** DSSet
 * 	Base setter, recieves the Base, and a sequence with a location to put at. 
 * 	location is determined according to the char* index (!)
 */
void DSSet(DNASeq ds, unsigned int loc, Base na) {
	if (!ds) return;

	if (loc >= (ds->len)) ERR_RANGE(loc);	// exits

	if (na == Illegal_NA) ERR_BASE(na);
	
	// setup- move two turned on bits to the modular location we need to set (then flip).
	unsigned int shift = (loc%4)*2;
	unsigned char mask = 3 << shift;

	*(ds->data + loc/4) &= ~mask;				// set 00 cleanup
	*(ds->data + loc/4) |= (na << shift);	// inject value
}

//========================================================================

// Returns the length of the DNA sequence
unsigned int DSLength(DNASeq ds) {
	if (!ds) return 0;

	return ds->len;
}

//========================================================================

/** Converts the DNA sequence to a string representation (e.g., "ACGT")
 * 
 * 	Returns a dynamically allocated char*
 **/
char* DSToString(DNASeq ds) {
	if (!ds) return NULL;

	char* str = (char*)malloc(ds->len + 1);	// +1 for '\0'
	if (!str) ERR_ALLOC((size_t)(ds->len + 1));
	
	// get char by char
	for (unsigned int loc = 0; loc < ds->len; loc++) {
		str[loc] = charBase[DSGet(ds, loc)];
	}
	//	put \0 by the end.
	str[ds->len] = '\0';

	return str;
}

//========================================================================

// Returns the reverse complement of the DNA sequence
DNASeq DSReverseComplement(DNASeq ds) {
	if (!ds) return NULL;

	// 1. Create a copy:
	DNASeq dup = DSCopy(ds);	// should exit on failure
	if (!dup) return NULL;


	// 2. Flip all:
	for (unsigned int i = 0; i < dup->bytes; i++) {
		*(dup->data + i) = ~*(ds->data + i);
	}
	

	// 3. Reverse:
	//	if len is even, all pairs get swapped appropriately.
	// if odd, middle remains as is, and its reverse, has actually already been made - by flipping.
	for (unsigned int i = 0; i < dup->len / 2; i++) {
		// first get both
		Base left = DSGet(dup, i);
		Base right = DSGet(dup, dup->len -1 -i);

		// proceed to set - essentially swapping.
		DSSet(dup, i, right);
		DSSet(dup, dup->len -1 -i, left);
	}

	
	return dup;
}

//========================================================================