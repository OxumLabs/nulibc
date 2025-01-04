# NuLibC Documentation

## Table of Contents
- [Introduction](#introduction)
- [``nprintf``](#nprintf)
- [``strcmp``](#strcmp)
- [``nstring``](#nstring)
- [``memory``](#memory)

---

### Introduction
NuLibC is a custom minimal C standard library designed specifically for the [Neit programming language](https://oxumlabs.github.io/nsite). It is built using **musl** for more static behavior, ensuring that it is compact and efficient and supports few basic functionality but is being developed to support more features in the future
---

### ``nprintf``

``nprintf`` is a function that allows formatted output to standard output (`stdout`) , standard error (`stderr`) , and standard input (`stdin`) . It supports format specifiers such as `%d`, `%s`, `%x`, etc., for printing integers, strings, and hexadecimal values! (I don't really know how the ``stdin`` could benifit you but it's there for you to use it)
 - parameters :
    - ``fd`` : The file descriptor to write to they are - STDOUT, STDERR, STDIN
    - ``s`` : The format string, followed by a variable number of arguments.
- code :
    - 
    ```c
    nprintf(STDOUT,"Hello World!\n");
    ```
---

### ``strcmp``

A function to compare two string-type values
- parameters :
    - ``str1`` : The first string to compare.
    - ``str2`` : The second string to compare.
- return :
    - 0 if the strings are equal else non-zero value if not equal
- code :
    - 
    ```c
    if (strcmp("Hello","Hello") == 0) {
        printf("The strings are equal\n");
    } else {
        printf("The strings are not equal\n");
    }
    ```
---

### ``nstring``

A custom string type that represents a string with an associated length
- code :
    - 
    ```c
    nstring str = strnew("Hello World!");
    printf("The string is %s\n", str.str);
    ```
---

### ``memory``

A custom memory manager that allows for management of multiple pools of memory in the system

it has the following functions associated with it :

- ``mem_init`` : Initializes a memory manager
   - parameters :
      - ``total`` : Total size of memory that can be managed
      - return : Pointer to initialized MemManager instance
   - code :
      - 
      ```c
      MemManager* mgr = mem_init(1024);
      ```

- ``mem_alloc`` : Allocates a memory block of the specified size and associates it with a name
   - parameters :
      - ``mgr`` : Pointer to the memory manager
      - ``size`` : Size of the memory block to be allocated
      - ``name`` : Name to associate with the memory block
      - return : Pointer to the allocated MemBlock
   - code :
      - 
      ```c
      MemBlock* blk = mem_alloc(mgr, 1024, "test");
      ```

- ``mem_free`` : Frees a memory block and marks it as free in the memory manager
   - parameters :
      - ``mgr`` : Pointer to the memory manager
      - ``blk`` : Pointer to the memory block to be freed
   - code :
      - 
      ```c
      mem_free(mgr, blk);
      ```

- ``mem_cleanup`` : Cleans up all allocated memory blocks and the memory manager
   - parameters :
      - ``mgr`` : Pointer to the memory manager to be cleaned up
   - code :
      - 
      ```c
      mem_cleanup(mgr);
      ```

- ``mem_wrtstr`` : Writes a string to a specified memory block
   - parameters :
      - ``blk`` : Pointer to the memory block
      - ``str`` : String to write to the memory block
      - return : 0 on success, negative error code on failure
   - code :
      - 
      ```c
      mem_wrtstr(blk, "Hello World!");
      ```

- ``mem_wrtint`` : Writes an integer value to a specified memory block
   - parameters :
      - ``blk`` : Pointer to the memory block
      - ``value`` : Integer value to write to the memory block
      - return : 0 on success, negative error code on failure
   - code :
      - 
      ```c
      mem_wrtint(blk, 1024);
      ```

- ``mem_rdint`` : Reads an integer value from a memory block by name
   - parameters :
      - ``mgr`` : Pointer to the memory manager
      - ``name`` : Name associated with the memory block
      - return : Integer value read from the memory block, or -1 on failure
   - code :
      - 
      ```c
      int value = mem_rdint(mgr, "test");
      ```

- ``mem_rdstr`` : Reads a string from a memory block by name
   - parameters :
      - ``mgr`` : Pointer to the memory manager
      - ``name`` : Name associated with the memory block
      - return : Pointer to the string, or NULL on failure
   - code :
      - 
      ```c
      char* str = mem_rdstr(mgr, "test");
      ```
---