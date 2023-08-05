#include <stdio.h>
#include <stdlib.h>
#include "esi_rrserver.h"
#include "esi_err/esi_err.h"
#include "esi_str/esi_str.h"

#define SUBJECT_NUM (5)
#define ACTION_NUM (5)
#define OBJECT_NUM (5)

static int sub2hdr[SUBJECT_NUM] = {-1, -1, -1, -1, -1};
static const char *sub_names[SUBJECT_NUM] = {"Bobo", "Lucety", "Li", "Mio", "Plu"};
static const char *act_names[ACTION_NUM] = {"plays", "hits", "ignores", "focuses", "sees"};

struct code_msg {
    int sub;
    int act;
    int obj;
};
typedef struct code_msg code_msg_t;

typedef char str_msg_t[256];

ESI_ARRAY_BASED_RRSERVER_DECL(translator_t, code_msg_t, str_msg_t, 10)
ESI_ARRAY_BASED_RRSERVER_IMPL(translator_t, code_msg_t, str_msg_t, 10)

static translator_t translator;

static void translate(code_msg_t *, str_msg_t *);
static void translate(code_msg_t *code, str_msg_t *msg) {
    strcpy(*msg, sub_names[code->sub]);
    strcat(*msg, " ");
    strcat(*msg, act_names[code->act]);
    strcat(*msg, " ");
    strcat(*msg, sub_names[code->obj]);
}

static esi_err_t handle_bobo(code_msg_t *, str_msg_t *);
static esi_err_t handle_bobo(code_msg_t *req, str_msg_t *res) {
    translate(req, res);
    return 0;
}

static esi_err_t handle_lucety(code_msg_t *, str_msg_t *);
static esi_err_t handle_lucety(code_msg_t *req, str_msg_t *res) {
    translate(req, res);
    return 0;
}

static esi_err_t handle_li(code_msg_t *, str_msg_t *);
static esi_err_t handle_li(code_msg_t *req, str_msg_t *res) {
    translate(req, res);
    return 0;
}

static esi_err_t handle_mio(code_msg_t *, str_msg_t *);
static esi_err_t handle_mio(code_msg_t *req, str_msg_t *res) {
    translate(req, res);
    return 0;
}

static esi_err_t handle_plu(code_msg_t *, str_msg_t *);
static esi_err_t handle_plu(code_msg_t *req, str_msg_t *res) {
    translate(req, res);
    return 0;
}

static void do_register(translator_t *, translator_t_hdr_func_t, int);
static void do_register(translator_t *rrs, translator_t_hdr_func_t hdr, int subid) {
    int ret;
    int hdr_id;

    ret = translator_t_register(rrs, hdr, &hdr_id);
    if (ret != 0) {
        printf("[ERROR]: %s\n", esi_rrserver_strerror(ret));
        exit(0);
    }
    sub2hdr[subid] = hdr_id;
    printf("[INFO]: subid = %d, hdr_id = %d\n", subid, hdr_id);
}

static int sub2hdr_mapper(code_msg_t *);
static int sub2hdr_mapper(code_msg_t *code) {
    printf("[INFO]: in new mapper\n");
    if (code->sub != 4) {
        return sub2hdr[code->sub];
    } else {
        return 0;
    }
}

static int plu_picker(code_msg_t *);
static int plu_picker(code_msg_t *code) {
    printf("[INFO]: in plu picker\n");
    return code->sub == 4;
}

static void init_env(void);
static void init_env(void) {
    int i;

    translator_t_init(&translator);
    do_register(&translator, handle_bobo, 0);
    do_register(&translator, handle_lucety, 1);
    do_register(&translator, handle_li, 2);
    do_register(&translator, handle_mio, 3);
    do_register(&translator, handle_plu, 4);
    translator_t_setMapper(&translator, sub2hdr_mapper, NULL);
    translator_t_setPicker(&translator, sub2hdr[4], plu_picker, NULL);
}

static void launch_one_test(int sub, int act, int obj);
static void launch_one_test(int sub, int act, int obj) {
    code_msg_t code;
    str_msg_t msg;
    int ret;

    code.sub = sub;
    code.act = act;
    code.obj = obj;
    printf("[ERROR]: before serving\n");
    ret = translator_t_serve(&translator, &code, &msg);
    if (ret != 0) {
        printf("[ERROR]: %s\n", esi_rrserver_strerror(ret));
        exit(0);
    }
    printf("[INFO]: code = (%d, %d, %d), response msg: %s\n", sub, act, obj, msg); 
}

int main(int argc, char *argv[]) {
    code_msg_t code;
    str_msg_t msg;
    int ret;

    init_env();
    launch_one_test(0, 2, 4);
    launch_one_test(4, 3, 1);

    return 0;
}