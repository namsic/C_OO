#ifndef __COLLECTION_MAP_H__
#define __COLLECTION_MAP_H__

struct MapInterface
{
  unsigned int (*size) (const struct MapInterface *self);
  void*        (*get)  (const struct MapInterface *self, const unsigned int index);

  void  (*add)    (struct MapInterface *self, const unsigned int index, void *value);
  void* (*remove) (struct MapInterface *self, const unsigned int index);
};

#endif  // __COLLECTION_LIST_H__