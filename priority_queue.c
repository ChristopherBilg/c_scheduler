#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "priority_queue.h"

struct priority_queue initialize_priority_queue(int number_of_elements) {
  if (number_of_elements <= 0)
    number_of_elements = 100000;

  struct priority_queue queue = {NULL, 0, 0};

  queue.length = 0;
  queue.max_length = number_of_elements;
  queue.all_nodes = (struct priority_node *)realloc(queue.all_nodes,
                                                     number_of_elements * sizeof(struct priority_node));

  return queue;
}

void destroy_priority_queue(struct priority_queue *queue) {
  free(queue->all_nodes);
}

void swap_nodes(struct priority_node *a, struct priority_node *b) {
  struct priority_node temp = *a;
  *a = *b;
  *b = temp;
}

_Bool push_to_priority_queue(struct priority_queue *queue, int priority, char *data) {
  if (priority_queue_is_full(queue))
    return false;

  queue->all_nodes[queue->length].priority = priority;
  queue->all_nodes[queue->length].data = data;

  int new = queue->length;
  int next = queue->length - 1;

  while (queue->all_nodes[new].priority < queue->all_nodes[next].priority) {
    swap_nodes(&queue->all_nodes[new], &queue->all_nodes[next]);
    new--;
    next--;
  }

  queue->length++;
  
  return true;
}

// Higher number equates to higher priority
// (Needs to be tested) Lower number should now equate to higher priority
char* pop_from_priority_queue(struct priority_queue *queue) {
  if (priority_queue_is_empty(queue))
    return "ERR: The priority queue is empty.";

  //char* data = queue->all_nodes[queue->length-1].data;
  //queue->length--;
  //return data;

  char* data = queue->all_nodes[0].data;
  for (int i = 0; i < queue->length; i++)
    swap_nodes(&queue->all_nodes[i], &queue->all_nodes[i+1]);
  
  queue->length--;
  return data;
}

_Bool priority_queue_is_empty(struct priority_queue *queue) {
  return true ? queue->length == 0 : false;
}

_Bool priority_queue_is_full(struct priority_queue *queue) {
  return true ? queue->length == queue->max_length : false;
}

void print_priority_queue(struct priority_queue *queue) {
  for (int i=0; i < queue->length; i++) {
    struct priority_node node = queue->all_nodes[i];
    printf("[%d] %s\n", node.priority, node.data);
  }
}
