#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/** 
 * About access Linux network device with `ioctl'
 * 
 * please refer to the following items with command `man'
 *      netdeivice(7)
 *      socket(7)
 *      ioctl_list(2)
 *      getifaddrs(3)
 *
 */
struct netdevice {
    int sockfd;
};

struct netdevice* netdevice_init() {

    struct netdevice* nd = 
            (struct netdevice *) malloc (sizeof(struct netdevice));

    if (nd != NULL) {
        nd->sockfd = socket(AF_INET, SOCK_DGRAM, 0);  
        if (nd->sockfd == -1) {
            free(nd);
            nd = NULL;
        }
    }
    return nd;
}

void netdevice_free(struct netdevice *nd) {
    
    if (nd != NULL) {
        close(nd->sockfd);
        free(nd);
    }
}

#if 0
#define NETDEVICE_LIST_SIZE 24 

int netdevice_list(struct netdevice *nd) {

    if (!nd) {
        return -1; 
    }
    return getifaddrs(&nd->nd_list);
#endif
    
#if 0
    struct ifconf ifc;
    int len = NETDEVICE_LIST_SIZE * sizeof(struct ifreq);

    int i = 0;
    while (1) {
        ifc.ifc_len = len;
        ifc.ifc_buf = (char *) malloc(ifc.ifc_len);
        ioctl(nd->sockfd, SIOCGIFCONF, &ifc);
        if (len > ifc.ifc_len)  {
            break;
        }
        // here, it mean the buf size is too small to fill all info.
        else {
            len += NETDEVICE_LIST_SIZE * sizeof(struct ifreq);
            free(ifc.ifc_buf);
        }
    }

    struct ifreq * cur_ifreq = 0;
    for (; i < ifc.ifc_len / sizeof(struct ifreq); ++i) {
        cur_ifreq = ifc.ifc_req + i;
        printf("=ifc.name: %s\n", cur_ifreq->ifr_name);
    }
}

#endif
static int netdevice_ioctl(struct netdevice *nd, int if_action, struct ifreq *req) {
   
    int rc = -1;
    if (nd && req) {
        rc = ioctl(nd->sockfd, if_action, req);
        if (rc == -1)  {
            perror("ioctl");
            rc = errno;
        }
    }
    return rc;
}

static int netdevice_get_flag(struct netdevice *nd, const char* ifname, int* flags) {

    struct ifreq req;
    strncpy(req.ifr_name, ifname, IFNAMSIZ);
    int rc = netdevice_ioctl(nd, SIOCGIFFLAGS, &req);
    if (rc == 0) {
        *flags = req.ifr_flags;
    }
   
    return rc;
}

static int netdevice_set_flag(struct netdevice *nd, const char* ifname, int flags) {
    struct ifreq req;
    strncpy(req.ifr_name, ifname, IFNAMSIZ);
    req.ifr_flags = flags;
    return netdevice_ioctl(nd, SIOCSIFFLAGS, &req);
}

int netdevice_enable(struct netdevice *nd, const char* ifname) {
    
    int flag = 0;
    int rc = netdevice_get_flag(nd, ifname,&flag);
    if (rc == 0) {
        flag |= IFF_UP | IFF_RUNNING;
        rc = netdevice_set_flag(nd, ifname, flag);
    }
    return rc;
}

int netdevice_disable(struct netdevice *nd, const char* ifname) {
    
    int flag = 0;
    int rc = netdevice_get_flag(nd, ifname, &flag);
    if (rc == 0) {
        flag &= ~IFF_UP;
        rc = netdevice_set_flag(nd, ifname, flag);
    }
   
    return rc;
}

static int mypton(const char * ip, struct sockaddr *sa) {
    memset(sa, 0x00, sizeof(struct sockaddr));
    sa->sa_family = AF_INET;
    struct sockaddr_in * add_in =(struct sockaddr_in *)sa;
    return inet_pton(AF_INET, ip, &add_in->sin_addr); 
}

int netdevice_set_ip4(struct netdevice *nd, 
                        const char* ifname,
                        const char* ip, 
                        const char* netmask) {
    if (nd == NULL || ifname == NULL) 
        return -1;
    struct sockaddr if_addr;
    struct sockaddr if_netmaskaddr;
   
    if (mypton(ip, &if_addr) != 1
        || mypton(netmask, &if_netmaskaddr) != 1) {
        // invaild ipv4 address.
        return -1; 
    }
   
    struct ifreq req;
    strncpy(req.ifr_name, ifname, IFNAMSIZ);
    memcpy(&req.ifr_addr, &if_addr, sizeof(struct sockaddr));
    
    int rc =  netdevice_ioctl(nd,SIOCSIFADDR, &req);
    if (rc == 0) {
        memcpy(&req.ifr_netmask, &if_netmaskaddr, sizeof(struct sockaddr));
        rc =  netdevice_ioctl(nd, SIOCSIFNETMASK, &req);
    }
    
    return rc;
}

#ifdef __netdev_util_debug__

int main(int args, char* argv[]) {
    //disable_eth("lo");
    //netdevice_list();
    if (args > 1) {
        struct netdevice *nd = netdevice_init();

        if (nd) {
            int flag;
            int rc = netdevice_get_flag(nd, argv[1], &flag);
            if (rc!=0) perror("get flag");
            if (flag & IFF_UP) printf("UP ");
            if (flag & IFF_RUNNING) printf("running ");
            if (flag & IFF_LOOPBACK) printf("lo ");
            if (flag & IFF_MULTICAST) printf("multicast ");
            printf("\n");
        }
        if (args > 2) {
            char *ip  = argv[2];
            char *netmask = NULL;
            if (args > 3) {
                netmask  = argv[3];
            }
            int rc = netdevice_set_ip4(nd, argv[1], ip, 
                    (netmask) ? netmask: "255.0.0.0" ); 
            if (rc !=0) perror("set ip");
        }
    }
    
    return 0;
}
#endif
