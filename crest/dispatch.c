
#include <stdlib.h>
#include <stdio.h>
#include <event2/http.h>
#include <event2/buffer.h>

#include "path.h"
#include "dispatch.h"

/*
 * Reutrn the decoded path and return NULL if it is not good URI.
 * NOTE: Must call 'free' for release memory.
 */
static char * decode_path(const char *uri) {

    const char *path = NULL;
    struct evhttp_uri *decoded  = NULL;
    char * decoded_path = NULL;

    /* Decode the URI */
    decoded = evhttp_uri_parse(uri);
    if (!decoded) {
        return NULL;
    }

    /* Let's see what path the user asked for. */
    path = evhttp_uri_get_path(decoded);
    if (!path) {
        path = "/";
    }

    /* We need to decode it, to see what path the user really wanted. */
    decoded_path = evhttp_uridecode(path, 0, NULL);

    if (decoded) {
        evhttp_uri_free(decoded);
    }

    return decoded_path;
}

/*
 * req: the pointer of evhttp_request.
 * n  : the pointer of struct node which handle this request.
 * method : which kind of HTTP request
 * ct     : the struct context pointer which hold the response data.
 */
int call_handler_and_response(struct evhttp_request *req, int method, struct node *n, struct context *ct) {

    HANDLE_CALLBACK_FUNC  cb_func = n->cb_funs[method];
    void *cb_param = n->cb_param[method];

    int reval = 0;
    if (cb_func != NULL) {
        int cb_func_reval = (*cb_func)(ct, cb_param);
        //FIXME: should check the status code which set by caller.
        if (cb_func_reval == 0) {/* OK */
            evhttp_send_reply(req, 200, "OK", ct->resp_buf);

            reval = 1;
        }
    }

    return reval;
}


/*
 * This callback gets invoked when we get any http request that doesn't match
 * any other callback.
 */
void dispatch_path_cb(struct evhttp_request *req, void *arg) {

    struct evbuffer   *evb      = NULL;
    const char *uri = evhttp_request_get_uri(req);
    char *decoded_path  = NULL;
    struct node *root = (struct node *)arg;

    decoded_path = decode_path(uri);
    if (decode_path == NULL)        /* Bad URI, response 404. */
        goto err_404;

    printf("[DEBUG] received path is {%s}\n", decoded_path);

    /* This holds the content we're sending. */
    struct context *ct = NULL;
    struct node *n = NULL;
    int cb_func_reval = 0;
    struct params * param_list = NULL;

    match_path(root, decoded_path, &n, &param_list);
    if (n != NULL) {
        evb = evbuffer_new();
        ct = context_new(req, param_list, evb);

        switch (evhttp_request_get_command(req)) {

        case EVHTTP_REQ_GET:
            printf("[DEBUG] EVHTTP_REQ_POST: %d\n", EVHTTP_REQ_POST);
            call_handler_and_response(req, 0, n, ct);
            goto done;

        case EVHTTP_REQ_POST:
            printf("[DEBUG] EVHTTP_REQ_POST: %d\n", EVHTTP_REQ_POST);
            call_handler_and_response(req, 1, n, ct);
            goto done;

        case EVHTTP_REQ_PUT:
            printf("[DEBUG] EVHTTP_REQ_POST: %d\n", EVHTTP_REQ_POST);
            call_handler_and_response(req, 2, n, ct);
            goto done;

        case EVHTTP_REQ_DELETE:
            printf("[DEBUG] EVHTTP_REQ_POST: %d\n", EVHTTP_REQ_POST);
            call_handler_and_response(req, 3, n, ct);
            goto done;

        default:
            printf("Not Supported HTTP Resquest method.");
            evhttp_send_error(req, 501, "Not Supported HTTP Resquest method.");
            goto done;
        }
    }

err_404:
    evhttp_send_error(req, 404, "Document was not found!!");

done:
    if (decoded_path) {
        free(decoded_path);
    }
    if (evb) {
        evbuffer_free(evb);
    }
    context_free(ct);
}


