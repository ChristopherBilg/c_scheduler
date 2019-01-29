// Obtained publically and freely (open-source) at https://www.geeksforgeeks.org/queue-set-2-linked-list-implementation/
// Only the general outline was used from the above source.

#include <stdlib.h>
#include <stdio.h>
#include "fifo_queue.h"

// A utility function to create a new linked list node.
struct QNode* newNode(int job) {
  struct QNode *temp = (struct QNode*)malloc(sizeof(struct QNode));
  temp->job = job;
  temp->next = NULL;
  return temp;
}

// A utility function to create an empty queue
struct Queue *createQueue() {
  struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
  q->front = q->rear = NULL;
  q->size = 0;
  q->statistics_max_size = 0;
  return q;
}

// Destroy a queue in memory
void destroyQueue(struct Queue *queue) {
  free(queue);
}

// The function to add a key k to q
void enQueue(struct Queue *q, int job) {
  // Create a new LL node
  struct QNode *temp = newNode(job);

  q->size++;
  // Statistics
  if (q->statistics_max_size < q->size)
    q->statistics_max_size = q->size;
  
  // If queue is empty, then new node is front and rear both
  if (q->rear == NULL)
  {
    q->front = q->rear = temp;
    q->size = 1;
    return;
  }

  // Add the new node at the end of queue and change rear
  q->rear->next = temp;
  q->rear = temp;
}

// Function to remove a key from given queue q
struct QNode *deQueue(struct Queue *q) {
  // If queue is empty, return NULL.
  if (q->front == NULL) {
    q->size = 0;
    return NULL;
  }

  // Store previous front and move front one node ahead
  struct QNode *temp = q->front;
  q->front = q->front->next;
  q->size--;

  // If front becomes NULL, then change rear also as NULL
  if (q->front == NULL)
    q->rear = NULL;
  return temp;
}
