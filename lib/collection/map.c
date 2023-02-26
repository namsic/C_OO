#include "collection/map.h"

#include <stdlib.h>
#include <assert.h>

struct HashMap
{
  struct MapInterface interface;
  unsigned int size;
};

static unsigned int hashMapSize(const struct MapInterface *self)
{
  assert(self);
  struct HashMap *map = (struct HashMap*)self;

  return map->size;
}

static void* hashMapGet(const struct MapInterface *self, const unsigned int index)
{
  return NULL;
}

void hashMapAdd(struct MapInterface *self, const unsigned int index, void *value)
{
}

void* hashMapRemove(struct MapInterface *self, const unsigned int index)
{
  return NULL;
}

struct MapInterface* newHashMap()
{
  struct HashMap *ret = malloc(sizeof(struct HashMap));
  assert(ret);

  struct HashMap hash_map = {
    .size = 0,
    .interface = {
      .size   = hashMapSize,
      .get    = hashMapGet,
      .add    = hashMapAdd,
      .remove = hashMapRemove
    }
  };

  *ret = hash_map;
  return (struct MapInterface*)ret;
}