/*
 *       Filename:  uri.h
 *    Description:
 *        Version:  1.0
 *        Created:  2012/7/3 9:36:50
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  ken
 */

#ifndef __CREST_NODE_
#define __CREST_NODE_

#include <stdlib.h>
#define PCRE_STATIC
#include <pcre.h>
#include "queue.h"

struct context;

typedef int (*HANDLE_CALLBACK_FUNC)(struct context *, void *arg) ;

enum node_state {
    NOTE_STATE_NORMAL,
    NOTE_STATE_REGISTED
};

struct node {

    char                 *name;        // the node name
    pcre                 *re;          // if node name is regex, here holds the
    // pre-compiled regex result for matching.
    enum node_state      state;

    HANDLE_CALLBACK_FUNC  cb_funs[5];  //callback funcions
    void                 *cb_param[5]; //the parameter for callback function.


    TAILQ_HEAD(,node)  children; // the children list of this Node.
    TAILQ_ENTRY(node)  entries;  // This holds the pointers
    // to the next and previous entries.
};


struct node * new_node(const char *name);
struct node * new_node_substr(const char *name, int name_len) ;
void delete_node(struct node * n) ;

int  is_leafnode(struct node* n) ;
void add_child(struct node* n, struct node* child) ;
void set_node_state(struct node*n, enum node_state state);

struct node * find_child(struct node* p, char *node_name, size_t node_len);
struct node * match_child(struct node* p, char *uri_tok, int uri_tok_len);

#ifdef __DEBUG__
void print_tree(struct node* root, int prechar) ;
#endif
#endif
