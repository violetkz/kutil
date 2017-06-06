
#ifndef ___DISPATCH__H
#define ___DISPATCH__H


/* 
 * the callback function for general http request.
 */
void dispatch_path_cb(struct evhttp_request *req, void *arg);

/*
 * the callback function for URI: /static.
 */
void dispatch_path_static_res_cb(struct evhttp_request *req, void *arg);


#endif 
