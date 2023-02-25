#include <stdlib.h>
#include <stdbool.h>

#include "../test-util.h"
#include "collection/list.h"

int* Int(int value) {
  int *ret = malloc(sizeof(int));
  *ret = value;
  return ret;
}

static bool interfaceTest(struct ListInterface *list)
{
  DO_TEST(list && list->size(list) == 0);

  int *elem;

  // insert to empty
  list->add(list, 0, Int(10));
  DO_TEST(list->size(list) == 1);
  elem = list->get(list, 0); DO_TEST(*elem == 10);

  // insert to head
  list->add(list, 0, Int(20));
  DO_TEST(list->size(list) == 2);
  elem = list->get(list, 0); DO_TEST(*elem == 20);
  elem = list->get(list, 1); DO_TEST(*elem == 10);

  // insert to mid
  list->add(list, 1, Int(30));
  DO_TEST(list->size(list) == 3);
  elem = list->get(list, 0); DO_TEST(*elem == 20);
  elem = list->get(list, 1); DO_TEST(*elem == 30);
  elem = list->get(list, 2); DO_TEST(*elem == 10);

  // insert to tail
  list->add(list, 3, Int(40));
  DO_TEST(list->size(list) == 4);
  elem = list->get(list, 0); DO_TEST(*elem == 20);
  elem = list->get(list, 1); DO_TEST(*elem == 30);
  elem = list->get(list, 2); DO_TEST(*elem == 10);
  elem = list->get(list, 3); DO_TEST(*elem == 40);

  // remove to head
  elem = list->remove(list, 0);
  DO_TEST(*elem == 20 && list->size(list) == 3);
  free(elem);
  elem = list->get(list, 0); DO_TEST(*elem == 30);
  elem = list->get(list, 1); DO_TEST(*elem == 10);
  elem = list->get(list, 2); DO_TEST(*elem == 40);

  // remove to mid
  elem = list->remove(list, 1);
  DO_TEST(*elem == 10 && list->size(list) == 2);
  free(elem);
  elem = list->get(list, 0); DO_TEST(*elem == 30);
  elem = list->get(list, 1); DO_TEST(*elem == 40);

  // remove to tail
  elem = list->remove(list, 1);
  DO_TEST(*elem == 40 && list->size(list) == 1);
  free(elem);
  elem = list->get(list, 0); DO_TEST(*elem == 30);

  return true;
}

int main()
{
  bool result = true;
  pushTestGroup("List");

  pushTestGroup("Linked list");
  result &= interfaceTest(newLinkedList());
  popTestGroup();

  return !result;
}