#pragma once 

/**
 * @file esi_err.h
 * @brief this module provides unified error code encoding and decoding
 * 
 * 
 * 
 * @author Li Weida
 * @date 2023.05.17
*/

#define ESI_ERR_SRC_WIDTH (8)
#define ESI_ERR_STATUS_WIDTH (16)
#define ESI_ERR_SRC(src_id) ((src_id) << (ESI_ERR_STATUS_WIDTH))
#define ESI_ERR_STATUS(status_id) (status_id)
#define ESI_ERR(src_id, status_id) (ESI_ERR_SRC(src_id) | ESI_ERR_STATUS(status_id))
#define ESI_ERR2SRC(err) ((err) >> ESI_ERR_STATUS_WIDTH)
#define ESI_ERR2STATUS(err) (err & ((1 << ESI_ERR_STATUS_WIDTH) - 1))

enum esi_err_src {
    ESI_ERR_SRC_NONE = 0
};

static const char *esi_err_src_msg[] = {
    "none"
};

enum esi_err_status {
    ESI_ERR_STATUS_NONE = 0
};

static const char *esi_err_status_msg[] = {
    "none"
};

const char *esi_strerror(int err);