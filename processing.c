#include <stdbool.h>
#include <stdlib.h>
#include "processing.h"

_Bool process_cpu(struct Queue *queue, struct priority_queue *p_queue, _Bool idle, int current_time) {
  // cpu is currently in progress.
  if (idle == false)
    return false;

  // if empty
  if (queue->front == NULL)
    return true;

  struct QNode *node = deQueue(queue);
  push_to_priority_queue(p_queue, current_time, node->job, CPU_ARRIVED);
  
  return true;
}

_Bool process_disk1(struct Queue *queue, struct priority_queue *p_queue, _Bool idle, int current_time) {
  // disk is currently in progress.
  if (idle == false)
    return false;

  // if empty
  if (queue->front == NULL)
    return true;
  
  struct QNode *node = deQueue(queue);
  push_to_priority_queue(p_queue, current_time, node->job, DISK1_ARRIVED);
  
  return false;
}

_Bool process_disk2(struct Queue *queue, struct priority_queue *p_queue, _Bool idle, int current_time) {
  // disk is currently in progress.
  if (idle == false)
    return false;

  // if empty
  if (queue->front == NULL)
    return true;
  
  struct QNode *node = deQueue(queue);
  push_to_priority_queue(p_queue, current_time, node->job, DISK2_ARRIVED);
  
  return false;
}
