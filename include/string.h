#ifndef INCLUDE_STRING_H_
#define INCLUDE_STRING_H_
#include "types.h"

extern void memcpy(char *, const char *, int);

extern void memset(void *, char, int);

extern void bzero(void *, int);

extern int strcmp(const char *, const char *);

extern char * strcpy(char *, const char *);

extern char * strcat(char *, const char *);

extern int strlen(const char *);

#endif
