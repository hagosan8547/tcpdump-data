#include "byteorder.h"

u_short ntohs_pcap(u_short netshort){
    return ((u_short)( _BYTE_R_SHIFT00(netshort) << 8 | _BYTE_R_SHIFT08(netshort)));
}
