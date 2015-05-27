/*
 *       Filename:  uri.h
 *    Description:
 *        Version:  1.0
 *        Created:  2012/7/3 9:36:50
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  ken
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "crest.h"
#include "queue.h"
#include "node.h"


// if the name of node starts with '{' and ends with '}', it will be as
// regular express.
void check_node_type(struct node *n) {

    pcre *re             = NULL;
    char buf[MAX_REGEX_LEN];
    const char * err     = NULL;
    int          offset  = -1;

    const char *name = n->name;
    size_t   name_len= strlen(n->name);

    const char *name_eof_ptr = name + name_len;

    if (name != NULL && name_len > 2 && name_len < MAX_REGEX_LEN) {
        if ( *name  == '{' && *(name + name_len - 1) == '}' ) {
            const char * copy_start_ptr  = name + 1;
            size_t   copy_len        = name_len - 2;

            /*
             * insert the prefix char '^' and postfix char '$' with regex.
             * e.g.
             *      [0-9]+      =>      ^[0-9]+$
             *      ^\d         =>      ^\d$
             *      \d$         =>      ^\d$
             */
            if ( name + 1  < name_eof_ptr && *(name + 1)  == '^') {
                copy_start_ptr += 1;
                copy_len       -= 1;
            }

            buf[0] = '^';
            memcpy(buf + 1, copy_start_ptr, copy_len);

            if (buf[copy_len] != '$') {
                buf[copy_len + 1] = '$';
                buf[copy_len + 2] = '\0';
            } else {
                buf[copy_len + 1] = '\0';
            }
            printf("[DEBUG] check_node.: '%s' \n", buf);

            /* pre-compile the regex. */
            re = pcre_compile(buf, 0,  &err, &offset, NULL);
            if (re == NULL) {
                printf("[ERROR] BAD_REGEX. %s\n", buf);
            }
        }
    }

    n->re = re;
}

int match_node(struct node *n, const char *name, size_t name_len) {

    int match = REVAL_NOT_MATCHED;

    if (n->re != NULL) {
        //the node was defined with regex.
        int re = pcre_exec(n->re, NULL, name, name_len, 0, 0, NULL, 0);
        printf("[DEBUG] pcre_exec return value: %d \n", re);
        if (pcre_exec(n->re, NULL, name, name_len, 0, 0, NULL, 0) >= 0) {
            match = REVAL_MATCHED;
        }
    } else {
        //normal node.
        if ( name_len == strlen(n->name)
                && strncmp(n->name, name, strlen(n->name)) == 0) {
            match = REVAL_MATCHED;
        }
    }

    return match;
}

struct node * new_node(const char *name) {
    struct node * new_node = (struct node *)malloc(sizeof (struct node));
    if (NULL != new_node) {
        memset(new_node, 0x00, sizeof( struct node));
        new_node->name = strdup(name);
        new_node->state= NOTE_STATE_NORMAL;
        check_node_type(new_node);
        //memset(&new_node->cb_funs, 0x00, 5);
        TAILQ_INIT(&new_node->children);
    }
    return new_node;
}

struct node * new_node_substr(const char *name, int len) {
    struct node * new_node = (struct node *)malloc(sizeof (struct node));
    if (NULL != new_node) {
        memset(new_node, 0x00, sizeof( struct node));
        char *buff = (char *) malloc(len + 1);
        new_node->name = buff;
        if (buff != NULL) {
            strncpy(buff, name, len);
            buff[len] = '\0';
        }
        new_node->state= NOTE_STATE_NORMAL;
        check_node_type(new_node);
        //memset(&new_node->cb_funs, 0x00, 5);
        TAILQ_INIT(&new_node->children);
    }
    return new_node;
}

int is_leafnode(struct node* n) {
    int re = 1;
    if (n != NULL && !(TAILQ_EMPTY(&n->children))) {
        re = 0;
    }
    return re;
}

void add_child(struct node* n, struct node* child) {

    TAILQ_INSERT_TAIL(&n->children, child, entries);
}

/*
 * return a child node whose name is 'node_name' of parent node 'p'.
 */
struct node * find_child(struct node* p, char *node_name, size_t node_len) {
    struct node *var;
    TAILQ_FOREACH(var, &p->children, entries) {
        if ( node_len == strlen(var->name)
                && strncmp(var->name, node_name, strlen(var->name)) == 0) {
            return var;
        }
    }
    return NULL;
}

/*
 * return a child node which matched with 'uri_tok'.
 */
struct node * match_child(struct node* p, char *uri_tok, int uri_tok_len) {
    struct node *var;
    TAILQ_FOREACH(var, &p->children, entries) {
        if (match_node(var, uri_tok, uri_tok_len)) {
            return var;
        }
    }
    return NULL;
}

void delete_node(struct node * n) {
    if (! is_leafnode(n)) {
        struct node *var, *tmp;
        for (var = TAILQ_FIRST(&n->children); var != NULL; var = tmp) {
            tmp = TAILQ_NEXT(var, entries);
            TAILQ_REMOVE(&n->children, var, entries);
            delete_node(var);
        }
    }
    //printf("free %s\n", n->name);
    free(n->name);
    free(n);
}

void set_node_state(struct node*n, enum node_state state) {
    n->state = state;
}

#ifdef __DEBUG__
void print_tree(struct node* root, int prechar) {
    printf("%*sname: %s, cb:%p %p %p %p %p, S: %d\n", prechar, " ", root->name,
           root->cb_funs[0],
           root->cb_funs[1],
           root->cb_funs[2],
           root->cb_funs[3],
           root->cb_funs[4],
           root->state
          );

    if (! is_leafnode(root)) {
        struct node *var;
        prechar += 4;
        TAILQ_FOREACH(var, &root->children, entries) {
            print_tree(var, prechar);
        }
    }
}
#endif
