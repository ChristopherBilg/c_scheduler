// Obtained publically and freely (open-source) at https://www.geeksforgeeks.org/queue-set-2-linked-list-implementation/
// Only the general outline was used from the above source.

#ifndef _HEADER_NAME_
#define _HEADER_NAME_
#endif

struct QNode
{
	int job;
	struct QNode *next;
};

struct Queue
{
	struct QNode *front, *rear;
  int size;
};

struct QNode* newNode(int k);
struct Queue *createQueue();
void destroyQueue(struct Queue *queue);
void enQueue(struct Queue *q, int job);
struct QNode *deQueue(struct Queue *q);
