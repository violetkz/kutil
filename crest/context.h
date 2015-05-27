
#ifndef crest_context_h
#define crest_context_h

#include <event2/http.h>
#include "crest.h"

struct params {
    char *params [MAX_PARAM_LEN];
    int   params_len;
};
struct context {
    //char* params[MAX_PARAM_LEN];
    struct params         *params;
    struct evhttp_request *req;
    struct evbuffer       *resp_buf;

    int    response_status_code;
};


struct params* uri_paramslist_new();
void           uri_paramslist_free(struct params *ps);
void           uri_paramslist_append(struct params *ps, const char *s, size_t s_len);
const char*    uri_paramslist_get(struct params *ps, size_t index);


struct context* context_new(struct evhttp_request *req,
                            struct params *pl,
                            struct evbuffer *resp_buf);
void            context_free(struct context *c);

struct params* context_get_params(struct context *c);
const char* context_get_uri(struct context *c);
const char* context_get_host(struct context *c);
const char* context_get_req_header(struct context *c, const char* header);
void context_set_resp_stutus_code(struct context *c, size_t status_code);
void context_set_resp_hearder(struct context *c, const char *header, 
                        const char *value);
int context_append_resp_buf(struct context *c, const char *fmt, ...);


#endif
