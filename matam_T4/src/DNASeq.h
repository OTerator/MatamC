#ifndef DNASEQ_H
#define DNASEQ_H

typedef enum {A, C, G, T, Illegal_NA} Base;
typedef struct DNASeq* DNASeq;


/*====================================================*/
/* Constructor:
*/
DNASeq DSCreate(const char* str);
/*====================================================*/
/* Constructor from file:
*/
DNASeq DSCreateFromFile(const char* file_path);
/*====================================================*/
/* Copy constructor
*/
DNASeq DSCopy(DNASeq ds);
/*====================================================*/
/* Destructor
*/
void DSDestroy(DNASeq ds);
/*====================================================*/
/* Accessors and mutators
*/
Base DSGet(DNASeq ds, unsigned int loc);
void DSSet(DNASeq ds, unsigned int loc, Base na);
/*====================================================*/
/* Returns the length of the DNA sequence
*/
unsigned int DSLength(DNASeq ds);
/*====================================================*/
/* Converts the DNA sequence to a string representation (e.g., "ACGT")
*/
char* DSToString(DNASeq ds);
/*====================================================*/
/* Returns the reverse complement of the DNA sequence
*/
DNASeq DSReverseComplement(DNASeq ds);


#endif	// DNASEQ_H