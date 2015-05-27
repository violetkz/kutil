/*
 *       Filename:  crest_context.c
 *    Description:
 *        Version:  1.0
 *        Created:  2012/7/19 16:16:05
 *       Compiler:  gcc
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <event2/buffer.h>

#include "crest.h"
#include "context.h"


struct params *uri_paramslist_new() {
    struct params *new_ps = (struct params *)malloc(sizeof (struct params));

    if (new_ps != NULL) {
        memset (new_ps, 0x00, sizeof (struct params));
    }

    return new_ps;
}

void uri_paramslist_free(struct params *ps) {

    if (ps != NULL ) {
        int i = 0;

        for (; i < MAX_PARAM_LEN; ++i) {
            FREE_AND_SET_NULL( ps->params[i] );
        }

        FREE_AND_SET_NULL(ps);
    }
}

void uri_paramslist_append(struct params *ps, const char *s, size_t s_len) {

    int len = ps->params_len;

    if (len < MAX_PARAM_LEN) {
        ps->params[len] = my_strdup(s, len);
        ps->params_len += 1;
    } else {
        //FIXME: handle the error over the limition of MAX_PARAM_LEN;
        printf("[ERROR] %s\n", "over the limition of MAX_PARAM_LEN");
    }
}


const char *uri_paramslist_get(struct params *ps, size_t index) {
    if (index < ps->params_len) {
        return  ps->params[index];
    }

    return NULL;
}

struct context *context_new(struct evhttp_request *req,
                            struct params   *pl,
                            struct evbuffer *resp_buf) {

    struct context *new_ct = (struct context*)malloc(sizeof (struct context));

    if (new_ct != NULL) {
        memset(new_ct, 0x00, sizeof(struct context));

        new_ct->params  = pl;
        new_ct->req = req;
        new_ct->resp_buf = resp_buf;
    }

    return new_ct;
}

void   context_free(struct context *c) {
    if (c != NULL) {
        uri_paramslist_free(c->params);
        FREE_AND_SET_NULL(c);
    }
}

struct params* context_get_params(struct context *c) {
    return c->params;
}

unsigned int context_get_params_len(struct context *c) {
    return (c != NULL) ? c->params->params_len : 0;
}

const char * context_get_param(struct context *c, unsigned int index) {
    return  (c != NULL && index < MAX_PARAM_LEN) ? uri_paramslist_get(c->params, index) : NULL;
}

const char* context_get_uri(struct context *c) {
    return (c != NULL) ?  evhttp_request_get_uri(c->req) : NULL;
}

const char* context_get_host(struct context *c) {
    return (c != NULL) ?  evhttp_request_get_host(c->req) : NULL;
}

const char* context_get_req_header(struct context *c, const char* header) {
    const char * value = NULL;

    if (c != NULL) {
        struct evkeyvalq *req_headers = evhttp_request_get_input_headers(c->req);
        value = evhttp_find_header(req_headers, header);
    }

    return value;
}

void context_set_resp_stutus_code(struct context *c, size_t status_code) {
    if (c != NULL) {
        c->response_status_code = status_code;
    }
}

void context_set_resp_hearder(struct context *c, const char *header,
                              const char *value) {

    if (c != NULL) {
        struct evkeyvalq * headers =  evhttp_request_get_output_headers(c->req);

        if (headers) {
            evhttp_add_header(headers, header,  value);
        }
    }
}

int context_append_resp_buf(struct context *c, const char *fmt, ...) {
    int res = -1;

    if (c) {
        va_list ap;

        va_start(ap, fmt);
        res = evbuffer_add_vprintf(c->resp_buf, fmt, ap);
        va_end(ap);
    }

    return (res);
}
