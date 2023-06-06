#pragma once 

/**
 * @file esi_platform_info.h
 * @brief "esi_platform_info" provide vendor information about the platform
 * 
 * This file serves as wrapper for the concrete platform info. Please 
 * include the concrete info header for your platform below.
 * 
 * @author Li Weida
 * @date 2023.05.26
*/

/* Add your platform info macros in the concrete platform info header */
/* For example, #include "esi_platform_info_myplatform.h" */


/* The following test macros serve as reminders */
#ifndef ESI_PLATFORM_NAME
#error "ESI_PLATFORM_NAME is required, please define it in esi_platform_info.h"
#endif

#ifndef ESI_PLATFORM_VERSION
#error "ESI_PLATFORM_VERSION is required, please define it in esi_platform_info.h"
#endif
