#include <assert.h>
#include <stdlib.h>

#include "test_util.h"
#include "collection/list.h"

static void listTest(struct ListInterface *list)
{
  assert(list->size(list) == 0);

  int *elem;

  // insert to empty
  list->add(list, 0, Int(10));
  assert(list->size(list) == 1);
  elem = list->get(list, 0); assert(*elem == 10);

  // insert to head
  list->add(list, 0, Int(20));
  assert(list->size(list) == 2);
  elem = list->get(list, 0); assert(*elem == 20);
  elem = list->get(list, 1); assert(*elem == 10);

  // insert to mid
  list->add(list, 1, Int(30));
  assert(list->size(list) == 3);
  elem = list->get(list, 0); assert(*elem == 20);
  elem = list->get(list, 1); assert(*elem == 30);
  elem = list->get(list, 2); assert(*elem == 10);

  // insert to tail
  list->add(list, 3, Int(40));
  assert(list->size(list) == 4);
  elem = list->get(list, 0); assert(*elem == 20);
  elem = list->get(list, 1); assert(*elem == 30);
  elem = list->get(list, 2); assert(*elem == 10);
  elem = list->get(list, 3); assert(*elem == 40);

  // remove to head
  elem = list->remove(list, 0);
  assert(*elem == 20 && list->size(list) == 3);
  free(elem);
  elem = list->get(list, 0); assert(*elem == 30);
  elem = list->get(list, 1); assert(*elem == 10);
  elem = list->get(list, 2); assert(*elem == 40);

  // remove to mid
  elem = list->remove(list, 1);
  assert(*elem == 10 && list->size(list) == 2);
  free(elem);
  elem = list->get(list, 0); assert(*elem == 30);
  elem = list->get(list, 1); assert(*elem == 40);

  // remove to tail
  elem = list->remove(list, 1);
  assert(*elem == 40 && list->size(list) == 1);
  free(elem);
  elem = list->get(list, 0); assert(*elem == 30);
}

int main()
{
  struct ListInterface *list = newLinkedList();
  listTest(list);
  free(list);

  return 0;
}