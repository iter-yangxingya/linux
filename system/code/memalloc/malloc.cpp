
#include "malloc.h"
#include <header.h>
#include <debug.h>

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

static free_list g_flist = {0, nullptr, nullptr, ""};
static size_t g_increment = increment_size;
static char *g_heap_begin = (char *)sbrk(0);    // heap begin pointer.
static char *g_heap_end = (char *)sbrk(0);

static
void* heap_malloc(size_t *size) {
    debug_out << "heap malloc begin size=" << *size;

    size_t s = *size;

    s = (s + g_increment - 1) / g_increment;
    s *= g_increment;
    if (s == 0)
        return nullptr;

    debug_out << "heap malloc really size=" << s;

    void *old_ptr;
    if ((old_ptr = sbrk(s)) == nullptr) {
        debug_out << "heap malloc sbrk(" << s << ") failed!";
        return nullptr;
    }

    g_heap_end = (char *)sbrk(0);
    *size  = size_t(g_heap_end - (char *)old_ptr);

    debug_out << "heap malloc end..." << *size;
    return old_ptr;
}

static
size_t heap_free(void *ptr) {
    debug_out << "heap free begin";

    if (ptr > g_heap_end || ptr < g_heap_begin) {
        // error...
        debug_out << "heap free but pointer not in heap range";
        return 0;
    }

    size_t len;
    char *end = g_heap_end;
    if ((len = (size_t)(end - (char *)ptr)) > g_increment) {
        size_t release = len / g_increment * g_increment;
        end -= release;
        if (brk(end) == -1) {
            debug_out << "heap free call brk() call failed";
            return 0;
        }

        debug_out << "heap free call brk() succeed, release size=" << release;
        g_heap_end = end;
        return release;
    }

    debug_out << "heap free release size too small, no release";
    debug_out << "heap free end";
    return 0;
}

static
free_node *make_node(void *ptr) {
    return (free_node *)ptr;
}

void *i_malloc(size_t size) {
    debug_out << "i_malloc begin size=" << size;

    if (size == 0) {
        debug_out << "i_malloc size is zero";
        return nullptr;
    }

    bool found = false;
    free_node *node = g_flist.next;
    free_node *prior = &g_flist;
    while (node != nullptr) {
        prior = node->prior;
        if (node->length >= size) {
            found = true;
            debug_out << "i_malloc found a free node";
            break;
        }
        node = node->next;
    }

    // first found.
    if (found) {
        if (node->length == size) {
            debug_out << "i_malloc found a free node, match";
            node->prior->next = node->next;
            node->next->prior = node->prior;
            node->length = size + pointer_field;
            return pointer_off(node);
        } else {
            debug_out << "i_malloc found a free node, NO match, split";
            free_node *new_node = make_node((char *)node + size + sizeof(size_t));
            new_node->length = node->length - size - pointer_field;
            new_node->next = node->next;
            new_node->prior = node->prior;

            node->prior->next = new_node;
            node->next->prior = new_node;
            return pointer_off(node);
        }
    }

    debug_out << "i_malloc NO found a free node";

    void *ptr;
    size_t len = size + sizeof(size_t);
    if ((ptr = heap_malloc(&len)) == nullptr) {
        debug_out << "i_malloc call heap malloc failed";
        return nullptr;
    }
    debug_out << "i_malloc call heap malloc size=" << len;

    node = make_node(ptr);
    size_t left = len - size - sizeof(size_t);
    debug_out << "i_malloc call heap malloc used, left=" << left;
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

    debug_out << "i_malloc end";
    return pointer_off(node);
}

void i_free(void *ptr) {
    debug_out << "i_free begin";

    if (ptr == nullptr) {
        debug_out << "i_free but input pointer is nullptr";
        return;
    }

    // forward merge.
    free_node *begin = (free_node *)pointer_pfx(ptr);
    size_t len = begin->length + sizeof(size_t);
    free_node *end = make_node((char *)begin + len);

    free_node *node = g_flist.next;
    free_node *prior = &g_flist;

    bool found = false;
    while (node != nullptr) {
        prior = node->prior;
        if (node == end) {
            found = true;
            debug_out << "i_free found a free node is begin with the free node tail";
            break;
        }
        node = node->next;
    }

    begin->next = found ? node->next : nullptr;
    begin->prior = prior;
    begin->length -= pointer_field;
    begin->length += (found ? length_all(node) : 0) ;

    prior->next = begin;

    debug_out << "i_free merge free node and next node";
    node = begin;

    free_node *tail = make_node((char *)prior + length_all(prior));
    if (tail == begin) {
        prior->next = begin->next;
        if (begin->next != nullptr)
            begin->next->prior = prior;

        prior->length += length_all(begin);

        debug_out << "i_free merge free node and prior node";

        node = prior;
    }

    char *pbegin = (char *)node + sizeof(size_t) + pointer_field;
    char *pend = (char *)node + length_all(node);
    if (pend == g_heap_end) {
        debug_out << "list tail is end with heap end, so need do clean once";
        node->length -= heap_free(pbegin);
    }
    debug_out << "i_free end";
}



