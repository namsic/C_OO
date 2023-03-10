#include <stdlib.h>

#include "../test-util.h"
#include "collection/map.h"

bool interfaceTest(struct MapInterface *map)
{
  DO_TEST(map && map->size(map) == 0);

  return true;
}

int main()
{
  bool result = true;
  pushTestGroup("Map");

  pushTestGroup("HashMap");
  result &= interfaceTest(newHashMap());
  popTestGroup();

  return !result;
}