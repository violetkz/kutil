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

#ifndef ___CREST_TOKEN
#define ___CREST_TOKEN

#include <assert.h>
#include <stdlib.h>

char *
__strtok_ (char *s, const char *delim, char **save_ptr);

// URI TOKEN
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
uritok(char *s, int *token_len, char **save_ptr) ;

#endif
