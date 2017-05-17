
#include "malloc.h"
#include <header.h>

typedef struct _free_node {
    size_t length;
    struct _free_node *prior;
    struct _free_node *next;
    char data[1];
} free_node, free_list;

#define page_size 4096
#define increment_size (32 * 4096)     // 128KB.
#define pointer_field  (2 * sizeof(void *))
#define pointer_off(x) ((char *)(x) + sizeof(size_t))
#define pointer_pfx(x) ((char *)(x) - sizeof(size_t))
#define length_all(x) ((x)->length + sizeof(size_t) + pointer_field)

static free_list g_flist = {0};
static size_t g_increment = increment_size;
static char *g_heap_begin = (char *)sbrk(0);    // heap begin pointer.
static char *g_heap_end = (char *)sbrk(0);

static
void* heap_malloc(size_t *size) {
    size_t s = *size;
    s = (s + g_increment - 1) / g_increment;
    s *= g_increment;
    if (s == 0)
        return nullptr;

    void *old_ptr;
    if ((old_ptr = sbrk(s)) == nullptr)
        return nullptr;

    g_heap_end = (char *)sbrk(0);
    *size  = size_t(g_heap_end - (char *)old_ptr);

    return old_ptr;
}

static
size_t heap_free(void *ptr) {
    if (ptr > g_heap_end || ptr < g_heap_begin) // error...
        return 0;

    size_t len;
    char *end = g_heap_end;
    if ((len = (size_t)(end - (char *)ptr)) > g_increment) {
        end -= g_increment;
        if (brk(end) == -1)
            return 0;

        g_heap_end = end;
        return g_increment;
    }

    return 0;
}

static
free_node *make_node(void *ptr) {
    return (free_node *)ptr;
}

void *i_malloc(size_t size) {
    if (size == 0)
        return nullptr;

    bool found = false;
    free_node *node = g_flist.next;
    free_node *prior;
    while (node != nullptr) {
        prior = node->prior;
        if (node->length >= size) {
            found = true;
            break;
        }
        node = node->next;
    }

    // first found.
    if (found) {
        if (node->length == size) {
            node->prior->next = node->next;
            node->next->prior = node->prior;
            node->length = size + pointer_field;
            return pointer_off(node);
        } else {
            free_node *new_node = make_node((char *)node + size + sizeof(size_t));
            new_node->length = node->length - size - pointer_field;
            new_node->next = node->next;
            new_node->prior = node->prior;

            node->prior->next = new_node;
            node->next->prior = new_node;

            return pointer_off(node);
        }
    }

    void *ptr;
    size_t len = size + sizeof(size_t);
    if ((ptr = heap_malloc(&len)) == nullptr)
        return nullptr;

    node = make_node(ptr);
    size_t left = len - size - sizeof(size_t);
    if (left > pointer_field + sizeof(size_t)) {
        free_node *new_node = make_node((char *)ptr + size + sizeof(size_t));
        new_node->length = left - pointer_field - sizeof(size_t);
        new_node->next = nullptr;
        new_node->prior = prior;

        prior->next = new_node;

        node->length = size;
    } else {
        node->length = len - sizeof(size_t);
    }

    return pointer_off(node);
}

void i_free(void *ptr) {
    if (ptr == nullptr)
        return;

    // forward merge.
    free_node *begin = (free_node *)pointer_pfx(ptr);
    size_t len = begin->length + sizeof(size_t);
    free_node *end = make_node((char *)begin + len);

    free_node *node = g_flist.next;
    free_node *prior;

    bool found = false;
    while (node != nullptr) {
        prior = node->prior;
        if (node == end) {
            found = true;
            break;
        }
        node = node->next;
    }

    begin->next = found ? node->next : nullptr;
    begin->prior = prior;
    begin->length -= pointer_field;
    begin->length += (found ? length_all(node) : 0) ;

    prior->next = begin;

    node = begin;

    free_node *tail = make_node((char *)prior + length_all(prior));
    if (tail == begin) {
        prior->next = begin->next;
        if (begin->next != nullptr)
            begin->next->prior = prior;

        prior->length += length_all(begin);
        node = prior;
    }

    char *pbegin = (char *)node + sizeof(size_t) + pointer_field;
    char *pend = (char *)node + length_all(node);
    if (pend == g_heap_end)
        node->length -= heap_free(pbegin);
}



