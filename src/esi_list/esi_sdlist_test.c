#include "esi_sdlist.h"

#include <stdio.h>

struct point2d {
    int x;
    int y;
};

typedef struct point2d point2d_t;

#define POINT_REPO_CAP 9
ESI_SDLIST_TYPE_DECL(point_repo_t, point2d_t, POINT_REPO_CAP);
ESI_SDLIST_TYPE_IMPL(point_repo_t, point2d_t, POINT_REPO_CAP);

static void print_sdlist_stat(point_repo_t *);
static void print_sdlist_stat(point_repo_t *p_sdlist) {
    printf(
        "point_repo_t{cap = %d, len = %d, free_len = %d}\n", 
        ESI_SDLIST_CAP(point_repo_t, p_sdlist),
        ESI_SDLIST_LEN(point_repo_t, p_sdlist),
        ESI_SDLIST_GET_FREE_LIST_LEN(point_repo_t, p_sdlist));
}

static void print_node_stat(ESI_SDLIST_NODE_T(point_repo_t) *);
static void print_node_stat(ESI_SDLIST_NODE_T(point_repo_t) *p_node) {
    printf("node{point{x = %d, y = %d}, prev = %d, prev = %d}\n", p_node->node_data.x, p_node->node_data.y, p_node->prev, p_node->next);
} 

static point_repo_t point_repo;

static void inspect_in_order(void);
static void inspect_in_order(void) {
    ESI_SDLIST_NODE_T(point_repo_t) *p_node;
    p_node = ESI_SDLIST_PEEK_FRONT(point_repo_t, &point_repo);
    printf("[INFO]: inspect each node in order:\n");
    while (p_node != NULL) {
        print_node_stat(p_node);
        p_node = ESI_SDLIST_GET_NEXT_NODE(point_repo_t, &point_repo, p_node);
    }
}

static void inspect_in_reverse_order(void) {
    ESI_SDLIST_NODE_T(point_repo_t) *p_node;
    p_node = ESI_SDLIST_PEEK_BACK(point_repo_t, &point_repo);
    printf("[INFO]: inspect each node in reverse order:\n");
    while (p_node != NULL) {
        print_node_stat(p_node);
        p_node = ESI_SDLIST_GET_PREV_NODE(point_repo_t, &point_repo, p_node);
    }
}

static void init_test(void);
static void init_test(void) {
    point2d_t point;
    
    ESI_SDLIST_INIT(point_repo_t, &point_repo);
    point.x = 2;
    point.y = 1;
    ESI_SDLIST_PUSH_FRONT(point_repo_t, &point_repo, &point);
    point.x = 2;
    point.y = 2;
    ESI_SDLIST_PUSH_BACK(point_repo_t, &point_repo, &point);
    point.x = 2;
    point.y = 3;
    ESI_SDLIST_PUSH_BACK(point_repo_t, &point_repo, &point);
    printf("[INFO]: initialize point_repo by pushing in 3 points.\n");
    print_sdlist_stat(&point_repo);
    inspect_in_order();
    inspect_in_reverse_order();
}

static point2d_t preset_point;
static int point_equal_to_preset(point2d_t *);
static int point_equal_to_preset(point2d_t *p_point) {
    return p_point->x == preset_point.x && p_point->y == preset_point.y;
}

int main(int argc, char *argv[]) {
    point2d_t point;
    ESI_SDLIST_NODE_T(point_repo_t) *p_node;
    int ret;

    init_test();

    // push front (1,1) (1,2) (1,3)
    point.x = 1;
    point.y = 3;
    ESI_SDLIST_PUSH_FRONT(point_repo_t, &point_repo, &point);
    point.x = 1;
    point.y = 2;
    ESI_SDLIST_PUSH_FRONT(point_repo_t, &point_repo, &point);
    point.x = 1;
    point.y = 1;
    ESI_SDLIST_PUSH_FRONT(point_repo_t, &point_repo, &point);
    printf("[INFO]: after pushing front (1,3) (1,2) (1,1)\n");
    print_sdlist_stat(&point_repo);
    inspect_in_order();

    // push back (3,1) (3,2) (3,3)
    point.x = 3;
    point.y = 1;
    ESI_SDLIST_PUSH_BACK(point_repo_t, &point_repo, &point);
    point.x = 3;
    point.y = 2;
    ESI_SDLIST_PUSH_BACK(point_repo_t, &point_repo, &point);
    point.x = 3;
    point.y = 3;
    ESI_SDLIST_PUSH_BACK(point_repo_t, &point_repo, &point);
    printf("[INFO]: after pushing front (1,3) (1,2) (1,1)\n");
    print_sdlist_stat(&point_repo);
    inspect_in_order();

    // now, more push should fail
    point.x = -1;
    point.y = -1;
    ret = ESI_SDLIST_PUSH_BACK(point_repo_t, &point_repo, &point);
    printf("[INFO]: push back when in cap, it reports: %s\n", esi_sdlist_strerror(ret));
    ret = ESI_SDLIST_PUSH_FRONT(point_repo_t, &point_repo, &point);
    printf("[INFO]: push front when in cap, it reports: %s\n", esi_sdlist_strerror(ret));
    printf("[INFO]: after pushing when in cap\n");
    print_sdlist_stat(&point_repo);
    inspect_in_order();

    // delete (2,1) (2,2) (2,3)
    preset_point.x = 2;
    preset_point.y = 1;
    p_node = ESI_SDLIST_FIND_IF(point_repo_t, &point_repo, point_equal_to_preset);
    ESI_SDLIST_DELETE(point_repo_t, &point_repo, p_node);
    preset_point.x = 2;
    preset_point.y = 2;
    p_node = ESI_SDLIST_FIND_IF(point_repo_t, &point_repo, point_equal_to_preset);
    ESI_SDLIST_DELETE(point_repo_t, &point_repo, p_node);
    preset_point.x = 2;
    preset_point.y = 3;
    p_node = ESI_SDLIST_FIND_IF(point_repo_t, &point_repo, point_equal_to_preset);
    ESI_SDLIST_DELETE(point_repo_t, &point_repo, p_node);
    printf("[INFO]: after deleting (2,1) (2,2) (2,3)");
    print_sdlist_stat(&point_repo);
    inspect_in_order();

    // insert (2,1) (2,2) (2,3) back
    preset_point.x = 1;
    preset_point.y = 3;
    p_node = ESI_SDLIST_FIND_IF(point_repo_t, &point_repo, point_equal_to_preset);
    point.x = 2;
    point.y = 1;
    ESI_SDLIST_INSERT_AFTER(point_repo_t, &point_repo, p_node, &point);
    preset_point.x = 2;
    preset_point.y = 1;
    p_node = ESI_SDLIST_FIND_IF(point_repo_t, &point_repo, point_equal_to_preset);
    point.x = 2;
    point.y = 3;
    ESI_SDLIST_INSERT_AFTER(point_repo_t, &point_repo, p_node, &point);
    preset_point.x = 2;
    preset_point.y = 3;
    p_node = ESI_SDLIST_FIND_IF(point_repo_t, &point_repo, point_equal_to_preset);
    point.x = 2;
    point.y = 2;
    ESI_SDLIST_INSERT_BEFORE(point_repo_t, &point_repo, p_node, &point);
    printf("[INFO]: after inserting back (2,1) (2,2) (2,3)\n");
    print_sdlist_stat(&point_repo);
    inspect_in_order();

    return 0;
}