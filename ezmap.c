/* ezmap.c - Simple low-performance map structure.
 * See https://github.com/fordsfords/ezmap for documentation.
 *
 * This code and its documentation is Copyright 2025, 2025 Steven Ford,
 * http://geeky-boy.com and licensed "public domain" style under Creative
 * Commons "CC0": http://creativecommons.org/publicdomain/zero/1.0/
 * To the extent possible under law, the contributors to this project have
 * waived all copyright and related or neighboring rights to this work.
 * In other words, you can use this code for any purpose without any
 * restrictions. This work is published from: United States. The project home
 * is https://github.com/fordsfords/ezmap
 *
 * Thanks to Claude.ai for assistance in writing this module.
 */

#include <stdlib.h>
#include <string.h>
#include "ezmap.h"


ezmap_t* ezmap_create() {
  ezmap_t* map = malloc(sizeof(ezmap_t));
  if (map == NULL) { return NULL; }  /* Handle error. */

  map->head = NULL;
  return map;
}  /* ezmap_create */


int ezmap_add(ezmap_t* map, void* key, void* value) {
  if (map == NULL || key == NULL) { return -1; }  /* Handle error. */

  /* Check if key already exists */
  ezmap_node_t* current = map->head;
  while (current != NULL) {
    if (memcmp(current->key, key, EZMAP_KEY_SIZE) == 0) {
      current->value = value;  /* Overwrite existing value */
      return 0;  /* Success. */
    }
    current = current->next;
  }

  /* Add new node */
  ezmap_node_t* new_node = malloc(sizeof(ezmap_node_t));
  if (new_node == NULL) { return -1; }  /* Handle error. */

  memcpy(new_node->key, key, EZMAP_KEY_SIZE);
  new_node->value = value;
  new_node->next = map->head;
  map->head = new_node;

  return 0;  /* Success. */
}  /* ezmap_add */


void* ezmap_lookup(ezmap_t* map, void* key) {
  if (map == NULL || key == NULL) { return NULL; }  /* Handle error. */

  ezmap_node_t* current = map->head;
  while (current != NULL) {
    if (memcmp(current->key, key, EZMAP_KEY_SIZE) == 0) {
      return current->value;
    }
    current = current->next;
  }

  return NULL;  /* Key not found. */
}  /* ezmap_lookup */
