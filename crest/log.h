
#ifndef log_hpp_______
#define log_hpp_______

#include <stdarg.h>
/*
 * log levels and flags.
 */
typedef enum
{
  /* GLib log levels */
  G_LOG_LEVEL_ERROR    = 0,       /* always fatal */
  G_LOG_LEVEL_CRITICAL,
  G_LOG_LEVEL_WARNING ,
  G_LOG_LEVEL_MESSAGE , 
  G_LOG_LEVEL_INFO    ,
  G_LOG_LEVEL_DEBUG   ,
} LOG_LEVEL;


typedef void (*log_func)(const char *log_domain, 
                         LOG_LEVEL level, 
                         const char *message,
                         void *arg);

/* Logging mechanism
typedef void (*log_func)(const char *log_domain, 
                         LOG_LEVEL level, 
                         const char *message,
                         void *arg);

unsigned int log_set_handler(const char *log_domain,
                             LOG_LEVEL  log_levels,
                             log_func   log_func,
                             void *     user_data);

void   log_remove_handler(const char    *log_domain,
                          unsigned int  handler_id);

*/
void   log_default_handler(const char    *log_domain,
                           LOG_LEVEL  log_level,
                           const char    *message,
                           void *        unused_data);

log_func  log_set_default_handler(log_func log_func);

void logv(const char    *log_domain,
          LOG_LEVEL     log_level,
          const char    *format,
          va_list       args,
          void*         data);

void simple_log(const char *domain, LOG_LEVEL level, const char* fmt, ...); 

#if 1
#define DOMAIN_STR  "cRest"
#define log_debug(FMT, ...) simple_log(DOMAIN_STR, G_LOG_LEVEL_DEBUG, FMT, __VA_ARGS__)
#define log_info(FMT, ...)  simple_log(DOMAIN_STR, G_LOG_LEVEL_INFO, FMT, __VA_ARGS__)
#define log_warn(FMT, ...)  simple_log(DOMAIN_STR, G_LOG_LEVEL_WARNING, FMT, __VA_ARGS__)
#define log_err(FMT, ...)  simple_log(DOMAIN_STR, G_LOG_LEVEL_ERROR, FMT, __VA_ARGS__)

#define log_fn_trace_s       simple_log(DOMAIN_STR, G_LOG_LEVEL_DEBUG, "[func: %s --->]", __func__) 
#define log_fn_trace_e       simple_log(DOMAIN_STR, G_LOG_LEVEL_DEBUG, "[func: %s <---]", __func__) 

#endif
#endif
