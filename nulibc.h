#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stddef.h>

/* ============================= Memory Manager ============================= */

/**
 * Struct representing a memory block in the pool.
 */
typedef struct Block {
    size_t size;           /**< Size of the block */
    int is_free;           /**< 1 if the block is free, 0 if it's used */
    struct Block* next;    /**< Pointer to the next block in the list */
    char name[32];         /**< Name associated with the block */
} Block;

extern int DEBUG;

/**
 * Struct representing the memory pool.
 */
typedef struct MemoryPool {
    size_t total_size;     /**< Total size of the memory pool */
    size_t used_size;      /**< Used size of the memory pool */
    size_t free_size;      /**< Free size of the memory pool */
    Block* free_list;      /**< Linked list of free blocks */
    struct MemoryPool* next; /**< Pointer to the next memory pool */
} MemoryPool;

/**
 * Creates a memory pool of a given size.
 *
 * @param total_size The size of the memory pool to create.
 * @return A pointer to the created memory pool, or NULL if an error occurred.
 */
MemoryPool* memory_pool_create(size_t total_size);

/**
 * Allocates a block of memory from the pool.
 *
 * @param pool The memory pool to allocate from.
 * @param size The size of the block to allocate.
 * @param block_name The name of the block being allocated.
 * @return A pointer to the allocated memory block, or NULL if no suitable block is found.
 */
void* memory_pool_alloc(MemoryPool* pool, size_t size, const char* block_name);

/**
 * Frees a previously allocated block of memory in the pool.
 *
 * @param pool The memory pool containing the block.
 * @param ptr A pointer to the memory block to free.
 */
void memory_pool_free(MemoryPool* pool, void* ptr);

/**
 * Destroys a memory pool, freeing all associated memory.
 *
 * @param pool The memory pool to destroy.
 */
void memory_pool_destroy(MemoryPool* pool);

/**
 * Prints debug information about the memory pool.
 *
 * @param pool The memory pool to print debug information about.
 */
void memory_pool_debug(MemoryPool* pool);

/**
 * Clears all memory pools.
 */
void memory_pool_clear(void);

/* ============================= Utility Functions =========================== */

/**
 * Writes an integer number to standard output.
 *
 * @param num The number to write.
 */
void write_num(int num);

/**
 * Writes a string to standard output.
 *
 * @param str The string to write.
 */
void write_str(const char *str);

/**
 * Writes a hexadecimal number to standard output.
 *
 * @param num The number to write in hexadecimal format.
 */
void write_hex(unsigned int num);

/**
 * Writes a single character to standard output.
 *
 * @param c The character to write.
 */
void write_char(char c);

/**
 * Custom implementation of printf-like function supporting various formats.
 *
 * @param s The format string.
 * @param ... The values to format and print.
 */
void nprintf(const char *s, ...);

/**
 * Compares two strings lexicographically.
 *
 * @param str1 The first string to compare.
 * @param str2 The second string to compare.
 * @return A negative integer if str1 < str2, a positive integer if str1 > str2, or 0 if they are equal.
 */
int strcmp(const char *str1, const char *str2);

#endif /* MEMORY_MANAGER_H */
