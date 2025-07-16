/* ezmap_test.c - self-test.
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "ezmap.h"

#define ASSRT(assrt__cond) do { \
  if (! (assrt__cond)) { \
    printf("ERROR [%s:%d]: assert '%s' failed\n", __FILE__, __LINE__, #assrt__cond); \
    exit(1); \
  } \
} while (0)


/* Command-line options */
int o_testnum;


char usage_str[] = "Usage: ezmap_test [-h] [-t testnum]";
void usage(char *msg) {
  if (msg) fprintf(stderr, "\n%s\n\n", msg);
  fprintf(stderr, "%s\n", usage_str);
  exit(1);
}  /* usage */

void help() {
  printf("%s\n"
    "where:\n"
    "  -h - print help\n"
    "  -t testnum - Specify which test to run [1].\n"
    "For details, see https://github.com/fordsfords/ezmap\n",
    usage_str);
  exit(0);
}  /* help */


void parse_cmdline(int argc, char **argv) {
  int i;

  /* Since this is Unix and Windows, don't use getopts(). */
  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-h") == 0) {
      help();  exit(0);

    } else if (strcmp(argv[i], "-t") == 0) {
      if ((i + 1) < argc) {
        i++;
        o_testnum = atoi(argv[i]);
      } else { fprintf(stderr, "Error, -t requires test number\n");  exit(1); }

    } else { fprintf(stderr, "Error, unknown option '%s'\n", argv[i]);  exit(1); }
  }  /* for i */
}  /* parse_cmdline */


void test1() {
  ezmap_t* map = ezmap_create(); ASSRT(map != NULL);
  int err;

  char key1[EZMAP_KEY_SIZE] = {0x01, 0x02, 0x03, 0x04};
  char *str_value = "first value";
  err = ezmap_add(map, key1, str_value);  ASSRT(err == 0);

  char key2[EZMAP_KEY_SIZE] = {0x05, 0x06, 0x07};
  int int_value = 42;
  err = ezmap_add(map, key2, &int_value);  ASSRT(err == 0);

  char* str_result = (char *)ezmap_lookup(map, key1);  ASSRT(str_result != NULL);
  ASSRT(strcmp(str_value, str_result) == 0);

  int *int_result = (int *)ezmap_lookup(map, key2);  ASSRT(int_result != NULL);
  ASSRT(int_value == *int_result);

  /* Overwrite key2. */
  err = ezmap_add(map, key2, str_value);  ASSRT(err == 0);
  str_result = (char *)ezmap_lookup(map, key2);  ASSRT(str_result != NULL);
  ASSRT(strcmp(str_value, str_result) == 0);
}  /* test1 */


void test2() {
}  /* test2 */


int main(int argc, char **argv) {
  parse_cmdline(argc, argv);

  if (o_testnum == 0 || o_testnum == 1) {
    test1();
    printf("test1: success\n");
  }

  if (o_testnum == 0 || o_testnum == 2) {
    test2();
    printf("test1: success\n");
  }

  return 0;
}  /* main */
