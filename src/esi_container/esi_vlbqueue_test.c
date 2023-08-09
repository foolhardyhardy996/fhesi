#include "esi_err/esi_err.h"
#include "esi_vlbqueue.h"
#include "esi_str/esi_str.h"
#include <stdio.h>

#define STR_REPO_CAP 5
#define STR_REPO_BUFSZ 11
ESI_VARLEN_BYTES_QUEUE_DECL(str_repo_t, STR_REPO_CAP, STR_REPO_BUFSZ)
ESI_VARLEN_BYTES_QUEUE_IMPL(str_repo_t, STR_REPO_CAP, STR_REPO_BUFSZ)

static int str_args_num = 5;
const char *str_args[] = {"a", "bc", "d", "ef", "ghi"};
static str_repo_t repo;

static void init_test(void);
static void init_test(void) {
    str_repo_t_init(&repo);
}

int main(int argc, char *argv[]) {
    int ret;
    char *s;
    int i = 0;

    init_test();
    for (i = 0; i < str_args_num; i++) {
        ret = str_repo_t_insertBack(&repo, (char *) str_args[i], strlen(str_args[i]) + 1);
        if (ret != 0) {
            printf("[INFO]: insert failed, it reports: %s\n", esi_vlbqueue_strerror(ret));
        } else {
            printf("[INFO]: insert \"%s\" successfully\n", str_args[i]);
        }
    }
    str_repo_t_deleteFront(&repo);
    str_repo_t_deleteFront(&repo);
    printf("[INFO]: after two deleteFront\n");
    ret = str_repo_t_insertBack(&repo, (char *) str_args[4], strlen(str_args[4]) + 1);
    if (ret != 0) {
        printf("[INFO]: insert \"%s\" failed, it reports: %s\n", str_args[4], esi_vlbqueue_strerror(ret));
    } else {
        printf("[INFO]: insert \"%s\" successfully\n", str_args[4]);
    }
    str_repo_t_deleteFront(&repo);
    str_repo_t_deleteFront(&repo);
    printf("[INFO]: after two deleteFront\n");
    if (repo.boundary != STR_REPO_BUFSZ) {
        printf("[ERROR]: fail to maintain boundary invariant\n");
    } else {
        printf("[INFO]: properly deleted corner node\n");
    }
    printf("[INFO]: everything works fine\n");

    return 0;
}