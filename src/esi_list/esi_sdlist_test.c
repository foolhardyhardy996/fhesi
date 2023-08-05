#include "esi_sdlist.h"

#include <stdio.h>

struct point2d {
    int x;
    int y;
};

typedef struct point2d point2d_t;

#define POINT_REPO_CAP 9
ESI_SDLIST_DECL(point_repo_t, point2d_t, POINT_REPO_CAP);
ESI_SDLIST_IMPL(point_repo_t, point2d_t, POINT_REPO_CAP);

static point_repo_t point_repo;

static void inspect_in_order(void);
static void inspect_in_reverse_order(void);
static point_repo_t_node_t *index2node(int);
static int node2index(point_repo_t_node_t *);
static void inspect_free_list(void);
static void print_sdlist_stat(point_repo_t *);
static void print_node_stat(point_repo_t_node_t *);
static void init_test(void);

static point_repo_t_node_t *index2node(int index) {
    return &(point_repo.repo[index]);
}

static int node2index(point_repo_t_node_t *node) {
    return node - point_repo.repo;
}

static void inspect_free_list(void) {
    point_repo_t_node_t *node;
    node = index2node(point_repo.free_head);
    printf("[INFO]: inspect free list: ");
    while (node != NULL) {
        printf("%d ", node2index(node));
        node = point_repo_t_getNext(&point_repo, node);
    }
    printf("\n");
}

static void inspect_in_reverse_order(void) {
    point_repo_t_node_t *node;
    node = point_repo_t_peekBack(&point_repo);
    printf("[INFO]: inspect each node in reverse order:\n");
    while (node != NULL) {
        print_node_stat(node);
        node = point_repo_t_getPrev(&point_repo, node);
    }
}

static void inspect_in_order(void) {
    point_repo_t_node_t *node;
    node = point_repo_t_peekFront(&point_repo);
    printf("[INFO]: inspect each node in order:\n");
    while (node != NULL) {
        print_node_stat(node);
        node = point_repo_t_getNext(&point_repo, node);
    }
}

static void print_sdlist_stat(point_repo_t *repo) {
    printf(
        "point_repo_t{cap = %d, len = %d}\n", 
        point_repo_t_cap,
        point_repo_t_len(repo));
    inspect_free_list();
    inspect_in_order();
    inspect_in_reverse_order();
}

static void print_node_stat(point_repo_t_node_t *node) {
    printf("node{point{x = %d, y = %d}, index = %d, prev = %d, prev = %d}\n", node->elem.x, node->elem.y, node2index(node), node->prev, node->next);
} 

static void init_test(void) {
    point2d_t point;
    
    point_repo_t_init(&point_repo);
    printf("[INFO]: after init\n");
    print_sdlist_stat(&point_repo);
    point.x = 2;
    point.y = 1;
    point_repo_t_insertFront(&point_repo, &point);
    printf("[INFO]: after insertFront (2,1).\n");
    print_sdlist_stat(&point_repo);
    point.x = 2;
    point.y = 2;
    point_repo_t_insertBack(&point_repo, &point);
    printf("[INFO]: after insertBack (2,2).\n");
    print_sdlist_stat(&point_repo);
    point.x = 2;
    point.y = 3;
    point_repo_t_insertBack(&point_repo, &point);
    printf("[INFO]: after insertBack (2,3).\n");
    print_sdlist_stat(&point_repo);
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

static point_repo_t_node_t *find_point_node(point_repo_t *, point2d_t *);
static point_repo_t_node_t *find_point_node(point_repo_t *repo, point2d_t *point) {
    point_repo_t_node_t *node;
    node = point_repo_t_peekFront(repo);
    preset_point = *point;
    while(node != NULL) {
        if (point_equal_to_preset(&(node->elem))) {
            return node;
        }
        node = point_repo_t_getNext(repo, node);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    point2d_t point;
    point_repo_t_node_t *node;
    int ret;

    init_test();

    // push front (1,1) (1,2) (1,3)
    point.x = 1;
    point.y = 3;
    point_repo_t_insertFront(&point_repo, &point);
    point.x = 1;
    point.y = 2;
    point_repo_t_insertFront(&point_repo, &point);
    point.x = 1;
    point.y = 1;
    point_repo_t_insertFront(&point_repo, &point);
    printf("[INFO]: after pushing front (1,3) (1,2) (1,1)\n");
    print_sdlist_stat(&point_repo);

    // push back (3,1) (3,2) (3,3)
    point.x = 3;
    point.y = 1;
    point_repo_t_insertBack(&point_repo, &point);
    point.x = 3;
    point.y = 2;
    point_repo_t_insertBack(&point_repo, &point);
    point.x = 3;
    point.y = 3;
    point_repo_t_insertBack(&point_repo, &point);
    printf("[INFO]: after pushing front (1,3) (1,2) (1,1)\n");
    print_sdlist_stat(&point_repo);

    // now, more push should fail
    point.x = -1;
    point.y = -1;
    ret = point_repo_t_insertBack(&point_repo, &point);
    printf("[INFO]: push back when in cap, it reports: %s\n", esi_sdlist_strerror(ret));
    ret = point_repo_t_insertFront(&point_repo, &point);
    printf("[INFO]: push front when in cap, it reports: %s\n", esi_sdlist_strerror(ret));
    printf("[INFO]: after pushing when in cap\n");
    print_sdlist_stat(&point_repo);

    // delete (2,1) (2,2) (2,3)
    preset_point.x = 2;
    preset_point.y = 1;
    node = find_point_node(&point_repo, &preset_point);
    printf("[INFO]: after find (2,1)\n");
    print_node_stat(node);
    point_repo_t_delete(&point_repo, node);
    printf("[INFO]: after delete (2,1)\n");
    print_sdlist_stat(&point_repo);
    preset_point.x = 2;
    preset_point.y = 2;
    node = find_point_node(&point_repo, &preset_point);
    printf("[INFO]: after find (2,2)\n");
    print_node_stat(node);
    point_repo_t_delete(&point_repo, node);
    printf("[INFO]: after delete (2,1)\n");
    print_sdlist_stat(&point_repo);
    preset_point.x = 2;
    preset_point.y = 3;
    node = find_point_node(&point_repo, &preset_point);
    printf("[INFO]: after find (2,3)\n");
    print_node_stat(node);
    point_repo_t_delete(&point_repo, node);
    printf("[INFO]: after deleting (2,1) (2,2) (2,3)\n");
    print_sdlist_stat(&point_repo);

    // insert (2,1) (2,2) (2,3) back
    preset_point.x = 1;
    preset_point.y = 3;
    node = find_point_node(&point_repo, &preset_point);
    point.x = 2;
    point.y = 1;
    point_repo_t_insertAfter(&point_repo, node, &point);
    preset_point.x = 2;
    preset_point.y = 1;
    node = find_point_node(&point_repo, &preset_point);    
    point.x = 2;
    point.y = 3;
    point_repo_t_insertAfter(&point_repo, node, &point);    
    preset_point.x = 2;
    preset_point.y = 3;
    node = find_point_node(&point_repo, &preset_point);
    point.x = 2;
    point.y = 2;
    point_repo_t_insertBefore(&point_repo, node, &point);
    printf("[INFO]: after inserting back (2,1) (2,2) (2,3)\n");
    print_sdlist_stat(&point_repo);

    return 0;
}