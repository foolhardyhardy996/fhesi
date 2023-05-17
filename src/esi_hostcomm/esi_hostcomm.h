#pragma once 

/**
 * @file esi_hostcomm.h
 * @brief this module encapsulate the communication mechanism between device 
 * and host machine
 * 
 * 
 * 
 * @author Li Weida
 * @date 2023.5.17
*/

struct esi_hostcomm_ops {
    int (*open)(struct esi_hostcomm *hostcomm, void *arg);
    int (*close)(struct esi_hostcomm *hostcomm);
    int (*rx_ready)(struct esi_hostcomm *hostcomm);
    int (*tx_ready)(struct esi_hostcomm *hostcomm);
    int (*send)(struct esi_hostcomm *hostcomm, unsigned char *buf, int len);
    int (*recv)(struct esi_hostcomm *hostcomm, unsigned char *buf, int cap);
};

struct esi_hostcomm {
    /**< the blob hides the detail of the concrete host communication 
     * mechanism*/
    void *hostcomm_struct;

    struct esi_hostcomm_ops *ops;
};
