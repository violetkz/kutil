/*
 *       Filename:  path.h
 *    Description:
 *        Version:  1.0
 *        Created:  2012/7/5 9:53:33
 *       Compiler:  gcc
 *
 */

#include "crest.h"
#include "path.h"

struct path init_root() {
    struct path root = { new_node("/") };
    return root;
}

void free_path(struct path root) {
    delete_node(root.node);
}

struct path add_path(struct path root, char * uri) {
    struct node *n  = new_path(root.node, uri);
    set_node_state(n, NOTE_STATE_REGISTED);
    struct path  np = {n};
    return np;
}

struct node * new_path(struct node * root, char * uri) {
    char *pos = NULL;
    int  len  = 0;
    char *p   = uritok(uri, &len, &pos);
    struct node* current = root;

    while (p) {

        //printf("%s\n", p);
        struct node * r = find_child(current, p, len);
        if (r != NULL)  {
            current = r;
        } else {
            // add all new child nodes once.
            while (p) {
                struct node* new_child = new_node_substr(p, len);
                add_child(current, new_child);
                current = new_child;
                p = uritok(NULL, &len, &pos);
            }
            break;
        }
        p = uritok(NULL, &len, &pos);
    }
    return current;
}


/*
 * FIXME
 * Matching Path rules:
 *      +   FRFO(First registed, first out)
 *      +   MML(MAX matched length)
 * e.g.
 *  pre-compiled node tree below.
 *                                '/'
 *                              /  |   \
 *                             /   |    \
 *                           '1'  {\d}  {\d+}
 *                                 |     |
 *                                / \   / \
 *                               /   |  |  |
 *                             X<1>  Y  X  Y
 *  URI: /1/X should be matched with Node<1>.
 */

int  match_path(struct node *root,
                char *uri,
                struct node ** found,
                struct params **params) {

    char *pos = NULL;
    int  len  = 0;
    char *p   = uritok(uri, &len, &pos);
    struct node* current = root;
    int   re   = REVAL_NOT_MATCHED;

    struct params *ps = NULL;

    while (p) {
        //printf("%s\n", p);
        struct node * r = match_child(current, p, len);
        if (r != NULL)  {
            current = r;

            if (params != NULL && r->re != NULL) {
                if (ps == NULL) {
                    ps = uri_paramslist_new();
                }
                uri_paramslist_append(ps, p, len);
            }

            p = uritok(NULL,&len, &pos);

        } else {
            current = NULL;
            break;
        }
    }

    // if 'current' is registed, return ture.
    if (current != NULL && current->state == NOTE_STATE_REGISTED) {
        if (found != NULL) {
            *found = current;
        }

        if (params != NULL) {
            *params = ps;
        }

        re = REVAL_MATCHED;

    } else {
        if (found != NULL) {
            *found = NULL;
        }

        if (params != NULL) {
            *params = NULL;
        }
        re = REVAL_NOT_MATCHED;

        uri_paramslist_free(ps); //whatever, free the memory here.
    }

    return re;
}


//void set_cb(struct node* n, int method, HANDLE_CALLBACK_FUNC cb);
void set_path_cb(struct path  p, int method, HANDLE_CALLBACK_FUNC cb, void *cb_param) {
    struct node *n = p.node;
    n->cb_funs[method] = cb;
    n->cb_param[method] = cb_param;
}

void del_path_cb(struct path p, int method) {
    struct node *n = p.node;
    n->cb_funs[method] = NULL;
    n->cb_param[method] = NULL;
}

