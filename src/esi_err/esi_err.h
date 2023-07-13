#pragma once 

/**
 * @file esi_err.h
 * @brief this module provides unified error code encoding and decoding 
 * mechanism
 * 
 * we define "esi_err = esi_err_src :: esi_err_status"
 * 
 * @author Li Weida
 * @date 2023.05.17
*/

/**
 * the definition of `esi_err_t` can be adjusted according custome needs
 * the only assumption is that, it should be of integeral type
*/
typedef /* custome definition */ int esi_err_t;

/**
 * the following macros can be adjusted according to the underlying platform 
 * and application
*/
#define ESI_ERR_SRC_WIDTH (8)
#define ESI_ERR_STATUS_WIDTH (8)
#define ESI_ERR_SRC(src_id) ((src_id) << (ESI_ERR_STATUS_WIDTH))
#define ESI_ERR_STATUS(status_id) (status_id)
#define ESI_ERR(src_id, status_id) (ESI_ERR_SRC(src_id) | ESI_ERR_STATUS(status_id))
#define ESI_ERR_SRC_PART(err) ((err) >> ESI_ERR_STATUS_WIDTH)
#define ESI_ERR_STATUS_PART(err) (err & ((1 << ESI_ERR_STATUS_WIDTH) - 1))

/**
 * please add custome "err_src" and "err_status" below
 * note that `ESI_ERR_SRC_NONE` and `ESI_ERR_STATUS_NONE` is required and must
 * be zero
*/
enum esi_err_src {
    ESI_ERR_SRC_NONE = 0
};

#define ESI_ERR_SRC_MSG {\
    "none"\
}

enum esi_err_status {
    ESI_ERR_STATUS_NONE = 0
};

#define ESI_ERR_STATUS_MSG {\
    "none"\
}

/**
 * @breif fhesi version of standard library `strerror`
 * 
 * this function uses a static buffer, so it's neither thread-safe or 
 * reentrant.
*/
const char *esi_strerror(esi_err_t err);

/**
 * you can customized the size of the static buffer used by `esi_strerror`
*/
#define ESI_STRERROR_BUFSIZE /* customized buffer size */ (128)