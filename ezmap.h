/* ezmap.h - Simple low-performance map structure.
 * See https://github.com/fordsfords/ezmap for documentation.
 *
 * This code and its documentation is Copyright 2025 Steven Ford,
 * http://geeky-boy.com and licensed "public domain" style under Creative
 * Commons "CC0": http://creativecommons.org/publicdomain/zero/1.0/
 * To the extent possible under law, the contributors to this project have
 * waived all copyright and related or neighboring rights to this work.
 * In other words, you can use this code for any purpose without any
 * restrictions. This work is published from: United States. The project home
 * is https://github.com/fordsfords/ezmap
 */

#ifndef EZMAP_H
#define EZMAP_H

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/* A key is a fixed-sized array of bytes. */
#define EZMAP_KEY_SIZE 128

typedef struct ezmap_node {
  unsigned char key[EZMAP_KEY_SIZE];
  void* value;
  struct ezmap_node* next;
} ezmap_node_t;

typedef struct ezmap {
  ezmap_node_t* head;
} ezmap_t;

ezmap_t* ezmap_create();
int ezmap_add(ezmap_t* map, const void* key, void* value);
void* ezmap_lookup(ezmap_t* map, const void* key);
void* ezmap_delete(ezmap_t* map, const void* key);


#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif  /* EZMAP_H */
