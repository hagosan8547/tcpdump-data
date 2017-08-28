#include "tcpdump-data.h"

void data_out_handler(
  u_char *args,
  const struct pcap_pkthdr *header,
  const u_char *packet
) {
  struct ether_header *eth_header;
  eth_header = (struct ether_header *) packet;
  if (ntohs(eth_header->ether_type) != ETHERTYPE_IP) {
      fprintf(stderr,"Not an IP packet. Skipping...\n");
      return;
  }
  const u_char *ip_header;
  const u_char *tcp_header;
  const u_char *payload;

  int eth_header_len = 14; /* Doesn't change */
  int ip_header_len;
  int tcp_header_len;
  int payload_len;

  /* ip header length set */
  ip_header = packet + eth_header_len;
  ip_header_len = ((*ip_header) & 0x0F);
  ip_header_len = ip_header_len * 4;

  u_char protocol = *(ip_header + 9);
  if (protocol != IPPROTO_TCP) {
      fprintf(stderr,"Not a TCP packet. Skipping...\n");
      return;
  }

  /* tcp header length set */
  tcp_header = packet + eth_header_len + ip_header_len;
  tcp_header_len = ((*(tcp_header + 12)) & 0xF0) >> 4;
  tcp_header_len = tcp_header_len * 4;

  /* total length calculate */
  int total_headers_size = eth_header_len+ip_header_len+tcp_header_len;

  /* payload length and payload pointer set */
  payload_len = header->caplen -
      (eth_header_len + ip_header_len + tcp_header_len);
  payload = packet + total_headers_size;

  if (payload_len > 0) {
      const u_char *temp_pointer = payload;
      int byte_count = 0;
      while (byte_count++ < payload_len) {
          printf("%c", *temp_pointer);
          temp_pointer++;
      }
      printf("\n");
  }
  return;
}
