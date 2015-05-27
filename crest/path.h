/*
 *       Filename:  path.h
 *    Description:
 *        Version:  1.0
 *        Created:  2012/7/5 9:53:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 */

#ifndef __CREST_PATH_
#define __CREST_PATH_

#include "token.h"
#include "node.h"
#include "context.h"

struct path {
    struct node * node;
    //char   *      name;
};

//initial path
struct path init_root();
//free the path.
void   free_path(struct path root);
struct node * new_path(struct node * root, char * uri);
//add a path
struct path add_path(struct path root, char * uri);

int  match_path(struct node *root,
                char *uri,
                struct node ** found,
                struct params **params);

void set_path_cb(struct path  p, int method, HANDLE_CALLBACK_FUNC cb, void *arg);

#endif
