#pragma once 

/**
 * @file esi_event.h
 * @brief "esi_event.h" provides abstraction to compose event loop
 * 
 * 
 * 
 * @author Li Weida
 * @date 2023.06.26
*/

#include "esi_arr/esi_arr.h"
#include "esi_ring/esi_ring.h"

enum esi_event_err {
    ESI_EVENT_ERR_NONE = 0,
    ESI_EVENT_ERR_EVENT_CAP = 1,
    ESI_EVENT_ERR_EVENT_ID_COLLISON = 2,
    ESI_EVENT_ERR_HANDLER_CAP = 3, 
    ESI_EVENT_ERR_HANDLER_ID_COLLISON = 4
};

#define ESI_EVENT_ERR_MSG {\
    "esi_event: ok", /*0*/\
    "esi_event_monitor: monitored events have reached capacity", /*1*/\
    "esi_event_monitor: event id collides with monitered event's", /*2*/\
    "esi_event_monitor: registered handlers have reached capacity", /*3*/\
    "esi_event_monitor: handler id collides with registered handler's" /*4*/\
}

const char *esi_event_strerror(int err);

#define ESI_TRIGGERED_EVENT_TYPE_DECL(TYPE_ALIAS, ARG_T) \
struct esi_triggered_event_##ARG_T;\
typedef struct esi_triggered_event_##ARG_T esi_triggered_event_##ARG_T##_st;\
typedef esi_triggered_event_##ARG_T##_st TYPE_ALIAS;\
typedef esi_triggered_event_##ARG_T##_st *TYPE_ALIAS##_ptr_t;\
typedef ARG_T TYPE_ALIAS##_arg_t;\
typedef ARG_T *TYPE_ALIAS##_arg_ptr_t;\
struct esi_triggered_event_##ARG_T {\
    int event_id;\
    ARG_T event_arg;\
};\
int TYPE_ALIAS##_init(TYPE_ALIAS##_ptr_t, int, TYPE_ALIAS##_arg_ptr_t);\

#define ESI_TRIGGERED_EVENT_INIT(EVENT_T, p_event, event_id, p_arg) EVENT_T##_init(p_event, event_id, p_arg)

#define ESI_TRIGGERED_EVENT_TYPE_IMPL(TYPE_ALIAS, ARG_T) \
int TYPE_ALIAS##_init(TYPE_ALIAS##_ptr_t p_event, int event_id, TYPE_ALIAS##_arg_ptr_t p_arg) {\
    p_event->event_id = event_id;\
    p_event->event_arg = *p_arg;\
    return ESI_EVENT_ERR_NONE;\
}\

#define ESI_POLLED_EVENT_TYPE_DECL(TYPE_ALIAS, ARG_T) \
struct esi_polled_event_##ARG_T;\
typedef struct esi_polled_event_##ARG_T esi_polled_event_##ARG_T##_st;\
typedef esi_polled_event_##ARG_T##_st TYPE_ALIAS;\
typedef esi_polled_event_##ARG_T##_st *TYPE_ALIAS##_ptr_t;\
typedef ARG_T TYPE_ALIAS##_arg_t;\
typedef ARG_T *TYPE_ALIAS##_arg_ptr_t;\
/* poll does two things: 1. maintain event state and invariant 2. return 1 when event occurred */\
typedef int (*TYPE_ALIAS##_poll_func_t)(TYPE_ALIAS##_ptr_t);\
struct esi_polled_event_##ARG_T {\
    int event_id;\
    ARG_T event_arg;\
    TYPE_ALIAS##_poll_func_t poll;\
};\
int TYPE_ALIAS##_init(TYPE_ALIAS##_ptr_t, int, TYPE_ALIAS##_arg_ptr_t, TYPE_ALIAS##_poll_func_t);\

#define ESI_POLLED_EVENT_INIT(EVENT_T, p_event, event_id, p_arg, poll_func) EVENT_T##_init(p_event, event_id, p_arg, poll_func)

#define ESI_POLLED_EVENT_TYPE_IMPL(TYPE_ALIAS, ARG_T) \
int TYPE_ALIAS##_init(TYPE_ALIAS##_ptr_t p_event, int event_id, TYPE_ALIAS##_arg_ptr_t p_arg, TYPE_ALIAS##_poll_func_t poll_func) {\
    p_event->event_id = event_id;\
    p_event->event_arg = *p_arg;\
    p_event->poll = poll_func;\
    return ESI_EVENT_ERR_NONE;\
}\

#define ESI_CHRONIC_EVENT_TYPE_DECL(TYPE_ALIAS, ARG_T, TIMEREF_T) \
struct esi_chronic_event_##ARG_T;\
typedef struct esi_chronic_event_##ARG_T esi_chronic_event_##ARG_T##_st;\
typedef esi_chronic_event_##ARG_T##_st TYPE_ALIAS;\
typedef esi_chronic_event_##ARG_T##_st *TYPE_ALIAS##_ptr_t;\
typedef int (*TYPE_ALIAS##_update_timeref_func_t)(TIMEREF_T *);\
typedef int (*TYPE_ALIAS##_is_timed_out_func_t)(TIMEREF_T *, TIMEREF_T *);\
typedef ARG_T TYPE_ALIAS##_arg_t;\
typedef ARG_T *TYPE_ALIAS##_arg_ptr_t;\
typedef TIMEREF_T TYPE_ALIAS##_timeref_t;\
typedef TIMEREF_T *TYPE_ALIAS##_timeref_ptr_t;\
struct esi_chronic_event_##ARG_T {\
    int event_id;\
    ARG_T event_arg;\
    TIMEREF_T last_time_stamp;\
    TIMEREF_T current_timeref;\
    TYPE_ALIAS##_update_timeref_func_t update_timeref;\
    TYPE_ALIAS##_is_timed_out_func_t is_timed_out;\
};\
int TYPE_ALIAS##_init(TYPE_ALIAS##_ptr_t, int, TYPE_ALIAS##_arg_ptr_t, TYPE_ALIAS##_update_timeref_func_t, TYPE_ALIAS##_is_timed_out_func_t);\

#define ESI_CHRONIC_EVENT_TIMEREF_T(EVENT_T) EVENT_T##_timeref_t

#define ESI_CHRONIC_EVENT_INIT(EVENT_T, p_event, event_id, p_arg, update_timeref_func, is_timed_out_func) EVENT_T##_init(p_event, event_id, p_arg, update_timeref_func, is_timed_out_func)

#define ESI_CHRONIC_EVENT_TYPE_IMPL(TYPE_ALIAS, ARG_T, TIMEREF_T) \
int TYPE_ALIAS##_init(TYPE_ALIAS##_ptr_t p_event, int event_id, TYPE_ALIAS##_arg_ptr_t p_arg, TYPE_ALIAS##_update_timeref_func_t update_timeref_func, TYPE_ALIAS##_is_timed_out_func_t is_timed_out_func) {\
    p_event->event_id = event_id;\
    p_event->event_arg = *p_arg;\
    p_event->update_timeref = update_timeref_func;\
    p_event->is_timed_out = is_timed_out_func;\
    p_event->update_timeref(&(p_event->current_timeref));\
    p_event->last_time_stamp = p_event->current_timeref;\
    return ESI_EVENT_ERR_NONE;\
}\

#define ESI_EVENT_ARG_T(EVENT_T) EVENT_T##_arg_t;

typedef void (*esi_event_handler_func_t)(void *);
struct esi_event_handler {
    int handler_id;
    int event_id;
    esi_event_handler_func_t handler_func;
};
typedef struct esi_event_handler esi_event_handler_t;
int esi_event_handler_init(esi_event_handler_t *p_handler, int handler_id, int event_id, esi_event_handler_func_t handler_func);

#define ESI_EVENT_MONITOR_TYPE_DECL(TYPE_ALIAS, TRIGGERED_EVENT_T, TRIGGERED_EVENT_CAP, POLLED_EVENT_T, POLLED_EVENT_CAP, CHRONIC_EVENT_T, CHRONIC_EVENT_CAP, HANDLER_CAP) \
struct esi_event_monitor_##TYPE_ALIAS;\
typedef struct esi_event_monitor_##TYPE_ALIAS TYPE_ALIAS;\
typedef TYPE_ALIAS *TYPE_ALIAS##_ptr_t;\
typedef esi_event_handler_func_t TYPE_ALIAS##_event_handler_func_t;\
typedef esi_event_handler_t TYPE_ALIAS##_event_handler_t;\
typedef TYPE_ALIAS##_event_handler_t *TYPE_ALIAS##_event_handler_ptr_t;\
/* supporting array and queue types */\
ESI_RING_TYPE_DECL(TYPE_ALIAS##_triggered_event_queue_t, TRIGGERED_EVENT_T, TRIGGERED_EVENT_CAP);\
ESI_ARR_TYPE_DECL(TYPE_ALIAS##_polled_event_list_t, POLLED_EVENT_T, POLLED_EVENT_CAP);\
ESI_ARR_TYPE_DECL(TYPE_ALIAS##_chronic_event_list_t, CHRONIC_EVENT_T, CHRONIC_EVENT_CAP);\
ESI_ARR_TYPE_DECL(TYPE_ALIAS##_event_handler_list_t, TYPE_ALIAS##_event_handler_t, HANDLER_CAP);\
struct esi_event_monitor_##TYPE_ALIAS {\
    TYPE_ALIAS##_triggered_event_queue_t triggered_event_queue;\
    TYPE_ALIAS##_polled_event_list_t polled_event_list;\
    TYPE_ALIAS##_chronic_event_list_t chronic_event_list;\
    TYPE_ALIAS##_event_handler_list_t event_handler_list;\
    int stop_flag;\
};\
typedef TRIGGERED_EVENT_T TYPE_ALIAS##_triggered_event_t;\
typedef TRIGGERED_EVENT_T *TYPE_ALIAS##_triggered_event_ptr_t;\
typedef POLLED_EVENT_T TYPE_ALIAS##_polled_event_t;\
typedef POLLED_EVENT_T *TYPE_ALIAS##_polled_event_ptr_t;\
typedef CHRONIC_EVENT_T TYPE_ALIAS##_chronic_event_t;\
typedef CHRONIC_EVENT_T *TYPE_ALIAS##_chronic_event_ptr_t;\
int TYPE_ALIAS##_init(TYPE_ALIAS##_ptr_t);\
int TYPE_ALIAS##_trigger_event(TYPE_ALIAS##_ptr_t, TYPE_ALIAS##_triggered_event_ptr_t);\
int TYPE_ALIAS##_register_polled_event(TYPE_ALIAS##_ptr_t, TYPE_ALIAS##_polled_event_ptr_t);\
int TYPE_ALIAS##_register_chronic_event(TYPE_ALIAS##_ptr_t, TYPE_ALIAS##_chronic_event_ptr_t);\
int TYPE_ALIAS##_register_event_handler(TYPE_ALIAS##_ptr_t, TYPE_ALIAS##_event_handler_ptr_t);\
int TYPE_ALIAS##_loop(TYPE_ALIAS##_ptr_t);\
int TYPE_ALIAS##_stop(TYPE_ALIAS##_ptr_t);\

#define ESI_EVENT_MONITOR_TRIGGERED_EVENT_QUEUE_T(MONITOR_T) MONITOR_T##_triggered_event_queue_t
#define ESI_EVENT_MONITOR_POLLED_EVENT_LIST_T(MONITOR_T) MONITOR_T##_polled_event_list_t
#define ESI_EVENT_MONITOR_CHRONIC_EVENT_LIST_T(MONITOR_T) MONITOR_T##_chronic_event_list_t

#define ESI_EVENT_MONITOR_INIT(MONITOR_T, p_monitor) MONITOR_T##_init(p_monitor)
#define ESI_EVENT_MONITOR_TRIGGER_EVENT(MONITOR_T, p_monitor, p_event) MONITOR_T##_trigger_event(p_monitor, p_event)
#define ESI_EVENT_MONITOR_REGISTER_POLLED_EVENT(MONITOR_T, p_monitor, p_event) MONITOR_T##_register_polled_event(p_monitor, p_event)
#define ESI_EVENT_MONITOR_REGISTER_CHRONIC_EVENT(MONITOR_T, p_monitor, p_event) MONITOR_T##_register_chronic_event(p_monitor, p_event)
#define ESI_EVENT_MONITOR_REGISTER_EVENT_HANDLER(MONITOR_T, p_monitor, p_handler) MONITOR_T##_register_event_handler(p_monitor, p_handler)
#define ESI_EVENT_MONITOR_LOOP(MONITOR_T, p_monitor) MONITOR_T##_loop(p_monitor)
#define ESI_EVENT_MONITOR_STOP(MONITOR_T, p_monitor) MONITOR_T##_stop(p_monitor)

#define ESI_EVENT_MONITOR_TYPE_IMPL(TYPE_ALIAS, TRIGGERED_EVENT_T, TRIGGERED_EVENT_CAP, POLLED_EVENT_T, POLLED_EVENT_CAP, CHRONIC_EVENT_T, CHRONIC_EVENT_CAP, HANDLER_CAP) \
/* supporting array and queue types implementation */\
static int TRIGGERED_EVENT_T##_eq(TRIGGERED_EVENT_T *, TRIGGERED_EVENT_T *);\
static int TRIGGERED_EVENT_T##_eq(TRIGGERED_EVENT_T * p_event1, TRIGGERED_EVENT_T * p_event2) {\
    return p_event1->event_id == p_event2->event_id;\
}\
ESI_RING_TYPE_IMPL_WITH_EQ(TYPE_ALIAS##_triggered_event_queue_t, TRIGGERED_EVENT_T, TRIGGERED_EVENT_CAP, TRIGGERED_EVENT_T##_eq);\
static int POLLED_EVENT_T##_eq(POLLED_EVENT_T *, POLLED_EVENT_T *);\
static int POLLED_EVENT_T##_eq(POLLED_EVENT_T * p_event1, POLLED_EVENT_T * p_event2) {\
    return p_event1->event_id == p_event2->event_id;\
}\
ESI_ARR_TYPE_IMPL_WITH_EQ(TYPE_ALIAS##_polled_event_list_t, POLLED_EVENT_T, POLLED_EVENT_CAP, POLLED_EVENT_T##_eq);\
static int CHRONIC_EVENT_T##_eq(CHRONIC_EVENT_T *, CHRONIC_EVENT_T *);\
static int CHRONIC_EVENT_T##_eq(CHRONIC_EVENT_T * p_event1, CHRONIC_EVENT_T * p_event2) {\
    return p_event1->event_id == p_event2->event_id;\
}\
ESI_ARR_TYPE_IMPL_WITH_EQ(TYPE_ALIAS##_chronic_event_list_t, CHRONIC_EVENT_T, CHRONIC_EVENT_CAP, CHRONIC_EVENT_T##_eq);\
static int TYPE_ALIAS##_event_handler_t##_eq(TYPE_ALIAS##_event_handler_t *, TYPE_ALIAS##_event_handler_t *);\
static int TYPE_ALIAS##_event_handler_t##_eq(TYPE_ALIAS##_event_handler_t * p_handler1, TYPE_ALIAS##_event_handler_t * p_handler2) {\
    return p_handler1->handler_id == p_handler2->handler_id;\
}\
ESI_ARR_TYPE_IMPL_WITH_EQ(TYPE_ALIAS##_event_handler_list_t, TYPE_ALIAS##_event_handler_t, HANDLER_CAP, TYPE_ALIAS##_event_handler_t##_eq);\
int TYPE_ALIAS##_init(TYPE_ALIAS##_ptr_t p_monitor) {\
    p_monitor->triggered_event_queue.head = 0;\
    p_monitor->triggered_event_queue.tail = 0;\
    p_monitor->polled_event_list.size = 0;\
    p_monitor->chronic_event_list.size = 0;\
    p_monitor->event_handler_list.size = 0;\
    p_monitor->stop_flag = 0;\
    return ESI_EVENT_ERR_NONE;\
}\
static int TYPE_ALIAS##_preset_event_id;\
static int TYPE_ALIAS##_polled_event_id_equal_preset_one(TYPE_ALIAS##_polled_event_ptr_t);\
static int TYPE_ALIAS##_polled_event_id_equal_preset_one(TYPE_ALIAS##_polled_event_ptr_t p_event) {\
    return p_event->event_id == TYPE_ALIAS##_preset_event_id;\
}\
static int TYPE_ALIAS##_chronic_event_id_equal_preset_one(TYPE_ALIAS##_chronic_event_ptr_t);\
static int TYPE_ALIAS##_chronic_event_id_equal_preset_one(TYPE_ALIAS##_chronic_event_ptr_t p_event) {\
    return p_event->event_id == TYPE_ALIAS##_preset_event_id;\
}\
int TYPE_ALIAS##_trigger_event(TYPE_ALIAS##_ptr_t p_monitor, TYPE_ALIAS##_triggered_event_ptr_t p_event) {\
    if (ESI_RING_IS_FULL(TYPE_ALIAS##_triggered_event_queue_t, &(p_monitor->triggered_event_queue))) {\
        return ESI_EVENT_ERR_EVENT_CAP;\
    }\
    ESI_RING_PUSH_BACK(TYPE_ALIAS##_triggered_event_queue_t, &(p_monitor->triggered_event_queue), p_event);\
    return ESI_EVENT_ERR_NONE;\
}\
int TYPE_ALIAS##_register_polled_event(TYPE_ALIAS##_ptr_t p_monitor, TYPE_ALIAS##_polled_event_ptr_t p_event) {\
    if (ESI_ARR_IS_FULL(TYPE_ALIAS##_polled_event_list_t, &(p_monitor->polled_event_list))) {\
        return ESI_EVENT_ERR_EVENT_CAP;\
    }\
    TYPE_ALIAS##_preset_event_id = p_event->event_id;\
    if (ESI_ARR_ANY(TYPE_ALIAS##_polled_event_list_t, &(p_monitor->polled_event_list), TYPE_ALIAS##_polled_event_id_equal_preset_one)) {\
        return ESI_EVENT_ERR_EVENT_ID_COLLISON;\
    }\
    ESI_ARR_APPEND(TYPE_ALIAS##_polled_event_list_t, &(p_monitor->polled_event_list), p_event);\
    return ESI_EVENT_ERR_NONE;\
}\
int TYPE_ALIAS##_register_chronic_event(TYPE_ALIAS##_ptr_t p_monitor, TYPE_ALIAS##_chronic_event_ptr_t p_event) {\
    if (ESI_ARR_IS_FULL(TYPE_ALIAS##_chronic_event_list_t, &(p_monitor->chronic_event_list))) {\
        return ESI_EVENT_ERR_EVENT_CAP;\
    }\
    TYPE_ALIAS##_preset_event_id = p_event->event_id;\
    if (ESI_ARR_ANY(TYPE_ALIAS##_chronic_event_list_t, &(p_monitor->chronic_event_list), TYPE_ALIAS##_chronic_event_id_equal_preset_one)) {\
        return ESI_EVENT_ERR_EVENT_ID_COLLISON;\
    }\
    ESI_ARR_APPEND(TYPE_ALIAS##_chronic_event_list_t, &(p_monitor->chronic_event_list), p_event);\
    return ESI_EVENT_ERR_NONE;\
}\
static int TYPE_ALIAS##_preset_handler_id;\
static int TYPE_ALIAS##_handler_id_equal_preset_one(TYPE_ALIAS##_event_handler_ptr_t);\
static int TYPE_ALIAS##_handler_id_equal_preset_one(TYPE_ALIAS##_event_handler_ptr_t p_handler) {\
    return p_handler->handler_id == TYPE_ALIAS##_preset_handler_id;\
}\
int TYPE_ALIAS##_register_event_handler(TYPE_ALIAS##_ptr_t p_monitor, TYPE_ALIAS##_event_handler_ptr_t p_handler) {\
    if (ESI_ARR_IS_FULL(TYPE_ALIAS##_event_handler_list_t, &(p_monitor->event_handler_list))) {\
        return ESI_EVENT_ERR_HANDLER_CAP;\
    }\
    TYPE_ALIAS##_preset_handler_id = p_handler->handler_id;\
    if (ESI_ARR_ANY(TYPE_ALIAS##_event_handler_list_t, &(p_monitor->event_handler_list), TYPE_ALIAS##_handler_id_equal_preset_one)) {\
        return ESI_EVENT_ERR_HANDLER_ID_COLLISON;\
    }\
    ESI_ARR_APPEND(TYPE_ALIAS##_event_handler_list_t, &(p_monitor->event_handler_list), p_handler);\
    return ESI_EVENT_ERR_NONE;\
}\
/* supporting inner function for looping over triggered event queue */\
static int TYPE_ALIAS##_call_handler_event_id;\
static void *TYPE_ALIAS##_call_handler_event_holder;\
static void TYPE_ALIAS##_call_handler(int, TYPE_ALIAS##_event_handler_ptr_t);\
static void TYPE_ALIAS##_call_handler(int index, TYPE_ALIAS##_event_handler_ptr_t p_handler) {\
    if (p_handler->event_id == TYPE_ALIAS##_call_handler_event_id) {\
        p_handler->handler_func(TYPE_ALIAS##_call_handler_event_holder);\
    }\
}\
/* supporting inner function for looping over polled event list */\
static TYPE_ALIAS##_event_handler_list_t *TYPE_ALIAS##_poll_and_handle_handler_list;\
static void TYPE_ALIAS##_poll_and_handle(int, TYPE_ALIAS##_polled_event_ptr_t);\
static void TYPE_ALIAS##_poll_and_handle(int index, TYPE_ALIAS##_polled_event_ptr_t p_event) {\
    if (p_event->poll(p_event)) {\
        TYPE_ALIAS##_call_handler_event_holder = (void *) p_event;\
        TYPE_ALIAS##_call_handler_event_id = p_event->event_id;\
        ESI_ARR_FOR_EACH_ELEM(TYPE_ALIAS##_event_handler_list_t, TYPE_ALIAS##_poll_and_handle_handler_list, TYPE_ALIAS##_call_handler);\
    }\
}\
static TYPE_ALIAS##_event_handler_list_t *TYPE_ALIAS##_handle_chronic_event_handler_list;\
static void TYPE_ALIAS##_handle_chronic_event(int, TYPE_ALIAS##_chronic_event_ptr_t);\
static void TYPE_ALIAS##_handle_chronic_event(int index, TYPE_ALIAS##_chronic_event_ptr_t p_event) {\
    /* update timeref, determine whether timed out */\
    p_event->update_timeref(&(p_event->current_timeref));\
    if (p_event->is_timed_out(&(p_event->current_timeref), &(p_event->last_time_stamp))) {\
        p_event->last_time_stamp = p_event->current_timeref;\
        TYPE_ALIAS##_call_handler_event_holder = (void *) p_event;\
        TYPE_ALIAS##_call_handler_event_id = p_event->event_id;\
        ESI_ARR_FOR_EACH_ELEM(TYPE_ALIAS##_event_handler_list_t, TYPE_ALIAS##_handle_chronic_event_handler_list, TYPE_ALIAS##_call_handler);\
    }\
}\
int TYPE_ALIAS##_loop(TYPE_ALIAS##_ptr_t p_monitor) {\
    while (p_monitor->stop_flag == 0) {\
        /* handle triggered events */\
        while (!ESI_RING_IS_EMPTY(TYPE_ALIAS##_triggered_event_queue_t, &(p_monitor->triggered_event_queue))) {\
            TYPE_ALIAS##_call_handler_event_holder = (void *) &(ESI_RING_PEEK_FRONT(TYPE_ALIAS##_triggered_event_queue_t, &(p_monitor->triggered_event_queue)));\
            TYPE_ALIAS##_call_handler_event_id = ESI_RING_PEEK_FRONT(TYPE_ALIAS##_triggered_event_queue_t, &(p_monitor->triggered_event_queue)).event_id;\
            ESI_ARR_FOR_EACH_ELEM(TYPE_ALIAS##_event_handler_list_t, &(p_monitor->event_handler_list), TYPE_ALIAS##_call_handler);\
            ESI_RING_POP_FRONT(TYPE_ALIAS##_triggered_event_queue_t, &(p_monitor->triggered_event_queue));\
        }\
        /* poll polled events and handle if needed */\
        TYPE_ALIAS##_poll_and_handle_handler_list = &(p_monitor->event_handler_list);\
        ESI_ARR_FOR_EACH_ELEM(TYPE_ALIAS##_polled_event_list_t, &(p_monitor->polled_event_list), TYPE_ALIAS##_poll_and_handle);\
        /* update timeref for chronic events and handle if needed */\
        TYPE_ALIAS##_handle_chronic_event_handler_list = &(p_monitor->event_handler_list);\
        ESI_ARR_FOR_EACH_ELEM(TYPE_ALIAS##_chronic_event_list_t, &(p_monitor->chronic_event_list), TYPE_ALIAS##_handle_chronic_event);\
    }\
    return ESI_EVENT_ERR_NONE;\
}\
int TYPE_ALIAS##_stop(TYPE_ALIAS##_ptr_t p_monitor) {\
    p_monitor->stop_flag = 1;\
    return ESI_EVENT_ERR_NONE;\
}