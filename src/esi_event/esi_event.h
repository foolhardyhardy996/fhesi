#pragma once 

/**
 * @file esi_change_event.h
 * @brief "esi_change_event.h" provides template for change event
 * 
 * 
 * 
 * @author Li Weida
 * @date 2023.08.05
*/

#include "esi_list/esi_sdlist.h"
#include "esi_err/esi_err.h"
#include "esi_functional/esi_functional.h"

enum esi_event_err {
    ESI_EVENT_ERR_NONE = 0,
    ESI_EVENTMON_ERR_CAP = 1,
    ESI_EVENTMON_ERR_INVALID_ID = 2,
    ESI_EVENTMON_ERR_INVALID_HDR = 3,
    ESI_EVENT_ERR_UNKNOWN = 4
};

#define ESI_EVENT_ERR_MSG {\
    "esi_event: ok", /*0*/\
    "esi_eventmon: capacity has been reached", /*1*/\
    "esi_eventmon: invalid event id", /*2*/\
    "esi_eventmon: invalid handler", /*3*/\
    "esi_event: unknown error" /*4*/\
}

const char *esi_event_strerror(int err);

#define ESI_CHANGE_EVENT_DECL(alias, blob_t, noti_t) \
typedef blob_t alias##_blob_t;\
typedef noti_t alias##_noti_t;\
struct alias##_change_event;\
typedef struct alias##_change_event alias;\
typedef int (*alias##_poll_func_t)(alias *);\
typedef void (*alias##_notify_func_t)(alias *, noti_t *);\
struct alias##_change_event {\
    blob_t blob;\
    int (*poll)(alias *);\
    void (*notify)(alias *, noti_t *);\
};\
esi_err_t alias##_init(alias *, blob_t *, alias##_poll_func_t, alias##_notify_func_t);\
esi_err_t alias##_initWithAssign(alias *, blob_t *, ESI_ASSIGN_FUNC_T(blob_t, assign), alias##_poll_func_t, alias##_notify_func_t);\
esi_err_t alias##_initWithEmplace(alias *, ESI_MODIFY_FUNC_T(blob_t, emplace), alias##_poll_func_t, alias##_notify_func_t);

#define ESI_CHANGE_EVENT_IMPL(alias, blob_t, noti_t) \
esi_err_t alias##_init(alias *self, blob_t *blob, alias##_poll_func_t poll, alias##_notify_func_t notify) {\
    self->blob = *blob;\
    self->poll = poll;\
    self->notify = notify;\
    return ESI_EVENT_ERR_NONE;\
}\
esi_err_t alias##_initWithAssign(alias *self, blob_t *blob, ESI_ASSIGN_FUNC_T(blob_t, assign), alias##_poll_func_t poll, alias##_notify_func_t notify) {\
    assign(&(self->blob), blob);\
    self->poll = poll;\
    self->notify = notify;\
    return ESI_EVENT_ERR_NONE;\
}\
esi_err_t alias##_initWithEmplace(alias *self, ESI_MODIFY_FUNC_T(blob_t, emplace), alias##_poll_func_t poll, alias##_notify_func_t notify) {\
    emplace(&(self->blob));\
    self->poll = poll;\
    self->notify = notify;\
    return ESI_EVENT_ERR_NONE;\
}

#define ESI_TIME_EVENT_DECL(alias, blob_t, noti_t) \
typedef blob_t alias##_blob_t;\
typedef noti_t alias##_noti_t;\
struct alias##_time_event;\
typedef struct alias##_time_event alias;\
typedef void (*alias##_update_func_t)(alias *);\
typedef int (*alias##_check_func_t)(alias *);\
typedef void (*alias##_notify_func_t)(alias *, noti_t *);\
struct alias##_time_event {\
    blob_t blob;\
    void (*update)(alias *);\
    int (*check)(alias *);\
    void (*notify)(alias *, noti_t *);\
};\
esi_err_t alias##_init(alias *, blob_t *, alias##_update_func_t, alias##_check_func_t, alias##_notify_func_t);\
esi_err_t alias##_initWithAssign(alias *, blob_t *, ESI_ASSIGN_FUNC_T(blob_t, assign), alias##_update_func_t, alias##_check_func_t, alias##_notify_func_t);\
esi_err_t alias##_initWithEmplace(alias *, ESI_MODIFY_FUNC_T(blob_t, emplace), alias##_update_func_t, alias##_check_func_t, alias##_notify_func_t);

#define ESI_TIME_EVENT_IMPL(alias, blob_t, noti_t) \
esi_err_t alias##_init(alias *self, blob_t *blob, alias##_update_func_t update, alias##_check_func_t check, alias##_notify_func_t notify) {\
    self->blob = *blob;\
    self->update = update;\
    self->check = check;\
    self->notify = notify;\
    return ESI_EVENT_ERR_NONE;\
}\
esi_err_t alias##_initWithAssign(alias *self, blob_t *blob, ESI_ASSIGN_FUNC_T(blob_t, assign), alias##_update_func_t update, alias##_check_func_t check, alias##_notify_func_t notify) {\
    assign(&(self->blob), blob);\
    self->update = update;\
    self->check = check;\
    self->notify = notify;\
    return ESI_EVENT_ERR_NONE;\
}\
esi_err_t alias##_initWithEmplace(alias *self, ESI_MODIFY_FUNC_T(blob_t, emplace), alias##_update_func_t update, alias##_check_func_t check, alias##_notify_func_t notify) {\
    emplace(&(self->blob));\
    self->update = update;\
    self->check = check;\
    self->notify = notify;\
    return ESI_EVENT_ERR_NONE;\
}

#define ESI_EMSG_EVENT_DECL(alias, blob_t, emsg_t) \
typedef blob_t alias##_blob_t;\
typedef emsg_t alias##_emsg_t;\
typedef emsg_t##_noti_t alias##_noti_t;\
struct alias##_emsg_event;\
typedef struct alias##_emsg_event alias;\
typedef void (*alias##_notify_func_t)(alias *, alias##_noti_t *);\
struct alias##_emsg_event {\
    blob_t blob;\
    void (*notify)(alias *, alias##_noti_t *);\
};\
esi_err_t alias##_init(alias *, blob_t *, alias##_notify_func_t);\
esi_err_t alias##_initWithAssign(alias *, blob_t *, ESI_ASSIGN_FUNC_T(blob_t, assign), alias##_notify_func_t);\
esi_err_t alias##_initWithEmplace(alias *, ESI_MODIFY_FUNC_T(blob_t, emplace), alias##_notify_func_t);

#define ESI_EMSG_EVENT_IMPL(alias, blob_t, emsg_t) \
esi_err_t alias##_init(alias *self, blob_t *blob, alias##_notify_func_t notify) {\
    self->blob = *blob;\
    self->notify = notify;\
    return ESI_EVENT_ERR_NONE;\
}\
esi_err_t alias##_initWithAssign(alias *self, blob_t *blob, ESI_ASSIGN_FUNC_T(blob_t, assign), alias##_notify_func_t notify) {\
    assign(&(self->blob), blob);\
    self->notify = notify;\
    return ESI_EVENT_ERR_NONE;\
}\
esi_err_t alias##_initWithEmplace(alias *self, ESI_MODIFY_FUNC_T(blob_t, emplace), alias##_notify_func_t notify) {\
    emplace(&(self->blob));\
    self->notify = notify;\
    return ESI_EVENT_ERR_NONE;\
}

#define ESI_EMSG_DECL(alias, noti_t) \
typedef noti_t alias##_noti_t;\
struct alias##_emsg {\
    int event_id;\
    noti_t noti;\
};\
typedef struct alias##_emsg alias;

/**
 * eventmon hosts four kinds of object repositories:
 * 1. three kinds of event
 * 2. handler control block
 * 3. message
*/
#define ESI_EVENTMON_DECL(alias, ce_t, te_t, me_t, event_cap, emsg_cap) \
typedef ce_t alias##_change_event_t;\
typedef te_t alias##_time_event_t;\
typedef me_t alias##_emsg_event_t;\
extern const int alias##_event_cap;\
extern const int alias##_emsg_queue_cap;\
struct alias##_eventmon;\
typedef struct alias##_eventmon alias;\
enum alias##_event_type {\
    alias##_ce_type,\
    alias##_te_type,\
    alias##_me_type\
};\
typedef ESI_MODIFY_FUNC_T(ce_t, alias##_ce_modifier_t);\
typedef ESI_MODIFY_FUNC_T(te_t, alias##_te_modifier_t);\
typedef ESI_MODIFY_FUNC_T(me_t, alias##_me_modifier_t);\
union alias##_event {\
    ce_t ce;\
    te_t te;\
    me_t me;\
};\
typedef union alias##_event alias##_event_t;\
union alias##_noti {\
    ce_t##_noti_t cenoti;\
    te_t##_noti_t tenoti;\
    me_t##_noti_t menoti;\
};\
typedef union alias##_noti alias##_noti_t;\
typedef void (*alias##_cehdr_t)(ce_t *, ce_t##_noti_t *);\
typedef void (*alias##_tehdr_t)(te_t *, te_t##_noti_t *);\
typedef void (*alias##_mehdr_t)(me_t *, me_t##_noti_t *);\
union alias##_hdr {\
    alias##_cehdr_t cehdr;\
    alias##_tehdr_t tehdr;\
    alias##_mehdr_t mehdr;\
};\
typedef union alias##_hdr alias##_hdr_t;\
struct alias##_eventcb {\
    int event_type;\
    alias##_event_t event;\
    alias##_hdr_t hdr;\
    int free_flag;\
};\
typedef struct alias##_eventcb alias##_eventcb_t;\
ESI_SDLIST_DECL(alias##_eventcb_repo_t, alias##_eventcb_t, event_cap)\
ESI_SDLIST_DECL(alias##_emsg_queue_t, me_t##_emsg_t, emsg_cap)\
struct alias##_eventmon {\
    alias##_eventcb_repo_t eventcb_repo;\
    alias##_emsg_queue_t emsg_queue;\
    int stop_flag;\
};\
esi_err_t alias##_init(alias *);\
esi_err_t alias##_registerChangeEvent(alias *, ce_t *, alias##_cehdr_t, int *);\
esi_err_t alias##_registerChangeEventWithAssign(alias *, ce_t *, ESI_ASSIGN_FUNC_T(ce_t, assign), alias##_cehdr_t, int *);\
esi_err_t alias##_registerChangeEventWithEmplace(alias *, ESI_MODIFY_FUNC_T(ce_t, emplace), alias##_cehdr_t, int *);\
esi_err_t alias##_setChangeEventHandler(alias *, int, alias##_cehdr_t, alias##_cehdr_t *);\
esi_err_t alias##_unregisterChangeEvent(alias *, int);\
esi_err_t alias##_registerTimeEvent(alias *, te_t *, alias##_tehdr_t, int *);\
esi_err_t alias##_registerTimeEventWithAssign(alias *, te_t *, ESI_ASSIGN_FUNC_T(te_t, assign), alias##_tehdr_t, int *);\
esi_err_t alias##_registerTimeEventWithEmplace(alias *, ESI_MODIFY_FUNC_T(te_t, emplace), alias##_tehdr_t, int *);\
esi_err_t alias##_setTimeEventHandler(alias *, int, alias##_tehdr_t, alias##_tehdr_t *);\
esi_err_t alias##_unregisterTimeEvent(alias *, int);\
esi_err_t alias##_registerMessageEvent(alias *, me_t *, alias##_mehdr_t, int *);\
esi_err_t alias##_registerMessageEventWithAssign(alias *, me_t *, ESI_ASSIGN_FUNC_T(me_t, assign), alias##_mehdr_t, int *);\
esi_err_t alias##_registerMessageEventWithEmplace(alias *, ESI_MODIFY_FUNC_T(me_t, emplace), alias##_mehdr_t, int *);\
esi_err_t alias##_setMessageEventHandler(alias *, int, alias##_mehdr_t, alias##_mehdr_t *);\
esi_err_t alias##_unregisterMessageEvent(alias *, int);\
esi_err_t alias##_addMessage(alias *, me_t##_emsg_t *);\
esi_err_t alias##_addMessageWithAssign(alias *, me_t##_emsg_t *, ESI_ASSIGN_FUNC_T(me_t##_emsg_t, assign));\
esi_err_t alias##_addMessageWithEmplace(alias *, ESI_MODIFY_FUNC_T(me_t##_emsg_t, emplace));\
esi_err_t alias##_startLoop(alias *);\
esi_err_t alias##_stopLoop(alias *);\

#define ESI_EVENTMON_IMPL(alias, ce_t, te_t, me_t, event_cap, emsg_cap) \
const int alias##_event_cap = event_cap;\
const int alias##_emsg_queue_cap = emsg_cap;\
ESI_SDLIST_IMPL(alias##_eventcb_repo_t, alias##_eventcb_t, event_cap)\
ESI_SDLIST_IMPL(alias##_emsg_queue_t, me_t##_emsg_t, emsg_cap)\
static int alias##_validateEventId(alias *, int);\
static int alias##_validateEventId(alias *self, int event_id) {\
    if (event_id < 0 || event_id >= event_cap) {\
        return 0;\
    }\
    return self->eventcb_repo.repo[event_id].elem.free_flag == 0;\
}\
/** It reminds me to construct some function object later. */\
static void alias##_emplaceEventcb_ce_assign(ce_t *, ce_t *);\
static void alias##_emplaceEventcb_ce_assign(ce_t *dest, ce_t *src) {\
    *dest = *src;\
}\
static void alias##_emplaceEventcb_te_assign(te_t *, te_t *);\
static void alias##_emplaceEventcb_te_assign(te_t *dest, te_t *src) {\
    *dest = *src;\
}\
static void alias##_emplaceEventcb_me_assign(me_t *, me_t *);\
static void alias##_emplaceEventcb_me_assign(me_t *dest, me_t *src) {\
    *dest = *src;\
}\
static ESI_ASSIGN_FUNC_T(ce_t, alias##_emplaceEventcb_ce_emplaceWithAssign_assign);\
static ce_t *alias##_emplaceEventcb_ce_emplaceWithAssign_src;\
static void alias##_emplaceEventcb_ce_emplaceWithAssign(ce_t *);\
static void alias##_emplaceEventcb_ce_emplaceWithAssign(ce_t *dest) {\
    alias##_emplaceEventcb_ce_emplaceWithAssign_assign(dest, alias##_emplaceEventcb_ce_emplaceWithAssign_src);\
}\
static ESI_ASSIGN_FUNC_T(te_t, alias##_emplaceEventcb_te_emplaceWithAssign_assign);\
static te_t *alias##_emplaceEventcb_te_emplaceWithAssign_src;\
static void alias##_emplaceEventcb_te_emplaceWithAssign(te_t *);\
static void alias##_emplaceEventcb_te_emplaceWithAssign(te_t *dest) {\
    alias##_emplaceEventcb_te_emplaceWithAssign_assign(dest, alias##_emplaceEventcb_te_emplaceWithAssign_src);\
}\
static ESI_ASSIGN_FUNC_T(me_t, alias##_emplaceEventcb_me_emplaceWithAssign_assign);\
static me_t *alias##_emplaceEventcb_me_emplaceWithAssign_src;\
static void alias##_emplaceEventcb_me_emplaceWithAssign(me_t *);\
static void alias##_emplaceEventcb_me_emplaceWithAssign(me_t *dest) {\
    alias##_emplaceEventcb_me_emplaceWithAssign_assign(dest, alias##_emplaceEventcb_me_emplaceWithAssign_src);\
}\
static int alias##_emplaceEventcb_event_type;\
static ESI_MODIFY_FUNC_T(ce_t, alias##_emplaceEventcb_ce_emplace);\
static ESI_MODIFY_FUNC_T(te_t, alias##_emplaceEventcb_te_emplace);\
static ESI_MODIFY_FUNC_T(me_t, alias##_emplaceEventcb_me_emplace);\
static alias##_cehdr_t alias##_emplaceEventcb_cehdr;\
static alias##_tehdr_t alias##_emplaceEventcb_tehdr;\
static alias##_mehdr_t alias##_emplaceEventcb_mehdr;\
void alias##_emplaceEventcb(alias##_eventcb_t *);\
void alias##_emplaceEventcb(alias##_eventcb_t *eventcb) {\
    eventcb->free_flag = 0;\
    eventcb->event_type = alias##_emplaceEventcb_event_type;\
    switch (alias##_emplaceEventcb_event_type) {\
    case alias##_ce_type: \
        alias##_emplaceEventcb_ce_emplace(&(eventcb->event.ce));\
        eventcb->hdr.cehdr = alias##_emplaceEventcb_cehdr;\
        break;\
    case alias##_te_type: \
        alias##_emplaceEventcb_te_emplace(&(eventcb->event.te));\
        eventcb->hdr.tehdr = alias##_emplaceEventcb_tehdr;\
        break;\
    case alias##_me_type: \
        alias##_emplaceEventcb_me_emplace(&(eventcb->event.me));\
        eventcb->hdr.mehdr = alias##_emplaceEventcb_mehdr;\
        break;\
    }\
}\
static void alias##_configEventcbEmplacer(int, void *, void *);\
static void alias##_configEventcbEmplacer(int event_type, void *event_emplacer, void *hdr) {\
    alias##_emplaceEventcb_event_type = event_type;\
    switch (event_type) {\
    case alias##_ce_type: \
        alias##_emplaceEventcb_ce_emplace = (alias##_ce_modifier_t) event_emplacer;\
        alias##_emplaceEventcb_cehdr = (alias##_cehdr_t) hdr;\
        break;\
    case alias##_te_type: \
        alias##_emplaceEventcb_te_emplace = (alias##_te_modifier_t) event_emplacer;\
        alias##_emplaceEventcb_tehdr = (alias##_tehdr_t) hdr;\
        break;\
    case alias##_me_type: \
        alias##_emplaceEventcb_me_emplace = (alias##_me_modifier_t) event_emplacer;\
        alias##_emplaceEventcb_mehdr = (alias##_mehdr_t) hdr;\
        break;\
    }\
}\
static esi_err_t alias##_repoErr2EventmonErr(int);\
static esi_err_t alias##_repoErr2EventmonErr(int err) {\
    switch (err) {\
    case ESI_SDLIST_ERR_CAP: \
        return ESI_EVENTMON_ERR_CAP;\
    default:\
        return ESI_EVENT_ERR_UNKNOWN;\
    }\
}\
static void alias##_handleChangeEvent(ce_t *, alias##_cehdr_t);\
static void alias##_handleChangeEvent(ce_t *ce, alias##_cehdr_t hdr) {\
    if (ce->poll(ce)) {\
        ce_t##_noti_t noti;\
        ce->notify(ce, &noti);\
        hdr(ce, &noti);\
    }\
}\
static void alias##_handleTimeEvent(te_t *, alias##_tehdr_t);\
static void alias##_handleTimeEvent(te_t *te, alias##_tehdr_t hdr) {\
    te->update(te);\
    if (te->check(te)) {\
        te_t##_noti_t noti;\
        te->notify(te, &noti);\
        hdr(te, &noti);\
    }\
}\
static void alias##_iterateChangeEventAndTimeEvent(alias *);\
static void alias##_iterateChangeEventAndTimeEvent(alias *self) {\
    alias##_eventcb_repo_t_node_t *node;\
    alias##_eventcb_t *eventcb;\
    node = alias##_eventcb_repo_t_peekFront(&(self->eventcb_repo));\
    while (node != NULL) {\
        eventcb = &(node->elem);\
        if (eventcb->event_type == alias##_ce_type) {\
            alias##_handleChangeEvent(&(eventcb->event.ce), eventcb->hdr.cehdr);\
        } else if (eventcb->event_type == alias##_te_type) {\
            alias##_handleTimeEvent(&(eventcb->event.te), eventcb->hdr.tehdr);\
        } else {\
            break;\
        }\
        node = alias##_eventcb_repo_t_getNext(&(self->eventcb_repo), node);\
    }\
}\
static void alias##_iterateMessageQueue(alias *);\
static void alias##_iterateMessageQueue(alias *self) {\
    alias##_emsg_queue_t_node_t *node;\
    me_t##_emsg_t *emsg;\
    int event_id;\
    me_t##_noti_t *noti;\
    me_t *me;\
    alias##_mehdr_t hdr;\
    node = alias##_emsg_queue_t_peekBack(&(self->emsg_queue));\
    while (node != NULL) {\
        emsg = &(node->elem);\
        event_id = emsg->event_id;\
        noti = &(emsg->noti);\
        me = &(self->eventcb_repo.repo[event_id].elem.event.me);\
        hdr = self->eventcb_repo.repo[event_id].elem.hdr.mehdr;\
        me->notify(me, noti);\
        hdr(me, noti);\
        alias##_emsg_queue_t_delete(&(self->emsg_queue), node);\
        node = alias##_emsg_queue_t_peekBack(&(self->emsg_queue));\
    }\
}\
esi_err_t alias##_init(alias *self) {\
    int i = 0;\
    alias##_eventcb_repo_t_init(&(self->eventcb_repo));\
    for (i = 0; i < alias##_eventcb_repo_t_cap; i++) {\
        self->eventcb_repo.repo[i].elem.free_flag = 1;\
    }\
    alias##_emsg_queue_t_init(&(self->emsg_queue));\
    self->stop_flag = 0;\
    return ESI_EVENT_ERR_NONE;\
}\
esi_err_t alias##_registerChangeEvent(alias *self, ce_t *ce, alias##_cehdr_t hdr, int *event_id_holder) {\
    int ret;\
    alias##_emplaceEventcb_ce_emplaceWithAssign_assign = alias##_emplaceEventcb_ce_assign;\
    alias##_emplaceEventcb_ce_emplaceWithAssign_src = ce;\
    alias##_configEventcbEmplacer(alias##_ce_type, (void *) alias##_emplaceEventcb_ce_emplaceWithAssign, (void *) hdr);\
    ret = alias##_eventcb_repo_t_emplaceFront(&(self->eventcb_repo), alias##_emplaceEventcb);\
    if (ret != 0) {\
        return alias##_repoErr2EventmonErr(ret);\
    }\
    if (event_id_holder != NULL) {\
        *event_id_holder = self->eventcb_repo.head;\
    }\
    return ESI_EVENT_ERR_NONE;\
}\
esi_err_t alias##_registerChangeEventWithAssign(alias *self, ce_t *ce, ESI_ASSIGN_FUNC_T(ce_t, assign), alias##_cehdr_t hdr, int *event_id_holder) {\
    int ret;\
    alias##_emplaceEventcb_ce_emplaceWithAssign_assign = assign;\
    alias##_emplaceEventcb_ce_emplaceWithAssign_src = ce;\
    alias##_configEventcbEmplacer(alias##_ce_type, (void *) alias##_emplaceEventcb_ce_emplaceWithAssign, (void *) hdr);\
    ret = alias##_eventcb_repo_t_emplaceFront(&(self->eventcb_repo), alias##_emplaceEventcb);\
    if (ret != 0) {\
        return alias##_repoErr2EventmonErr(ret);\
    }\
    if (event_id_holder != NULL) {\
        *event_id_holder = self->eventcb_repo.head;\
    }\
    return ESI_EVENT_ERR_NONE;\
}\
esi_err_t alias##_registerChangeEventWithEmplace(alias *self, ESI_MODIFY_FUNC_T(ce_t, emplace), alias##_cehdr_t hdr, int *event_id_holder) {\
    int ret;\
    alias##_configEventcbEmplacer(alias##_ce_type, (void *) emplace, (void *) hdr);\
    ret = alias##_eventcb_repo_t_emplaceFront(&(self->eventcb_repo), alias##_emplaceEventcb);\
    if (ret != 0) {\
        return alias##_repoErr2EventmonErr(ret);\
    }\
    if (event_id_holder != NULL) {\
        *event_id_holder = self->eventcb_repo.head;\
    }\
    return ESI_EVENT_ERR_NONE;\
}\
esi_err_t alias##_setChangeEventHandler(alias *self, int event_id, alias##_cehdr_t new_hdr, alias##_cehdr_t *old_hdr) {\
    alias##_eventcb_t *eventcb;\
    if (!alias##_validateEventId(self, event_id)) {\
        return ESI_EVENTMON_ERR_INVALID_ID;\
    }\
    if (new_hdr == NULL) {\
        return ESI_EVENTMON_ERR_INVALID_HDR;\
    }\
    if (old_hdr != NULL) {\
        *old_hdr = self->eventcb_repo.repo[event_id].elem.hdr.cehdr;\
    }\
    self->eventcb_repo.repo[event_id].elem.hdr.cehdr = new_hdr;\
    return ESI_EVENT_ERR_NONE;\
}\
esi_err_t alias##_unregisterChangeEvent(alias *self, int event_id) {\
    alias##_eventcb_repo_t_node_t *node;\
    if (!alias##_validateEventId(self, event_id)) {\
        return ESI_EVENTMON_ERR_INVALID_ID;\
    }\
    node = alias##_eventcb_repo_t_getNodeByRepoIndex(&(self->eventcb_repo), event_id);\
    node->elem.free_flag = 1;\
    alias##_eventcb_repo_t_delete(&(self->eventcb_repo), node);\
    return ESI_EVENT_ERR_NONE;\
}\
esi_err_t alias##_registerTimeEvent(alias *self, te_t *te, alias##_tehdr_t hdr, int *event_id_holder) {\
    int ret;\
    alias##_emplaceEventcb_te_emplaceWithAssign_assign = alias##_emplaceEventcb_te_assign;\
    alias##_emplaceEventcb_te_emplaceWithAssign_src = te;\
    alias##_configEventcbEmplacer(alias##_te_type, (void *) alias##_emplaceEventcb_te_emplaceWithAssign, (void *) hdr);\
    ret = alias##_eventcb_repo_t_emplaceFront(&(self->eventcb_repo), alias##_emplaceEventcb);\
    if (ret != 0) {\
        return alias##_repoErr2EventmonErr(ret);\
    }\
    if (event_id_holder != NULL) {\
        *event_id_holder = self->eventcb_repo.head;\
    }\
    return ESI_EVENT_ERR_NONE;\
}\
esi_err_t alias##_registerTimeEventWithAssign(alias *self, te_t *te, ESI_ASSIGN_FUNC_T(te_t, assign), alias##_tehdr_t hdr, int *event_id_holder) {\
    int ret;\
    alias##_emplaceEventcb_te_emplaceWithAssign_assign = assign;\
    alias##_emplaceEventcb_te_emplaceWithAssign_src = te;\
    alias##_configEventcbEmplacer(alias##_te_type, (void *) alias##_emplaceEventcb_te_emplaceWithAssign, (void *) hdr);\
    ret = alias##_eventcb_repo_t_emplaceFront(&(self->eventcb_repo), alias##_emplaceEventcb);\
    if (ret != 0) {\
        return alias##_repoErr2EventmonErr(ret);\
    }\
    if (event_id_holder != NULL) {\
        *event_id_holder = self->eventcb_repo.head;\
    }\
    return ESI_EVENT_ERR_NONE;\
}\
esi_err_t alias##_registerTimeEventWithEmplace(alias *self, ESI_MODIFY_FUNC_T(te_t, emplace), alias##_tehdr_t hdr, int *event_id_holder) {\
    int ret;\
    alias##_configEventcbEmplacer(alias##_te_type, (void *) emplace, (void *) hdr);\
    ret = alias##_eventcb_repo_t_emplaceFront(&(self->eventcb_repo), alias##_emplaceEventcb);\
    if (ret != 0) {\
        return alias##_repoErr2EventmonErr(ret);\
    }\
    if (event_id_holder != NULL) {\
        *event_id_holder = self->eventcb_repo.head;\
    }\
    return ESI_EVENT_ERR_NONE;\
}\
esi_err_t alias##_setTimeEventHandler(alias *self, int event_id, alias##_tehdr_t new_hdr, alias##_tehdr_t *old_hdr) {\
    alias##_eventcb_t *eventcb;\
    if (!alias##_validateEventId(self, event_id)) {\
        return ESI_EVENTMON_ERR_INVALID_ID;\
    }\
    if (new_hdr == NULL) {\
        return ESI_EVENTMON_ERR_INVALID_HDR;\
    }\
    if (old_hdr != NULL) {\
        *old_hdr = self->eventcb_repo.repo[event_id].elem.hdr.tehdr;\
    }\
    self->eventcb_repo.repo[event_id].elem.hdr.tehdr = new_hdr;\
    return ESI_EVENT_ERR_NONE;\
}\
esi_err_t alias##_unregisterTimeEvent(alias *self, int event_id) {\
    alias##_eventcb_repo_t_node_t *node;\
    if (!alias##_validateEventId(self, event_id)) {\
        return ESI_EVENTMON_ERR_INVALID_ID;\
    }\
    node = alias##_eventcb_repo_t_getNodeByRepoIndex(&(self->eventcb_repo), event_id);\
    node->elem.free_flag = 1;\
    alias##_eventcb_repo_t_delete(&(self->eventcb_repo), node);\
    return ESI_EVENT_ERR_NONE;\
}\
esi_err_t alias##_registerMessageEvent(alias *self, me_t *me, alias##_mehdr_t hdr, int *event_id_holder) {\
    int ret;\
    alias##_emplaceEventcb_me_emplaceWithAssign_assign = alias##_emplaceEventcb_me_assign;\
    alias##_emplaceEventcb_me_emplaceWithAssign_src = me;\
    alias##_configEventcbEmplacer(alias##_me_type, (void *) alias##_emplaceEventcb_me_emplaceWithAssign, (void *) hdr);\
    ret = alias##_eventcb_repo_t_emplaceBack(&(self->eventcb_repo), alias##_emplaceEventcb);\
    if (ret != 0) {\
        return alias##_repoErr2EventmonErr(ret);\
    }\
    if (event_id_holder != NULL) {\
        *event_id_holder = self->eventcb_repo.tail;\
    }\
    return ESI_EVENT_ERR_NONE;\
}\
esi_err_t alias##_registerMessageEventWithAssign(alias *self, me_t *me, ESI_ASSIGN_FUNC_T(me_t, assign), alias##_mehdr_t hdr, int *event_id_holder) {\
    int ret;\
    alias##_emplaceEventcb_me_emplaceWithAssign_assign = assign;\
    alias##_emplaceEventcb_me_emplaceWithAssign_src = me;\
    alias##_configEventcbEmplacer(alias##_me_type, (void *) alias##_emplaceEventcb_me_emplaceWithAssign, (void *) hdr);\
    ret = alias##_eventcb_repo_t_emplaceBack(&(self->eventcb_repo), alias##_emplaceEventcb);\
    if (ret != 0) {\
        return alias##_repoErr2EventmonErr(ret);\
    }\
    if (event_id_holder != NULL) {\
        *event_id_holder = self->eventcb_repo.tail;\
    }\
    return ESI_EVENT_ERR_NONE;\
}\
esi_err_t alias##_registerMessageEventWithEmplace(alias *self, ESI_MODIFY_FUNC_T(me_t, emplace), alias##_mehdr_t hdr, int *event_id_holder) {\
    int ret;\
    alias##_configEventcbEmplacer(alias##_me_type, (void *) emplace, (void *) hdr);\
    ret = alias##_eventcb_repo_t_emplaceBack(&(self->eventcb_repo), alias##_emplaceEventcb);\
    if (ret != 0) {\
        return alias##_repoErr2EventmonErr(ret);\
    }\
    if (event_id_holder != NULL) {\
        *event_id_holder = self->eventcb_repo.tail;\
    }\
    return ESI_EVENT_ERR_NONE;\
}\
esi_err_t alias##_setMessageEventHandler(alias *self, int event_id, alias##_mehdr_t new_hdr, alias##_mehdr_t *old_hdr) {\
    alias##_eventcb_t *eventcb;\
    if (!alias##_validateEventId(self, event_id)) {\
        return ESI_EVENTMON_ERR_INVALID_ID;\
    }\
    if (new_hdr == NULL) {\
        return ESI_EVENTMON_ERR_INVALID_HDR;\
    }\
    if (old_hdr != NULL) {\
        *old_hdr = self->eventcb_repo.repo[event_id].elem.hdr.mehdr;\
    }\
    self->eventcb_repo.repo[event_id].elem.hdr.mehdr = new_hdr;\
    return ESI_EVENT_ERR_NONE;\
}\
esi_err_t alias##_unregisterMessageEvent(alias *self, int event_id) {\
    alias##_eventcb_repo_t_node_t *node;\
    if (!alias##_validateEventId(self, event_id)) {\
        return ESI_EVENTMON_ERR_INVALID_ID;\
    }\
    node = alias##_eventcb_repo_t_getNodeByRepoIndex(&(self->eventcb_repo), event_id);\
    node->elem.free_flag = 1;\
    alias##_eventcb_repo_t_delete(&(self->eventcb_repo), node);\
    return ESI_EVENT_ERR_NONE;\
}\
esi_err_t alias##_addMessage(alias *self, me_t##_emsg_t *msg) {\
    int ret;\
    if (!alias##_validateEventId(self, msg->event_id)) {\
        return ESI_EVENTMON_ERR_INVALID_ID;\
    }\
    ret = alias##_emsg_queue_t_insertFront(&(self->emsg_queue), msg);\
    if (ret != 0) {\
        return alias##_repoErr2EventmonErr(ret);\
    }\
    return ESI_EVENT_ERR_NONE;\
}\
esi_err_t alias##_addMessageWithAssign(alias *self, me_t##_emsg_t *msg, ESI_ASSIGN_FUNC_T(me_t##_emsg_t, assign)) {\
    int ret;\
    if (!alias##_validateEventId(self, msg->event_id)) {\
        return ESI_EVENTMON_ERR_INVALID_ID;\
    }\
    ret = alias##_emsg_queue_t_insertFrontWithAssign(&(self->emsg_queue), msg, assign);\
    if (ret != 0) {\
        return alias##_repoErr2EventmonErr(ret);\
    }\
    return ESI_EVENT_ERR_NONE;\
}\
esi_err_t alias##_addMessageWithEmplace(alias *self, ESI_MODIFY_FUNC_T(me_t##_emsg_t, emplace)) {\
    int ret;\
    ret = alias##_emsg_queue_t_emplaceFront(&(self->emsg_queue), emplace);\
    if (ret != 0) {\
        return alias##_repoErr2EventmonErr(ret);\
    }\
    if (!alias##_validateEventId(self, self->eventcb_repo.head)) {\
        alias##_emsg_queue_t_delete(&(self->emsg_queue), alias##_emsg_queue_t_peekFront(&(self->emsg_queue)));\
        return ESI_EVENTMON_ERR_INVALID_ID;\
    }\
    return ESI_EVENT_ERR_NONE;\
}\
/*To save time, I do a little trick: change events and time events are registered at front*/\
/*message events are registered at back*/\
esi_err_t alias##_startLoop(alias *self) {\
    while (self->stop_flag == 0) {\
        alias##_iterateChangeEventAndTimeEvent(self);\
        alias##_iterateMessageQueue(self);\
    }\
    return ESI_EVENT_ERR_NONE;\
}\
esi_err_t alias##_stopLoop(alias *self) {\
    self->stop_flag = 1;\
    return ESI_EVENT_ERR_NONE;\
}
