#include "tcpdump-data.h"

//#define DEBUG_MY_PACKET_HANDLER 0
#define DEBUG_DATA_OUT_HANDLER 1
#define DEBUG

char def_dev_str[]="eth0";

/*
 * -F [FILENAME]
 * --Filter [FILENAME]
 * --Filter=[FILENAME]
 *     Use file as input for the filter expression.
 *     An additional expression given
 *     on the command line is ignored.
 *
 * -d
 * --dump
 *     Dump the compiled packet-matching code
 *     in a human readable form
 *     to standard output and stop.
 *
 * -w [FILENAME]
 * -wfile [FILENAME]
 * -wfile=[FILENAME]
 *     Write the raw packets
 *     to file rather than parsing
 *     and printing them out.
 */
 /* higher priority: Filter, interface.
  * lower priority: snapshot-length
  */
struct option longopts[] = {
  { "Filter",         optional_argument, NULL, 'F' },
  { "dump",           no_argument,       NULL, 'd' },
  { "interface",      optional_argument, NULL, 'i' },
  { "wfile",          optional_argument, NULL, 'w' },
  { "rfile",          optional_argument, NULL, 'r' },
  { "buffersize",     optional_argument, NULL, 'b' },
  { "changesize",     optional_argument, NULL, 'c' },
  { "snapshot-length",optional_argument, NULL, 's' },
  { 0,                0,                 0,     0  },
};

int main(int argc, char * const argv[]) {
  char *device = def_dev_str;
  char *filter = NULL;
  char error_buffer[PCAP_ERRBUF_SIZE];
  int opt;
  int longindex;
  pcap_t *handle;
  /* Snapshot length is how many bytes to capture from each packet. This includes*/
  int snapshot_length = 2048;
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
  while ((opt = getopt_long_only(
    argc,
    argv,
    "F::i::s::",
    longopts,
    &longindex
  )) != -1) {
    #ifdef DEBUG
      fprintf(
        stderr,
        "%d %s\n",
        longindex,
        longopts[longindex].name);
    #endif
    switch (opt) {
      case 'F':
      filter=optarg;
      break;

      /*
       * -i interface
       * --interface=interface
       *     Listen on interface.
       *     If unspecified,
       *     tcpdump searches the system interface list
       *     for the lowest numbered,
       *     configured up interface (excluding loopback),
       *     which may turn out to be, for example,
       *     ``eth0''.
       */
      case 'i':
      /* number */
      device=choice_device(atoi(argv[longindex]));
      break;

      case 's':
      snapshot_length=atoi(optarg);
      break;

      default:
      break;
    }
  }

  handle = pcap_open_live(
    device,
    snapshot_length,
    0,
    10000,
    error_buffer
  );
  pcap_loop(
    handle,
    total_packet_count,
    proxy_handler,
    my_arguments
  );

  return 0;
}
