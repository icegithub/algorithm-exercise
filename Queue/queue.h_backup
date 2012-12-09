#ifndef _QUEUE_H
#define _QUEUE_H

#define INITLENGTH 10

typedef int status;
typedef int qElemType; 

typedef struct queueNode {
     qElemType vector[INITLENGTH];
     struct queueNode *next;
}queueNode, *queuePtr;

typedef struct {
     queuePtr front; //the front( head ) point
     queuePtr rear;  //the rear( taile ) point
}linkQueue;

/* create a queue */
status initQueue( linkQueue *q );

/* destory a queue */
status destroyQueue( linkQueue *q );

/* clear a queue */
status clearQueue( linkQueue *q );

/* if queue is empty return true or return false */
status queueEmpty( linkQueue q );

/* return the length of the queue */
int    queueLength( linkQueue q );

/*
 * if queue is not empty and 
 * return head by e and reuturn OK
 * else reutnr ERROR
 */
status getHead( linkQueue q, qElemType *e );

/*
 * put the e into the tail( rear ) of the queue
*/
status enQueue( linkQueue *q, qElemType e );

/*
 * if queue is not empty, delete the head element and
 * return the the head element by e, return OK
 * or return ERROR
 */
status deQueue( linkQueue *q, qElemType *e );

#endif
