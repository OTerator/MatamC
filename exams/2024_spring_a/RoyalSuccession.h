#ifndef ROYALSUCCESSION_H
#define ROYALSUCCESSION_H
#include <stdbool.h>

typedef struct RoyalSuccession* RoyalSuccession;

RoyalSuccession		RSCreate();

void				RSDestroy(RoyalSuccession rs);

const char*			RSGet(RoyalSuccession rs, unsigned int i);

bool				RSAdd(RoyalSuccession rs, const char* name, unsigned int i);

unsigned int		RSNumSuccessors(RoyalSuccession rs);

void				RSPrint(RoyalSuccession rs);


#endif