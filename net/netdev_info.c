#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <ifaddrs.h>
#include <stdlib.h>
#include <string.h>

#include "netdev_info.h"
//typedef int (*iffilter)(struct ifaddrs *, void *);

//The  getifaddrs()  function creates a linked list of structures describing the
//network interfaces of the local system, and stores the address
//of the first item of the list in *ifap.  The list consists of ifaddrs
//structures, defined as follows:
//
//   struct ifaddrs {
//       struct ifaddrs  *ifa_next;    /* Next item in list */
//       char            *ifa_name;    /* Name of interface */
//       unsigned int     ifa_flags;   /* Flags from SIOCGIFFLAGS */
//       struct sockaddr *ifa_addr;    /* Address of interface */
//       struct sockaddr *ifa_netmask; /* Netmask of interface */
//       union {
//           struct sockaddr *ifu_broadaddr;
//                            /* Broadcast address of interface */
//           struct sockaddr *ifu_dstaddr;
//                            /* Point-to-point destination address */
//       } ifa_ifu;
//   #define              ifa_broadaddr ifa_ifu.ifu_broadaddr
//   #define              ifa_dstaddr   ifa_ifu.ifu_dstaddr
//       void            *ifa_data;    /* Address-specific data */

static struct netdevinfos *clone(struct ifaddrs* ifaddr) {
    if (ifaddr) {
        unsigned int size = sizeof(struct netdevinfos);
        struct netdevinfos *node = (struct netdevinfos*) malloc (size);
        if (node) {
            memset(node, 0x00, size);

            strncpy(node->ifa_name, ifaddr->ifa_name, IFNAMSIZ);
            node->ifa_flags = ifaddr->ifa_flags;

            unsigned int sockaddr_len = sizeof (struct sockaddr);

            memcpy(&(node->ifa_addr), ifaddr->ifa_addr, sockaddr_len);
            if (ifaddr->ifa_netmask) {
                memcpy(&(node->ifa_netmask), ifaddr->ifa_netmask, sockaddr_len);
            }
            if (ifaddr->ifa_data != NULL) {
                memcpy(&(node->ifa_data), ifaddr->ifa_data, 64);
            }
        }
        return node;
    }
    return NULL;
}

void free_netdevinfos(struct netdevinfos *result) {
    
    while(result) {
        struct netdevinfos *next =  result->ifa_next;
        free(result);
        result =  next;
    }
}

int get_netdevinfos(struct netdevinfos **result, iffilter filter, void* filter_arg) {
    struct ifaddrs *ifaddrs_; 
    int rc = getifaddrs(&ifaddrs_);

    struct ifaddrs *cur = ifaddrs_;

    struct netdevinfos *result_head = NULL;
    struct netdevinfos *result_tail = NULL;
    while (cur != NULL) {
        if (filter && 0  == filter(cur, filter_arg)) {
            struct netdevinfos *node = clone(cur);
            
            if (result_head == NULL) 
                result_head = node;
            else {
                result_tail->ifa_next = node;
            }
            result_tail =  node;
        }
        cur = cur->ifa_next;
    }
    freeifaddrs(ifaddrs_);
    *result = result_head;
    return rc;
}

