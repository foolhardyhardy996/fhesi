#pragma once 

/**
 * @file esi_err_test.h
 * @brief this file is adapted from "esi_err.h" for the purpose of testing
 * 
 * we define "esi_err = esi_err_src :: esi_err_status"
 * 
 * @author Li Weida
 * @date 2023.05.30
*/

#include <stdint.h>

/**
 * the definition of `esi_err_t` can be adjusted according custome needs
 * the only assumption is that, it should be of integeral type
*/
typedef uint32_t esi_err_t;

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
    ESI_ERR_SRC_NONE = 0,
    ESI_ERR_SRC_PART1 = 1,
    ESI_ERR_SRC_PART2 = 2,
    ESI_ERR_SRC_PART3 = 3
};

#define ESI_ERR_SRC_MSG {\
    "none", /*0*/\
    "component1", /*1*/\
    "component2", /*2*/\
    "component3"  /*3*/\
}

enum esi_err_status {
    ESI_ERR_STATUS_NONE = 0,
    ESI_ERR_STATUS_BUSSY = 1,
    ESI_ERR_STATUS_DEAD = 2, 
    ESI_ERR_STATUS_DEFUNCT = 3, 
    ESI_ERR_STATUS_WRONGPARAM = 4
};

#define ESI_ERR_STATUS_MSG {\
    "none", /*0*/\
    "bussy, try again", /*1*/\
    "dead, please inform administrator", /*2*/\
    "defunct, please try fixing", /*3*/\
    "wrong parameter, please check interface doc" /*4*/\
}

/**
 * @breif fhesi version of standard library `strerror`
*/
const char *esi_strerror(esi_err_t err);

/**
 * you can customized the size of the static buffer used by `esi_strerror`
*/
#define ESI_STRERROR_BUFSIZE /* customized buffer size */ (128)