#pragma once 

/**
 * @file esi_pktchan.h
 * @brief "esi_pktchan.h" provides abstraction for paket based communication channel
 * 
 * 
 * 
 * @author Li Weida
 * @date 2023.07.19
*/

#include "esi_iointerface/esi_iointerface.h"

struct esi_pktchan;
typedef struct esi_pktchan esi_pktchan_t;
struct esi_pktchan {
    void *blob;
    int (*get_pkt_max_len)(esi_pktchan_t *);
    int (*is_ready_to_send)(esi_pktchan_t *);
    int (*send)(esi_pktchan_t *, esi_io_buf_wrapper_t *);
    int (*is_ready_to_recv)(esi_pktchan_t *);
    int (*recv)(esi_pktchan_t *, esi_io_buf_wrapper_t *);
};