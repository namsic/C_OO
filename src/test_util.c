#include "test_util.h"

#include <stdlib.h>
#include <assert.h>

int* Int(int value)
{
  int *ret = malloc(sizeof(int));
  assert(ret);
  *ret = value;
  return ret;
}
