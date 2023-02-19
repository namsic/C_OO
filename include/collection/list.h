#ifndef __COLLECTION_LIST_H__
#define __COLLECTION_LIST_H__

struct ListInterface{
  unsigned int (*size)   (const struct ListInterface *self);
  void*        (*get)    (const struct ListInterface *self, const unsigned int index);

  void         (*insert) (struct ListInterface *self, const unsigned int index, void* value);
  void*        (*remove) (struct ListInterface *self, const unsigned int index);
};

struct ListInterface* newLinkedList();

#endif  // __COLLECTION_LIST_H__