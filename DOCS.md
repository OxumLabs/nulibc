
# NuLibC Documentation

NuLibC is a minimalistic custom C library designed for the Neit programming language. Built using musl, it is optimized for compactness and efficiency. While currently supporting basic features, the library is under active development and will include additional functionalities in the future.

---

## Table of Contents

1. [Introduction](#introduction)
2. [``nprintf``](#nprintf)
3. [``strcmp``](#strcmp)
4. [``nstring``](#nstring)
5. [``memory``](#memory)

---

### Introduction

NuLibC provides essential C functions tailored for the Neit language, offering a minimalistic and efficient implementation with static behavior. It focuses on standard operations like formatted printing, string manipulation, and custom memory management.

---

### ``nprintf``

The `nprintf` function is used for formatted output. It can write to standard output (`STDOUT`), standard error (`STDERR`), and standard input (`STDIN`).

#### Parameters:
- `fd`: The file descriptor to write to. Possible values:
  - `STDOUT` (1)
  - `STDERR` (2)
  - `STDIN` (0)
- `format`: The format string followed by a variable number of arguments. Supports format specifiers such as `%d`, `%s`, `%x`, etc.

#### Example Usage:
```c
nprintf(STDOUT, "Hello, World!
");
```

---

### ``strcmp``

The `strcmp` function compares two null-terminated C strings.

#### Parameters:
- `str1`: The first string to compare.
- `str2`: The second string to compare.

#### Return Value:
- `0` if the strings are equal.
- A non-zero value if the strings are different.

#### Example Usage:
```c
if (strcmp("Hello", "Hello") == 0) {
    printf("The strings are equal.
");
} else {
    printf("The strings are not equal.
");
}
```

---

### ``nstring``

`nstring` is a custom type representing a string with an associated length. It is optimized for efficient string manipulation and memory management.

#### Example Usage:
```c
nstring str = strnew("Hello, World!");
printf("The string is: %s
", str.str);
```

#### Functions:

##### `strnew`

Creates a new `nstring` from a given C string.

**Parameters:**
- `const char *str`: The C string to convert into `nstring`.

**Return Value:**
- A new `nstring` structure containing the string and its length.

```c
nstring str = strnew("Hello, World!");
```

##### `nstrlen`

Returns the length of an `nstring`.

**Parameters:**
- `nstring *str`: The `nstring` whose length is to be calculated.

**Return Value:**
- The length of the string.

```c
size_t len = nstrlen(&str);
```

##### `nstrcpy`

Copies the content of one `nstring` into another `nstring`.

**Parameters:**
- `const nstring *src`: The source `nstring` to copy from.

**Return Value:**
- A new `nstring` containing the same content as `src`.

```c
nstring strCopy = nstrcpy(&src);
```

##### `nstrcat`

Concatenates two `nstring` objects into a new `nstring`.

**Parameters:**
- `const nstring *s1`: The first `nstring` to concatenate.
- `const nstring *s2`: The second `nstring` to concatenate.

**Return Value:**
- A new `nstring` containing the concatenation of `s1` and `s2`.

```c
nstring strConcat = nstrcat(&s1, &s2);
```

##### `nstrchr`

Finds the first occurrence of a character in an `nstring`.

**Parameters:**
- `const nstring *s`: The `nstring` to search.
- `char c`: The character to search for.

**Return Value:**
- The index of the first occurrence of `c` in `s`, or `-1` if not found.

```c
size_t index = nstrchr(&s, 'c');
```

##### `nstrncpy`

Copies a substring from one `nstring` into a new `nstring`.

**Parameters:**
- `const nstring *s`: The `nstring` to copy from.
- `size_t start`: The starting index of the substring.
- `size_t length`: The length of the substring to copy.

**Return Value:**
- A new `nstring` containing the substring from `s`.

```c
nstring substring = nstrncpy(&s, start, length);
```

##### `nstrdup`

Duplicates a C string into a new `nstring`.

**Parameters:**
- `const char *cstr`: The C string to duplicate.

**Return Value:**
- A new `nstring` containing the content of `cstr`.

```c
nstring strDup = nstrdup("Hello, World!");
```

##### `nstr_at_s`

Retrieves the character at a specified index from an `nstring`.

**Parameters:**
- `const nstring *s`: The `nstring` to access.
- `size_t index`: The index of the character to retrieve.

**Return Value:**
- The character at the specified index.

```c
char c = nstr_at_s(&s, index);
```

---

### ``memory``

The `memory` module provides custom memory management, supporting multiple memory pools for efficient memory allocation and freeing.

#### Functions:

##### `mem_init`

Initializes a memory manager with a specified total size.

**Parameters:**
- `size_t total`: The total size of memory to manage.

**Return Value:**
- A pointer to the initialized `MemManager`.

```c
MemManager *mgr = mem_init(1024);
```

##### `mem_alloc`

Allocates a memory block of the specified size.

**Parameters:**
- `MemManager *mgr`: The memory manager to use.
- `size_t size`: The size of the memory block to allocate.
- `const char *name`: A name to associate with the memory block.

**Return Value:**
- A pointer to the allocated `MemBlock`.

```c
MemBlock *blk = mem_alloc(mgr, 1024, "test_block");
```

##### `mem_free`

Frees a previously allocated memory block.

**Parameters:**
- `MemManager *mgr`: The memory manager.
- `MemBlock *blk`: The memory block to free.

```c
mem_free(mgr, blk);
```

##### `mem_cleanup`

Cleans up all allocated memory blocks and the memory manager.

**Parameters:**
- `MemManager *mgr`: The memory manager to clean up.

```c
mem_cleanup(mgr);
```

##### `mem_wrtstr`

Writes a string to a specified memory block.

**Parameters:**
- `MemBlock *blk`: The memory block to write to.
- `const char *str`: The string to write.

**Return Value:**
- `0` on success, negative error code on failure.

```c
mem_wrtstr(blk, "Hello, World!");
```

##### `mem_wrtint`

Writes an integer to a memory block.

**Parameters:**
- `MemBlock *blk`: The memory block to write to.
- `int value`: The integer value to write.

**Return Value:**
- `0` on success, negative error code on failure.

```c
mem_wrtint(blk, 12345);
```

##### `mem_rdint`

Reads an integer from a memory block by its name.

**Parameters:**
- `MemManager *mgr`: The memory manager.
- `const char *name`: The name of the memory block.

**Return Value:**
- The integer value, or `-1` on failure.

```c
int value = mem_rdint(mgr, "test_block");
```

##### `mem_rdstr`

Reads a string from a memory block by its name.

**Parameters:**
- `MemManager *mgr`: The memory manager.
- `const char *name`: The name of the memory block.

**Return Value:**
- A pointer to the string, or `NULL` on failure.

```c
char *str = mem_rdstr(mgr, "test_block");
```

---

### Conclusion

NuLibC is designed for minimalism and efficiency, making it an ideal choice for use with the Neit language. With support for formatted output, string manipulation, and custom memory management, it is a versatile foundation for building systems in low-resource environments.

For further updates and contributions, check the [NuLibC GitHub repository](https://github.com/oxumlabs/nulibc).
