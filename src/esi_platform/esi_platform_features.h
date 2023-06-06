#pragma once 

/**
 * @file esi_platform_features.h
 * @brief this module provides feature test macros for components available 
 * on this platform
 * 
 * This file serves as wrapper for the concrete platform features. Please 
 * include the concrete feature header for your platform below. 
 * 
 * @author Li Weida
 * @date 2023.05.26
*/

/* Add the feature test macros in the concrete implementation for your platform */
/** 
 * Possible features currently supported by fhesi:
 * ESI_PLATFORM_FEATURES_UART_AVAILABLE
 * 
*/

/**
 * for example
 * #include "esi_platform_features_myplatform.h"
*/

/**
 * this test macro serves as an reminder
*/
#ifndef ESI_PLATFORM_FEATURES_DEFINED
#error "Please provide feature test macros for this platform."
#endif 