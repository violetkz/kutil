

#include <stdio.h>
#include <string.h>
#include <event2/http.h>
#include <event2/keyvalq_struct.h>

#include "crest.h"
#include "token.h"
#include "path.h"
#include "httpd.h"
#include "context.h"
#include "log.h"

int cb_callback(struct context* x, void *arg) {

    const char *uri = evhttp_request_get_uri(x->req);
    evbuffer_add_printf(x->resp_buf, "{\"uri\":\"%s\"",   uri);

    int i=0;
    for (; i<MAX_PARAM_LEN ; ++i) {
        const char *p = uri_paramslist_get(context_get_params(x), i);
        if (p != NULL) {
            evbuffer_add_printf(x->resp_buf, ", \"param\": \"%s\"", p);
        }
    }
    if (arg) {
        evbuffer_add_printf(x->resp_buf, ", \"arg\": \"%s\"", (char *)arg);
    }
    evbuffer_add_printf(x->resp_buf, "}");
    struct evkeyvalq * headers =  evhttp_request_get_output_headers(x->req);
    if (headers) {
        evhttp_add_header(headers, "Content-type",  "application/json");
    }
    return 0;
}

int main() {
    struct path root = init_root();
    struct path test5 = add_path(root, "/{^[c-d]}");
    set_path_cb(test5, 0, cb_callback, NULL);

    struct path test6 = add_path(root, "/{\\d$}");
    char *message = "args test";
    set_path_cb(test6, 0, cb_callback, message);

    struct path test7 = add_path(root, "/{\\d+}/c/{[a-zA-Z]+}");
    set_path_cb(test7, 0, cb_callback, NULL);

#ifdef __DEBUG__
    print_tree(root.node,1);
#endif

//    struct node * m = match_path(root.node, "23/xxa2x");
//    print_tree(m,1);

//    m = match_path(root.node, "23/xxa2x/9");
//    if (m == NULL) {
//       printf("NO match with m\n");
//  }

    
    log_debug("%s --- %s", "xx", "ssss");
    log_err("%s", "~~~~~~~~~");
    log_fn_trace_s;
    log_fn_trace_e;
    crest_run(9999,root.node);


    free_path(root);

    return 0;
}


