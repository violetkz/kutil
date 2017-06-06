/*
 * =====================================================================================
 *
 *       Filename:  token.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2012/7/5 15:49:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "crest.h"
#include "util.h"
#include "token.h"

/* Parse S into tokens separated by characters in DELIM.
   If S is NULL, the saved pointer in SAVE_PTR is used as
   the next starting point.  For example:
	char s[] = "-abc-=-def";
	char *sp;
	x = strtok_r(s, "-", &sp);	// x = "abc", sp = "=-def"
	x = strtok_r(NULL, "-=", &sp);	// x = "def", sp = NULL
	x = strtok_r(NULL, "=", &sp);	// x = NULL
		// s = "abc\0-def\0"
*/


char *
__strtok_ (char *s, const char *delim, char **save_ptr) {
    char *token;

    if (s == NULL) {
        s = *save_ptr;
    }

    /* Scan leading delimiters.  */
    s += strspn (s, delim);
    if (*s == '\0') {
        *save_ptr = s;
        return NULL;
    }

    /* Find the end of the token.  */
    token = s;
    s = strpbrk (token, delim);
    if (s == NULL) {
        /* This token finishes the string.  */
        *save_ptr = strchr (token, '\0');
        token = my_strdup(token, *save_ptr - token);
    } else {
        /* Terminate the token and make *SAVE_PTR point past it.  */
        // *s = '\0';

        int len = s - token;
        token = my_strdup(token, len);

        *save_ptr = s + 1;
    }
    return token;
}

// URI TOKEN
char *
uritok(char *s, int *token_len, char **save_ptr) {
    char *token;
    *token_len  = 0;

    if (s == NULL) {
        s = *save_ptr;
    }

    /* Scan leading delimiters.  */
    s += strspn (s, "/");
    if (*s == '\0') {
        *save_ptr = s;
        return NULL;
    }

    /* Find the end of the token.  */
    token = s;
    s = strpbrk (token, "/");
    if (s == NULL) {
        /* This token finishes the string.  */
        *save_ptr = strchr (token, '\0');
        *token_len = *save_ptr - token;
    } else {
        /* Terminate the token and make *SAVE_PTR point past it.  */
        //*s = '\0';
        *save_ptr = s + 1;
        *token_len = s - token;
    }
    return token;
}
