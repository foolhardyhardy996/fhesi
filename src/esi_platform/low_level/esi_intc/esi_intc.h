#pragma once 

/**
 * @file esi_intc.h
 * @brief "esi_intc" provides a unified set of interfaces for interrupt controller.
 * 
 * The optional features should be enabled or disabled in platform specific 
 * "esi_intc" header. The implementation of these interfaces should be provided 
 * by platform specific code.
 * 
 * @author Li Weida
 * @date 2023.06.06
 * 
*/

#include "esi_common/esi_err/esi_err.h"

/**
 * !!! Please include platform specific `esi_intc` header here
 * It should contain optional feature enable/disable macros
 * 
 * For example:
 * #include "esi_intc_myplatform.h"
 * 
*/

/**
 * @brief we use different values of `esi_irq_t` to identify different IRQ.
 * 
 * The mapping between `esi_irq_t` values to concrete IRQ implementation is 
 * implementation defined. If there are more one interrupt controllers in 
 * the system, or there are more than one kinds of interrupts, their semantics 
 * are implemented by functions, not `esi_irq_t` values.
 * 
*/
typedef int esi_irq_t;

/**
 * IRQs are referred by the following macros, they are of `esi_irq_t` type:
 * ESI_IRQ1
 * ESI_IRQ2
 * ...
*/

/**
 * @brief `esi_isr_t` is the function type for interrupt handler.
 * 
 * When installing ISR, user should provides both a function of type 
 * `esi_isr_t` and a value of type `void *`.
 * 
*/
typedef void (*esi_isr_t)(esi_irq_t, void *);

esi_irq_t esi_intc_get_irq_num(void);

esi_irq_t esi_intc_get_irq_by_id(int id);

esi_err_t esi_intc_install_isr(esi_irq_t irq, esi_isr_t isr, void *arg);

esi_err_t esi_intc_get_status(esi_irq_t irq, void *status);

int esi_intc_is_pending(esi_irq_t irq);

esi_err_t esi_intc_clear_pending(esi_irq_t irq);

esi_err_t esi_intc_config(void *arg);

#ifdef ESI_INTC_MASKING_AVAILABLE
esi_err_t esi_intc_mask(esi_irq_t irq);

esi_err_t esi_intc_unmask(esi_irq_t irq);
#endif

#ifdef ESI_INTC_PRIORITY_AVAILABLE
int esi_intc_get_prio_levels(void);
esi_err_t esi_intc_set_prio(esi_irq_t irq, int prio);
#endif

