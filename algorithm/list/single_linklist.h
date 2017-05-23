//
// \file single_linklist.h
// \brief single linked list.
//

#if !defined(algorithm_single_linklist_h__)
#define algorithm_single_linklist_h__

struct single_linknode;
typedef struct single_linknode single_linklist;

// api defs.

single_linklist* list_initialize();
void list_finalize(single_linklist *list);
void list_clear(single_linklist *list);
bool list_empty(single_linklist const *list);
size_t list_length(single_linklist const *list);

// element operate.
bool get_element(single_linklist const *list, int i, T *elem);
int locate_element(single_linklist const *list, T elem1, bool (*compare)(T elem1, T elem2));
bool prior_element(single_linklist const *list, T elem, T *prior_elem);
bool next_element(single_linklist const *list, T elem, T *next_elem);

// list operate.
bool list_insert(single_linklist *list, int i, T elem);
bool list_delete(single_linklist *list, int i, T *elem);

// traverse operate.
void list_traverse(single_linklist const *list, void (*visit)(T elem));

#endif // algorithm_single_linklist_h__
