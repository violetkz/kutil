
#include <stdio.h>
#include "log.h"

static log_func global_log_handler = NULL;

static const char * log_message_tbl[] = {
    "ERROR" ,
    "CRITICAL",
    "WARNING" ,
    "MESSAGE" ,
    "INFO"    ,
    "DEBUG"   ,
    NULL
};

void   log_default_handler(const char *log_domain,
                           LOG_LEVEL  log_level,
                           const char *message,
                           void *     unused_data) {

    fprintf(stdout, "-%s- [%-8s]: %s\n", log_domain,
            log_message_tbl[log_level],
            message
           );
}

log_func  log_set_default_handler(log_func log_func_) {
    log_func old = global_log_handler;
    global_log_handler = log_func_;
    return old;
}


void logv(const char    *log_domain,
          LOG_LEVEL     log_level,
          const char    *format,
          va_list       args,
          void*         data) {

#define LOG_BUFF_LEN 2048
    
    char buf[LOG_BUFF_LEN];
    vsnprintf(buf,LOG_BUFF_LEN, format, args);

    if (global_log_handler) {
        (*global_log_handler)(log_domain, log_level, buf, data);
    } else {
        log_default_handler(log_domain, log_level, buf, NULL);
    }
}

void simple_log(const char* domain, LOG_LEVEL level, const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    logv(domain, level, fmt, ap, NULL);
    va_end(ap);
}
