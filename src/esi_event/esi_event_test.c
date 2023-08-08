#include "esi_event.h"

#include <stdio.h>
#include <stdint.h>
#include "esi_str/esi_str.h"

ESI_CHANGE_EVENT_DECL(usr_enter_event_t, int, int)
ESI_CHANGE_EVENT_IMPL(usr_enter_event_t, int, int)
ESI_TIME_EVENT_DECL(termination_event_t, int, int)
ESI_TIME_EVENT_IMPL(termination_event_t, int, int)
typedef char byte256_t[256];
ESI_EMSG_DECL(byte256_emsg_t, byte256_t)
ESI_EMSG_EVENT_DECL(echo_event_t, int, byte256_emsg_t)
ESI_EMSG_EVENT_IMPL(echo_event_t, int, byte256_emsg_t)

#define TEST_EVTMON_EVENT_CAP (16)
#define TEST_EVTMON_EMSG_CAP (16)
ESI_EVENTMON_DECL(test_evtmon_t, usr_enter_event_t, termination_event_t, echo_event_t, TEST_EVTMON_EVENT_CAP, TEST_EVTMON_EMSG_CAP)
ESI_EVENTMON_IMPL(test_evtmon_t, usr_enter_event_t, termination_event_t, echo_event_t, TEST_EVTMON_EVENT_CAP, TEST_EVTMON_EMSG_CAP)

static test_evtmon_t evtmon;
static usr_enter_event_t usr_enter_event;
static termination_event_t termination_event;
static echo_event_t echo_event;
static int usr_enter_event_id = -1;
static int termination_event_id = -1;
static int echo_event_id = -1;

static int usr_enter_event_poll(usr_enter_event_t *);
static int usr_enter_event_poll(usr_enter_event_t *self) {
    uint8_t buffer[128];
    self->blob++;
    printf("[NOTICE]: enter whether there is avaliable input (Y/N)\n");
    scanf("%s", buffer);
    if (strcmp((const char *) buffer, "y") == 0 || strcmp((const char *) buffer, "Y") == 0) {
        return 1;
    } else {
        printf("[INFO]: you entered \"%s\", which is interpreted as N\n", buffer);
        return 0;
    }
}

static void usr_enter_event_notify(usr_enter_event_t *, int *);
static void usr_enter_event_notify(usr_enter_event_t *self, int *noti) {
    printf("[INFO]: notify usr_enter_event\n");
    *noti = self->blob;
}

static void receive_user_input(usr_enter_event_t *, int *);
static void receive_user_input(usr_enter_event_t *e, int *noti) {
    byte256_emsg_t emsg;
    int ret;
    printf("[INFO]: handling usr_enter_event, notification = %d\n", *noti);
    scanf("%s", emsg.noti);
    while (strcmp(emsg.noti, "q") != 0) {
        emsg.event_id = echo_event_id;
        ret = test_evtmon_t_addMessage(&evtmon, &emsg);
        if (ret != 0) {
            printf("[ERROR]: fail to add message: %s\n", esi_event_strerror(ret));
        } else {
            printf("[INFO]: add message: %s\n", emsg.noti);
        }
        scanf("%s", emsg.noti);
    }
    printf("[INFO]: finish receiving user input\n");
}

static void termination_event_update(termination_event_t *);
static void termination_event_update(termination_event_t *self) {
    self->blob++;
}

static int termination_event_check(termination_event_t *);
static int termination_event_check(termination_event_t *self) {
    printf("[INFO]: checking counter, counter = %d\n", self->blob);
    if (self->blob >= 5) {
        return 1;
    } else {
        return 0;
    }
}

static void termination_event_notify(termination_event_t *, int *);
static void termination_event_notify(termination_event_t *self, int *noti) {
    printf("[INFO]: notify termination_event\n");
    *noti = self->blob;
}

static void terminate(termination_event_t *, int *);
static void terminate(termination_event_t *e, int *noti) {
    printf("[INFO]: loop num = %d, it's time to terminate.\n", *noti);
    test_evtmon_t_stopLoop(&evtmon);
}

static void echo_event_notify(echo_event_t *, byte256_t *);
static void echo_event_notify(echo_event_t *self, byte256_t *noti) {
    printf("[INFO]: notify echo_event\n");
    self->blob++;
} 

static void echo(echo_event_t *, byte256_t *);
static void echo(echo_event_t *e, byte256_t *noti) {
    printf("[INFO]: echo: %s\n", *noti);
} 

static void fill_byte256_with_zeros(byte256_t *);
static void fill_byte256_with_zeros(byte256_t *noti) {
    memset(*noti, 0, 256);
}

static void init_test(void);
static void init_test(void) {
    int counter = 0;
    test_evtmon_t_init(&evtmon);
    usr_enter_event_t_init(&usr_enter_event, &counter, usr_enter_event_poll, usr_enter_event_notify);
    termination_event_t_init(&termination_event, &counter, termination_event_update, termination_event_check, termination_event_notify);
    echo_event_t_init(&echo_event, &counter, echo_event_notify);
    printf("[INFO]: after init\n");
}

static void register_events(void);
static void register_events(void) {
    test_evtmon_t_registerChangeEvent(&evtmon, &usr_enter_event, receive_user_input, &usr_enter_event_id);
    test_evtmon_t_registerTimeEvent(&evtmon, &termination_event, terminate, &termination_event_id);
    test_evtmon_t_registerMessageEvent(&evtmon, &echo_event, echo, &echo_event_id);
    printf("[INFO]: usr_enter_event_id = %d, termination_event_id = %d, echo_event_id = %d\n", usr_enter_event_id, termination_event_id, echo_event_id);
}

int main(int argc, char *argv[]) {
    init_test();
    register_events();
    test_evtmon_t_startLoop(&evtmon);
    printf("[INFO]: Everything works well\n");
    
    return 0;
}