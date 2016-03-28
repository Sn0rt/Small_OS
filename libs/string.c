#include "string.h"

inline void memcpy(char *dest, const char *src, int len)
{
    for ( ; len != 0; len--) {
        *dest++ =  *src++;
    }
}

inline void memset(void *dest, char val, int len)
{
    char *dst = (char *)dest;
    for ( ; len != 0; len--) {
        *dst++ = val;
    }
}

inline void bzero(void *dest, int len)
{
    memset(dest, 0, len);
}

inline int strcmp(const char *s1, const char *s2)
{
    while (*s1 && s2 && (*s1++ == *s2++));
    if (*s1 == '\0' && *s2 == '\0')
        return 0;
    else if (*s1 == '\0')
        return -1;
    else
        return 1;
}

inline char * strcpy(char *dest, const char *src)
{
    char *tmp = dest;
    while (*src)
        *dest++ = *src++;
    *dest = '\0';
    return tmp;
}

inline char *strcat(char *dest, const char *src)
{
    char *cp = dest;
    while (*cp)
        cp++;
    while ((*cp++ = *src++));
    return dest;
}

inline int strlen(const char *src)
{
    const char *end = src;
    while (*end++);
    return (end - src - 1);
}
