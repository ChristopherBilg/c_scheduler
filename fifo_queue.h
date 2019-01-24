// Obtained publically and freely (open-source) at https://www.geeksforgeeks.org/queue-set-2-linked-list-implementation/
// Obtained publically and freely (open-source) at https://www.geeksforgeeks.org/queue-set-2-linked-list-implementation/
// Professor Kwatny allowed the use of public domain works in our projects.

#ifndef _HEADER_NAME_
#define _HEADER_NAME_
#endif

// A linked list (LL) node to store a queue entry 
struct QNode
{
	int key;
	struct QNode *next;
};

// The queue, front stores the front node of LL and rear stores ths 
// last node of LL 
struct Queue
{
	struct QNode *front, *rear;
};

struct QNode* newNode(int k);
struct Queue *createQueue();
void destroyQueue(struct Queue *queue);
void enQueue(struct Queue *q, int k);
struct QNode *deQueue(struct Queue *q);
