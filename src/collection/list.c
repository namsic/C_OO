#include "collection/list.h"

#include <stdlib.h>
#include <assert.h>

struct Node
{
  void *value;
  struct Node *next;
};

struct LinkedList
{
  struct ListInterface interface;
  unsigned int size;
  struct Node *head;
};

static struct Node* getNthNode(const struct LinkedList *linked_list,
                               const unsigned int index, struct Node **prev)
{
  assert(linked_list && index <= linked_list->size);

  struct Node *curr = linked_list->head;
  if (prev) *prev = NULL;

  for (int i=0; i<index; i++) {
    if (prev) *prev = curr;
    curr = curr->next;
  }

  return curr;
}

static unsigned int linkedListSize(const struct ListInterface *self)
{
  assert(self);
  struct LinkedList *list = (struct LinkedList*)self;

  return list->size;
}

static void* linkedListGet(const struct ListInterface *self,
                           const unsigned int index)
{
  assert(self);
  struct LinkedList *list = (struct LinkedList*)self;

  struct Node *node = getNthNode(list, index, NULL);
  assert(node);

  return node->value;
}

static void linkedListAdd(struct ListInterface *self, const unsigned int index,
                          void *value)
{
  assert(self);
  struct LinkedList *list = (struct LinkedList*)self;

  struct Node *new_node = malloc(sizeof(struct Node));
  assert(new_node);
  new_node->value = value;

  struct Node *prev;
  struct Node *node = getNthNode(list, index, &prev);

  if (prev) prev->next = new_node;
  else list->head = new_node;

  new_node->next = node;
  list->size += 1;
}

static void* linkedListRemove(struct ListInterface *self,
                              const unsigned int index)
{
  assert(self);
  struct LinkedList *list = (struct LinkedList*)self;

  struct Node *prev;
  struct Node *node = getNthNode(list, index, &prev);
  assert(node);

  if (prev) prev->next = node->next;
  else list->head = node->next;
  list->size -= 1;

  void *ret = node->value;
  free(node);

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
      .add    = linkedListAdd,
      .remove = linkedListRemove
    }
  };

  *ret = linked_list;
  return (struct ListInterface*)ret;
}