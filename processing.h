#ifndef _HEADER_NAME_
#define _HEADER_NAME_
#endif

#include <stdbool.h>
#include "fifo_queue.h"
#include "priority_queue.h"

_Bool process_cpu(struct Queue *queue, struct priority_queue *p_queue, _Bool idle, int current_time);
_Bool process_disk1(struct Queue *queue, struct priority_queue *p_queue, _Bool idle, int current_time);
_Bool process_disk2(struct Queue *queue, struct priority_queue *p_queue, _Bool idle, int current_time);
