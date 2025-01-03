#include "asv.h"

void asv_pqueue_init(asv_PQueue *queue) {
  queue->front = NULL;
  queue->rear = NULL;
  queue->size = 0;
}

int asv_pqueue_pop(asv_PQueue *queue, int *priority) {
  if (queue->size == 0) {
    return INT_MIN;
  }

  asv_QueueElement *current = queue->front;
  if (priority) {
    *priority = current->priority;
  }
  int value = current->value;

  if (!current->next) {
    queue->front = NULL;
    queue->rear = NULL;
  }
  else {
    queue->front = current->next;
    queue->front->prev = NULL;
  }

  free(current);
  queue->size--;
  return value;
}

void asv_pqueue_push(asv_PQueue *queue, int value, int priority) {
  asv_QueueElement *new_element = (asv_QueueElement *) malloc(sizeof(asv_QueueElement));
  new_element->value = value;
  new_element->priority = priority;
  new_element->next = NULL;
  new_element->prev = NULL;

  asv_QueueElement *current = queue->rear;
  if (!queue->rear) {
    queue->rear = new_element;
    queue->front = new_element;
  }
  else {
    while (current && current->priority < priority) {
      current = current->prev;
    }

    if (!current) {
      new_element->next = queue->front;
      queue->front->prev =new_element;
      queue->front = new_element;
    }
    else {
      new_element->next = current->next;
      if (current->next) {
        current->next->prev = new_element;
      }
      current->next = new_element;
    }
  }
  queue->size++;
}

void asv_pqueue_free(asv_PQueue *queue) {
  while (queue->front) {
    asv_QueueElement *temp = queue->front;
    queue->front = queue->front->next;
    free(temp);
  }
  queue->front = NULL;
  queue->rear = NULL;
  queue->size = 0;
}
