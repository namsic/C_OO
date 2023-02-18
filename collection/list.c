#include "list.h"

#include <stdlib.h>
#include <assert.h>

struct Node
{
  void* value;
  struct Node *next;
};

struct LinkedList
{
  struct ListInterface interface;
  unsigned int size;
  struct Node *head;
};

static unsigned int linkedListSize(const struct ListInterface *self)
{
  struct LinkedList *linked_list = (struct LinkedList*)self;
  assert(linked_list);
  return linked_list->size;
}

static void* linkedListGet(const struct ListInterface *self,
                           const unsigned int index)
{
  struct LinkedList *linked_list = (struct LinkedList*)self;
  assert(linked_list);
  assert(index <= linked_list->size);

  struct Node *curr = linked_list->head;
  for (int i=0; i<index; i++) curr = curr->next;
  return curr->value;
}

static void linkedListInsert(struct ListInterface *self,
                             const unsigned int index,
                             void* value)
{
  struct LinkedList *linked_list = (struct LinkedList*)self;
  assert(linked_list);
  assert(index <= linked_list->size);

  struct Node *new_node = malloc(sizeof(struct Node));
  assert(new_node);
  new_node->value = value;

  struct Node *prev = NULL;
  struct Node *curr = linked_list->head;
  for (int i=0; i<index; i++) {
    prev = curr;
    curr = curr->next;
  }

  if (prev) prev->next = new_node;
  else linked_list->head = new_node;

  new_node->next = curr;
  linked_list->size += 1;
}

static void* linkedListRemove(struct ListInterface *self,
                             const unsigned int index)
{
  struct LinkedList *linked_list = (struct LinkedList*)self;
  assert(linked_list);
  assert(index < linked_list->size);

  struct Node *prev = NULL;
  struct Node *curr = linked_list->head;
  for (int i=0; i<index; i++) {
    prev = curr;
    curr = curr->next;
  }

  if (prev) prev->next = curr->next;
  else linked_list->head = curr->next;

  void *ret = curr->value;
  free(curr);
  linked_list->size -= 1;
  return ret;
}

struct ListInterface* newLinkedList()
{
  struct LinkedList *ret = malloc(sizeof(struct LinkedList));
  assert(ret);

  struct LinkedList linked_list = {
    .head = NULL,
    .size = 0,
    .interface = {
      .size   = linkedListSize,
      .get    = linkedListGet,
      .insert = linkedListInsert,
      .remove = linkedListRemove
    }
  };

  *ret = linked_list;
  return (struct ListInterface*)ret;
}