
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "util.h"

char* my_strdup(const char* start, int len) {
    char* buf = (char *)malloc(len + 1);
    assert(buf != NULL);
    //printf("%p\n", buf);

    strncpy(buf, start, len);
    *(buf + len) = '\0';
    return buf;
}
