#ifndef BYTEORDER_H
#define BYTEORDER_H

#include <pcap.h>

#define _BYTE_R_SHIFT00(x) (  x        & 0xFF)
#define _BYTE_R_SHIFT08(x) ( (x >>  8) & 0xFF)
#define _BYTE_R_SHIFT16(x) ( (x >> 16) & 0xFF)
#define _BYTE_R_SHIFT24(x) ( (x >> 24) & 0xFF)

// TODO: need?
#define _BYTE_L_SHIFT00(x) (  x        & 0xFF)
#define _BYTE_L_SHIFT08(x) ( (x <<  8) & 0xFF)
#define _BYTE_L_SHIFT16(x) ( (x << 16) & 0xFF)
#define _BYTE_L_SHIFT24(x) ( (x << 24) & 0xFF)

extern u_short ntohs_pcap(u_short netshort);

#endif
