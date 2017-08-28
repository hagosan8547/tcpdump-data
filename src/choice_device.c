#include "tcpdump-data.h"

#define DEBUG

char *choice_device(
  int device_num
) {
  pcap_if_t *alldevs;
  pcap_if_t *d;
  int i=0;
  int select=device_num;
  char errbuf[PCAP_ERRBUF_SIZE];

  #ifdef DEBUG
  fprintf(stderr, "choice_device:%d,%d\n",i,select);
  #endif

  if (pcap_findalldevs(&alldevs,errbuf) == -1) {
    fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
    return 0;
  }
  // non select
  if (select <= 0) {

    #ifdef DEBUG
    fprintf(stderr, "device_select\n");
    #endif

    /*
    for (d = alldevs; d; d=d->next) {
      fprintf(stderr,"%d %s", ++i, d->name);
      if (d->description) {
        fprintf(stderr," (%s)\n", d->description);
      } else {
        fprintf(stderr," (No description available)\n");
      }
    }
    */
    i=print_device(alldevs);

    if(i==0)
    {
      fprintf(stderr,"\nNo interfaces found! Make sure WinPcap is installed.\n");
      return 0;
    }

    fprintf(stderr, "Enter the interface number (1-%d): ",i);
    scanf("%d", &select);
  }

  #ifdef DEBUG
  fprintf(stderr,"device_choice\n");
  #endif

  i=0;
  for (d = alldevs; i<(select-1); d=d->next){
    #ifdef DEBUG
    fprintf(stderr,"device: %s\n", d->name);
    #endif
    i++;
  }
  #ifdef DEBUG
  fprintf(stderr,"device: %s\n", d->name);
  #endif
  return d->name;
}
