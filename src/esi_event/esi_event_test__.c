#include "esi_event.h"

#include <stdio.h>
#include <time.h>

ESI_TRIGGERED_EVENT_TYPE_DECL(my_tevent_t, int);
ESI_TRIGGERED_EVENT_TYPE_IMPL(my_tevent_t, int);

ESI_POLLED_EVENT_TYPE_DECL(my_pevent_t, int);
ESI_POLLED_EVENT_TYPE_IMPL(my_pevent_t, int);

ESI_CHRONIC_EVENT_TYPE_DECL(my_cevent_t, int, size_t);
ESI_CHRONIC_EVENT_TYPE_IMPL(my_cevent_t, int, size_t);

ESI_EVENT_MONITOR_TYPE_DECL(my_monitor_t, my_tevent_t, 5, my_pevent_t, 5, my_cevent_t, 5, 10);
ESI_EVENT_MONITOR_TYPE_IMPL(my_monitor_t, my_tevent_t, 5, my_pevent_t, 5, my_cevent_t, 5, 10);

static my_monitor_t monitor;

#define TEVENT_STOP_ID 1
#define TEVENT_BARK_ID 2

#define PEVENT_FLAGCHECK_ID 3

#define CEVENT_FLAGSET_ID 4
#define CEVENT_CLOSE_ID 5

static my_tevent_t tevent_stop, tevent_bark;
static my_pevent_t pevent_flagcheck;
static my_cevent_t cevent_flagset, cevent_close;

static int event_flag;

#define HANDLER_STOP_ID 1
#define HANDLER_BARK1_ID 2
#define HANDLER_BARK2_ID 3
#define HANDLER_FLAGCHECK_ID 4
#define HANDLER_FLAGSET_ID 5
#define HANDLER_CLOSE_ID 6

static esi_event_handler_t handler_stop, handler_bark1, handler_bark2, handler_flagcheck, handler_flagset, handler_close;

static void handle_stop(void *);
static void handle_stop(void *event_holder) {
    my_tevent_t *p_event = (my_tevent_t *) event_holder;

    p_event->event_arg++;
    printf("[INFO]: handling stop for %d times\n", p_event->event_arg);
    ESI_EVENT_MONITOR_STOP(my_monitor_t, &monitor);
}

static void handle_bark1(void *);
static void handle_bark1(void *event_holder) {
    my_tevent_t *p_event = (my_tevent_t *) event_holder;

    p_event->event_arg++;
    printf("[INFO]: handling bark for %d times, it's bark1\n", p_event->event_arg);
}

static void handle_bark2(void *);
static void handle_bark2(void *event_holder) {
    my_tevent_t *p_event = (my_tevent_t *) event_holder;

    p_event->event_arg++;
    printf("[INFO]: handling bark for %d times, it's bark2\n", p_event->event_arg);
}

static int poll_flag(my_pevent_t *);
static int poll_flag(my_pevent_t *p_event) {
    return event_flag;
}

static void handle_flagcheck(void *);
static void handle_flagcheck(void *event_holder) {
    my_pevent_t *p_event = (my_pevent_t *) event_holder;

    p_event->event_arg++;
    event_flag = 0;
    ESI_EVENT_MONITOR_TRIGGER_EVENT(my_monitor_t, &monitor, &tevent_bark);
    printf("[INFO]: handling flagcheck for %d times\n", p_event->event_arg);
}

static int update_timeref_for_flagset(size_t *);
static int update_timeref_for_flagset(size_t *timeref) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    *timeref = ts.tv_sec;
    return 0;
}

static int is_timed_out_for_flagset(size_t *, size_t *);
static int is_timed_out_for_flagset(size_t *timeref1, size_t *timeref2) {
    return (*timeref1 - *timeref2) >= 2;
}

static void handle_flagset(void *);
static void handle_flagset(void *event_holder) {
    my_cevent_t *p_event = (my_cevent_t *) event_holder;

    p_event->event_arg++;
    event_flag = 1;
    ESI_EVENT_MONITOR_TRIGGER_EVENT(my_monitor_t, &monitor, &tevent_bark);
    printf("[INFO]: handling flagset for %d times\n", p_event->event_arg);
}

static int update_timeref_for_close(size_t *);
static int update_timeref_for_close(size_t *timeref) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    *timeref = ts.tv_sec;
    return 0;
}

static int is_timed_out_for_close(size_t *, size_t *);
static int is_timed_out_for_close(size_t *timeref1, size_t *timeref2) {
    return (*timeref1 - *timeref2) >= 15;
}

static void handle_close(void *);
static void handle_close(void *event_holder) {
    my_cevent_t *p_event = (my_cevent_t *) event_holder;

    p_event->event_arg++;
    ESI_EVENT_MONITOR_TRIGGER_EVENT(my_monitor_t, &monitor, &tevent_stop);
    printf("[INFO]: handling close for %d times\n", p_event->event_arg);
}

static int init_test(void);
static int init_test(void) {
    int counter = 0;

    event_flag = 0;

    ESI_TRIGGERED_EVENT_INIT(my_tevent_t, &tevent_stop, TEVENT_STOP_ID, &counter);
    ESI_TRIGGERED_EVENT_INIT(my_tevent_t, &tevent_bark, TEVENT_BARK_ID, &counter);

    ESI_POLLED_EVENT_INIT(my_pevent_t, &pevent_flagcheck, PEVENT_FLAGCHECK_ID, &counter, poll_flag);
    
    ESI_CHRONIC_EVENT_INIT(my_cevent_t, &cevent_flagset, CEVENT_FLAGSET_ID, &counter, update_timeref_for_flagset, is_timed_out_for_flagset);
    ESI_CHRONIC_EVENT_INIT(my_cevent_t, &cevent_close, CEVENT_CLOSE_ID, &counter, update_timeref_for_close, is_timed_out_for_close);

    esi_event_handler_init(&handler_stop, HANDLER_STOP_ID, TEVENT_STOP_ID, handle_stop);
    esi_event_handler_init(&handler_bark1, HANDLER_BARK1_ID, TEVENT_BARK_ID, handle_bark1);
    esi_event_handler_init(&handler_bark2, HANDLER_BARK2_ID, TEVENT_BARK_ID, handle_bark2);
    esi_event_handler_init(&handler_flagcheck, HANDLER_FLAGCHECK_ID, PEVENT_FLAGCHECK_ID, handle_flagcheck);
    esi_event_handler_init(&handler_flagset, HANDLER_FLAGSET_ID, CEVENT_FLAGSET_ID, handle_flagset);
    esi_event_handler_init(&handler_close, HANDLER_CLOSE_ID, CEVENT_CLOSE_ID, handle_close);

    ESI_EVENT_MONITOR_INIT(my_monitor_t, &monitor);
    ESI_EVENT_MONITOR_REGISTER_POLLED_EVENT(my_monitor_t, &monitor, &pevent_flagcheck);
    ESI_EVENT_MONITOR_REGISTER_CHRONIC_EVENT(my_monitor_t, &monitor, &cevent_flagset);
    ESI_EVENT_MONITOR_REGISTER_CHRONIC_EVENT(my_monitor_t, &monitor, &cevent_close);

    ESI_EVENT_MONITOR_REGISTER_EVENT_HANDLER(my_monitor_t, &monitor, &handler_stop);
    ESI_EVENT_MONITOR_REGISTER_EVENT_HANDLER(my_monitor_t, &monitor, &handler_bark1);
    ESI_EVENT_MONITOR_REGISTER_EVENT_HANDLER(my_monitor_t, &monitor, &handler_bark2);
    ESI_EVENT_MONITOR_REGISTER_EVENT_HANDLER(my_monitor_t, &monitor, &handler_flagcheck);
    ESI_EVENT_MONITOR_REGISTER_EVENT_HANDLER(my_monitor_t, &monitor, &handler_flagset);
    ESI_EVENT_MONITOR_REGISTER_EVENT_HANDLER(my_monitor_t, &monitor, &handler_close);

    return 0;
}

int main(int argc, char *argv[]) {
    init_test();
    ESI_EVENT_MONITOR_LOOP(my_monitor_t, &monitor);
    printf("[INFO]: everything is fine\n");

    return 0;
}