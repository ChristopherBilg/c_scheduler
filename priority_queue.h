#ifndef _HEADER_NAME_
#define _HEADER_NAME_
#endif

struct priority_node {
  int priority;
  char *data;
};

struct priority_queue {
  struct priority_node *all_nodes;
  int length;
  int max_length;
};

_Bool initialize_priority_queue(struct priority_queue *queue, int number_of_elements);
void destroy_priority_queue(struct priority_queue *queue);
void swap_nodes(struct priority_node *a, struct priority_node *b);
_Bool push_to_priority_queue(struct priority_queue *queue, int priority, char *data);
char* pop_from_priority_queue(struct priority_queue *queue);
_Bool priority_queue_is_empty(struct priority_queue *queue);
_Bool priority_queue_is_full(struct priority_queue *queue);
void print_priority_queue(struct priority_queue *queue);
