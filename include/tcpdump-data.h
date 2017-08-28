#ifndef TCPDUMP_DATA_H
#define TCPDUMP_DATA_H

#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#ifdef _WIN32
/* Windows */
#include <Winsock2.h>

struct ether_header {
  u_char ether_dhost[6];
  u_char ether_shost[6];
  u_short ether_type;
};

#else
/* Linux */
#include <netinet/in.h>
#include <netinet/if_ether.h>
#endif


#define ETHERTYPE_PUP 0x0200 /* PUP protocol */
#define ETHERTYPE_IP  0x0800 /* IP protocol */
#define ETHERTYPE_ARP 0x0806 /* Addr, resolution protocol */

typedef struct ether_header eth_h_t;

// Add to handlr proxy function.
void (*proxy_handler)(
  u_char *args,
  const struct pcap_pkthdr *header,
  const u_char *packet
);

extern void data_out_handler(
  u_char *args,
  const struct pcap_pkthdr *header,
  const u_char *packet
);

extern void my_packet_handler(
  u_char *args,
  const struct pcap_pkthdr *header,
  const u_char *packet
);

extern char *choice_device(
  int device_num
);

extern int print_device(
  pcap_if_t *alldevs
);

#endif
