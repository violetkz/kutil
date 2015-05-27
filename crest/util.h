
#ifndef _CREST_UTIL___H
#define _CREST_UTIL___H

/* the limition number of the parameters in URI */
#define MAX_PARAM_LEN 5

/* the MAX length of regular express parameter */
#define MAX_REGEX_LEN 64

/* return code: found the matched node. */
#define REVAL_MATCHED 1

/* return code: Not found the matched node */
#define REVAL_NOT_MATCHED 0

#define FREE_AND_SET_NULL(X)                                 \
{                                                            \
    if ( (X) != NULL ) {                                     \
        free( (X) );                                         \
        X = NULL;                                            \
    }                                                        \
}                                                            \
 
/* HTTP method */
enum {
CREST_HTTP_METHOD_GET = 0, 
CREST_HTTP_METHOD_POST,
CREST_HTTP_METHOD_PUT,
CREST_HTTP_METHOD_DELETE,
};


#if 0
#define NEW_STRUCT(X)
{

    X * new_ptr = (X *) malloc (sizeof(X));
    if (new_ptr != NULL) {
        memset(new_ptr, 0x00, sizeof(X));
    }
} while(0);
#endif

/*
 * copy the string from pointer 'start' with length 'len'.
 * return the new string pointer.
 * NOTE: Must *free the memory* after using.
 */
char* my_strdup(const char* start, int len);

#endif
