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

  int ethernet_header_length = 14; /* Doesn't change */
  int ip_header_length;
  int tcp_header_length;
  int payload_length;

  ip_header = packet + ethernet_header_length;
  ip_header_length = ((*ip_header) & 0x0F);
  ip_header_length = ip_header_length * 4;

  u_char protocol = *(ip_header + 9);
  if (protocol != IPPROTO_TCP) {
      fprintf(stderr,"Not a TCP packet. Skipping...\n");
      return;
  }

  tcp_header = packet + ethernet_header_length + ip_header_length;
  tcp_header_length = ((*(tcp_header + 12)) & 0xF0) >> 4;
  tcp_header_length = tcp_header_length * 4;

  int total_headers_size = ethernet_header_length+ip_header_length+tcp_header_length;
  payload_length = header->caplen -
      (ethernet_header_length + ip_header_length + tcp_header_length);
  payload = packet + total_headers_size;

  if (payload_length > 0) {
      const u_char *temp_pointer = payload;
      int byte_count = 0;
      while (byte_count++ < payload_length) {
          printf("%c", *temp_pointer);
          temp_pointer++;
      }
      printf("\n");
  }
  return;
}
