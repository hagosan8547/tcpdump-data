#include "tcpdump-data.h"

int main(int argc, char const *argv[]) {
  char *device = "any";
  char error_buffer[PCAP_ERRBUF_SIZE];
  pcap_t *handle;
  /* Snapshot length is how many bytes to capture from each packet. This includes*/
  int snapshot_length = 1024;
  /* End the loop after this many packets are captured */
  int total_packet_count = -1;
  u_char *my_arguments = NULL;

  handle = pcap_open_live(device, snapshot_length, 0, 10000, error_buffer);
  pcap_loop(handle, total_packet_count, my_packet_handler, my_arguments);

  return 0;
}
