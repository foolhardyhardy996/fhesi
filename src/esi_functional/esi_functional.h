#pragma once 

/**
 * @file esi_functional.h
 * @brief common functional utilities
 * 
 * 
 * 
 * @author Li Weida
 * @date 2023.07.26
*/

#define ESI_ASSIGN_FUNC_T(obj_t, var) void (*var)(obj_t *, obj_t *)
#define ESI_MAP_FUNC_T(obj_t, var) void (*var)(obj_t *, obj_t *)
#define ESI_PREDICATE_T(obj_t, var) int (*var)(obj_t *)
#define ESI_MODIFY_FUNC_T(obj_t, var) void (*var)(obj_t *)
#define ESI_LITERAL_BIOP_FUNC_T(arg1_t, arg2_t, res_t, var) res_t (*var)(arg1_t, arg2_t)
#define ESI_LITERAL_UNIOP_FUNC_T(arg_t, res_t, var) res_t (*var)(arg_t)
#define ESI_BIOP_FUNC_T(arg1_t, arg2_t, res_t, var) void (*var)(arg1_t *, arg2_t *, res_t *)
#define ESI_UNIOP_FUNC_T(arg_t, res_t, var) void (*var)(arg_t *, res_t *)
