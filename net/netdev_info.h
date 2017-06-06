#ifndef netdev_info_h_
#define netdev_info_h_

#include <net/if.h> 
#include <sys/types.h>
#include <ifaddrs.h>

struct netdevinfos {
   struct netdevinfos  *ifa_next;            /* Next item in list */
   char            ifa_name[IFNAMSIZ];       /* Name of interface */
   unsigned int    ifa_flags;                /* Flags from SIOCGIFFLAGS */
   struct sockaddr ifa_addr;                 /* Address of interface */
   struct sockaddr ifa_netmask;              /* Netmask of interface */
   char            ifa_data[64];
};


// the filter function definition for `get_netdevs_info'
enum {
    IFFILTER_MATCH     = 0, 
    IFFILTER_DISMATCH  = 1
};

/* filter callback function definition */
typedef int (*iffilter)(struct ifaddrs *, void *);

/* get netdevinfos */
int get_netdevinfos(struct netdevinfos **result, iffilter filter, void* filter_arg);

/* free memory */
void free_netdevinfos(struct netdevinfos *result);

#endif //~netdev_info_h_
