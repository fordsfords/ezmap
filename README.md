# ezmap
Overly-simple map in C.


## Table of contents

<!-- mdtoc-start -->
&bull; [ezmap](#ezmap)  
&nbsp;&nbsp;&nbsp;&nbsp;&bull; [Table of contents](#table-of-contents)  
&nbsp;&nbsp;&nbsp;&nbsp;&bull; [Introduction](#introduction)  
&nbsp;&nbsp;&nbsp;&nbsp;&bull; [Purpose](#purpose)  
&nbsp;&nbsp;&nbsp;&nbsp;&bull; [Features](#features)  
&nbsp;&nbsp;&nbsp;&nbsp;&bull; [Limitations](#limitations)  
&nbsp;&nbsp;&nbsp;&nbsp;&bull; [API](#api)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&bull; [Types](#types)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&bull; [Functions](#functions)  
&nbsp;&nbsp;&nbsp;&nbsp;&bull; [Usage Example](#usage-example)  
&nbsp;&nbsp;&nbsp;&nbsp;&bull; [Building](#building)  
&nbsp;&nbsp;&nbsp;&nbsp;&bull; [License](#license)  
<!-- TOC created by '../mdtoc/mdtoc.pl README.md' (see https://github.com/fordsfords/mdtoc) -->
<!-- mdtoc-end -->


## Introduction

A minimal map implementation for C applications that need basic key-value storage with binary keys.
Not intended for production use.

Thanks to Claude.ai for assisting with the code and documentation for this module.

## Purpose

This module provides a simple map data structure for C programs that need to store key-value pairs
where keys are binary data (not null-terminated strings).
It's designed primarily for demonstration purposes in example C applications where there is no
widely-accepted standard map available.
I expect you to discard this map module and replace it with your favorite production-level map.

**Important**: This is a simple implementation with poor performance,
intended for examples and prototypes.
Production applications should use established map libraries appropriate
for their environment (C++ STL, Boost, etc.).

## Features

- **Binary keys**: Keys are fixed-size byte arrays, not strings
- **Pointer values**: Values are void pointers to your data
- **Key overwriting**: Adding an existing key updates its value
- **Simple API**: Create, add, lookup - that's it
- **No dependencies**: Uses only standard C library functions

## Limitations

- **Low Performance**: Uses a simple linked list - O(n) operations
- **No deletion**: Cannot remove individual entries
- **No iteration**: Cannot walk through all entries
- **No cleanup**: Map persists for program lifetime
- **Single-threaded**: No thread safety mechanisms
- **Fixed key size**: All keys must be exactly `EZMAP_KEY_SIZE` bytes

Regarding fixed key sizes, you are more than welcome to use
variable-length strings as keys so long as they fit within
`EZMAP_KEY_SIZE` bytes (including final null)
and that the remaining bytes in the array are cleared.

## API

### Types

```c
typedef struct ezmap ezmap_t;
```

### Functions

```c
ezmap_t* ezmap_create();
```
Creates a new empty map. Returns NULL on error.

```c
int ezmap_add(ezmap_t* map, void* key, void* value);
```

Adds or updates a key-value pair. Key must be exactly `EZMAP_KEY_SIZE` bytes.
Caller is responsible for zero-padding key array.
- Returns 0 on success
- Returns -1 on error (NULL parameters or memory allocation failure)
- Overwrites existing values for duplicate keys

```c
void* ezmap_lookup(ezmap_t* map, void* key);
```
Retrieves the value associated with a key.
- Returns the value pointer on success
- Returns NULL if key not found or on error

## Usage Example

```c
#include "ezmap.h"

int main() {
  ezmap_t* map = ezmap_create();
  if (map == NULL) { /* Handle error */ }

  /* Add entries */
  char key1[EZMAP_KEY_SIZE] = {0x01, 0x02, 0x03, 0x04};  /* Initializes rest of bytes to 0. */
  char* value1 = "first value";
  ezmap_add(map, key1, value1);

  char key2[EZMAP_KEY_SIZE] = {0x05, 0x06, 0x07, 0x08};
  static int value2 = 42;
  ezmap_add(map, key2, &value2);

  /* Lookup entries */
  char* result1 = (char*)ezmap_lookup(map, key1);
  int* result2 = (int*)ezmap_lookup(map, key2);

  return 0;
}
```

## Building

See "bld.sh".


## License

I want there to be NO barriers to using this code, so I am releasing it to the public domain.
But "public domain" does not have an internationally agreed upon definition, so I use CC0:

Copyright 2019-2024 Steven Ford http://geeky-boy.com and licensed
"public domain" style under
[CC0](http://creativecommons.org/publicdomain/zero/1.0/):
![CC0](https://licensebuttons.net/p/zero/1.0/88x31.png "CC0")

To the extent possible under law, the contributors to this project have
waived all copyright and related or neighboring rights to this work.
In other words, you can use this code for any purpose without any
restrictions.  This work is published from: United States.  The project home
is https://github.com/fordsfords/ezmap

To contact me, Steve Ford, project owner, you can find my email address
at http://geeky-boy.com.  Can't see it?  Keep looking.
