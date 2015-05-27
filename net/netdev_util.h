#ifndef __netdev_utl_h
#define __netdev_utl_h

struct netdevice;

struct netdevice* netdevice_init();
void netdevice_free(struct netdevice *nd);

/* enable netdevice by ifname */
int netdevice_enable(struct netdevice *nd, const char* ifname) ;

/* disable netdevice by ifname */
int netdevice_disable(struct netdevice *nd, const char* ifname) ;

/* setup the IPv4 address */
int netdevice_set_ip4(struct netdevice *nd, 
                        const char* ifname,
                        const char* ip, 
                        const char* netmask);
#endif
