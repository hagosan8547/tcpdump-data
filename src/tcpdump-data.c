#include "tcpdump-data.h"

//#define DEBUG_MY_PACKET_HANDLER 0
#define DEBUG_DATA_OUT_HANDLER 1

char def_dev_str[]="any";

int main(int argc, char const *argv[]) {
  char *device = def_dev_str;
  char error_buffer[PCAP_ERRBUF_SIZE];
  pcap_t *handle;
  /* Snapshot length is how many bytes to capture from each packet. This includes*/
  int snapshot_length = 1024;
  /* End the loop after this many packets are captured */
  int total_packet_count = -1;
  u_char *my_arguments = NULL;

  #ifdef DEBUG_MY_PACKET_HANDLER
  proxy_handler=my_packet_handler;
  #endif

  #ifdef DEBUG_DATA_OUT_HANDLER
  proxy_handler=data_out_handler;
  #endif

  // TODO: add to option
  device=choice_device(atoi(argv[1]));
  
  handle = pcap_open_live(device, snapshot_length, 0, 10000, error_buffer);
  pcap_loop(handle, total_packet_count, proxy_handler, my_arguments);

  return 0;
}
