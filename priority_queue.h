#ifndef _HEADER_NAME_
#define _HEADER_NAME_
#endif

enum EVENT {
  SIM_STARTING,
  SIM_ENDING,
  ARRIVED,
  FINISHED,
  CPU_ARRIVED,
  CPU_FINISHED,
  DISK1_ARRIVED,
  DISK1_FINISHED,
  DISK2_ARRIVED,
  DISK2_FINISHED
};

struct priority_node {
  int priority;
  int job;
  enum EVENT event;
};

struct priority_queue {
  struct priority_node *all_nodes;
  int length;
  int max_length;
  int statistics_max_size;
};

struct priority_queue initialize_priority_queue(int number_of_elements);
void destroy_priority_queue(struct priority_queue *queue);
void swap_nodes(struct priority_node *a, struct priority_node *b);
_Bool push_to_priority_queue(struct priority_queue *queue, int priority, int job, enum EVENT event);
struct priority_node pop_from_priority_queue(struct priority_queue *queue);
_Bool priority_queue_is_empty(struct priority_queue *queue);
_Bool priority_queue_is_full(struct priority_queue *queue);
void print_priority_queue(struct priority_queue *queue);
