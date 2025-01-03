#include "asv.h"

void asv_hashmap_init(asv_HashMap *map) {
  for (int i = 0; i < HASH_CAPACITY; i++) {
    map->buffer[i] = NULL;
  }
  map->size = 0;
}

void asv_hashmap_add(asv_HashMap *map, int key, int value) {
  if (key < 0) {
    return;
  }

  int index = key % HASH_CAPACITY;

  if (asv_hashmap_get(map, key) != -1) {
    asv_HashBucket *current = map->buffer[index];
    while (current->key != key) {
      current = current->next;
    }

    current->value = value;
  }
  else {
    asv_HashBucket *new_bucket = (asv_HashBucket *) malloc(sizeof(asv_HashBucket));
    new_bucket->key = key;
    new_bucket->value = value;
    new_bucket->next = map->buffer[index];
    map->buffer[index] =new_bucket;
  }
}

int asv_hashmap_get(asv_HashMap *map, int key) {
  if (key < 0) {
    return -1;
  }

  int index = key % HASH_CAPACITY;
  asv_HashBucket *current = map->buffer[key];
  while (current) {
    if (current->key == key) {
      return current->value;
    }
    current = current->next;
  }

  return -1;
}

void asv_hashmap_remove(asv_HashMap *map, int key) {
  if (key < 0) {
    return;
  }

  int index = key % HASH_CAPACITY;
  asv_HashBucket *prev = NULL;
  asv_HashBucket *current = map->buffer[index];

  while (current->key != key) {
    current = current->next;
  }

  if (prev) {
    prev->next = current->next;
  }
  else {
    map->buffer[index] = NULL;
  }
  free(current);
}

void asv_hashmap_free(asv_HashMap *map) {
  for (int i = 0; i < HASH_CAPACITY; i++) {
    asv_HashBucket *current = map->buffer[i];
    while (current) {
      asv_HashBucket *temp = current;
      current = current->next;
      free(temp);
    }
  }
  map->size = 0;
}
