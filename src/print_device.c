#include "tcpdump-data.h"

int print_device(
  pcap_if_t *alldevs
) {
  pcap_if_t *d;
  int i=0;

  for (d = alldevs; d; d=d->next) {
    fprintf(stderr,"%d %s", ++i, d->name);
    if (d->description) {
      fprintf(stderr," (%s)\n", d->description);
    } else {
      fprintf(stderr," (No description available)\n");
    }
  }

  return i;
}
