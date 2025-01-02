    #include <stdarg.h>
    #include <unistd.h>
    void write_num(int num) {
        char buffer[20];
        int i = 0;

        if (num < 0) {
            write(STDOUT_FILENO, "-", 1);
            num = -num;
        }

        if (num == 0) {
            write(STDOUT_FILENO, "0", 1);
            return;
        }

        while (num > 0) {
            buffer[i++] = (num % 10) + '0';
            num /= 10;
        }

        for (int j = i - 1; j >= 0; j--) {
            write(STDOUT_FILENO, &buffer[j], 1);
        }
    }

    void write_str(const char *str) {
        while (*str) {
            write(STDOUT_FILENO, str, 1);
            str++;
        }
    }

    void write_hex(unsigned int num) {
        const char hex_chars[] = "0123456789abcdef";
        char buffer[10];
        int i = 0;

        if (num == 0) {
            write(STDOUT_FILENO, "0", 1);
            return;
        }

        while (num > 0) {
            buffer[i++] = hex_chars[num % 16];
            num /= 16;
        }

        for (int j = i - 1; j >= 0; j--) {
            write(STDOUT_FILENO, &buffer[j], 1);
        }
    }

    void write_char(char c) {
        write(STDOUT_FILENO, &c, 1);
    }

    void nprintf(const char *s, ...) {
        va_list args;
        va_start(args, s);

        const char *ptr = s;
        while (*ptr != '\0') {
            if (*ptr == '%' && *(ptr + 1) == 'd') {
                int num = va_arg(args, int);
                write_num(num);
                ptr += 2;
            } else if (*ptr == '%' && *(ptr + 1) == 's') {
                char *str = va_arg(args, char*);
                write_str(str);
                ptr += 2;
            } else if (*ptr == '%' && *(ptr + 1) == 'c') {
                char c = (char) va_arg(args, int);
                write_char(c);
                ptr += 2;
            } else if (*ptr == '%' && *(ptr + 1) == 'x') {
                unsigned int hex = va_arg(args, unsigned int);
                write_hex(hex);
                ptr += 2;
            } else if (*ptr == '%' && *(ptr + 1) == 'p') {
                void *ptr_value = va_arg(args, void*);
                write_hex((unsigned long)ptr_value);
                ptr += 2;
            } else {
                write_char(*ptr);
                ptr++;
            }
        }

        va_end(args);
    }
    int strcmp(const char *str1, const char *str2) {
        while (*str1 != '\0' && *str2 != '\0') {
            if (*str1 != *str2) {
                return (unsigned char)(*str1) - (unsigned char)(*str2);
            }
            str1++;
            str2++;
        }
        return (unsigned char)(*str1) - (unsigned char)(*str2);
    }






    /*
    =============================Memory Manager====================================
    */
   #include <stdio.h>
#include <stdlib.h>
#include <string.h>

int DEBUG = 1;

typedef struct Block {
    size_t size;
    int is_free;
    struct Block* next;
    char name[32];
} Block;

typedef struct MemoryPool {
    size_t total_size;
    size_t used_size;
    size_t free_size;
    Block* free_list;
    struct MemoryPool* next;
} MemoryPool;

MemoryPool* global_pool_list = NULL;
void memory_pool_add(MemoryPool* pool) {
    if (!pool) return;

    pool->next = global_pool_list;
    global_pool_list = pool;
}

MemoryPool* memory_pool_create(size_t total_size) {
    if (total_size == 0) {
        if (DEBUG) printf("Error: Cannot create a memory pool with size 0.\n");
        return NULL;
    }

    MemoryPool* new_pool = (MemoryPool*)malloc(sizeof(MemoryPool));
    if (!new_pool) {
        if (DEBUG) printf("Error: Failed to allocate memory for new memory pool.\n");
        return NULL;
    }

    new_pool->total_size = total_size;
    new_pool->used_size = 0;
    new_pool->free_size = total_size;
    new_pool->free_list = (Block*)malloc(total_size);
    if (!new_pool->free_list) {
        free(new_pool);
        if (DEBUG) printf("Error: Failed to allocate memory for memory pool's block list.\n");
        return NULL;
    }

    new_pool->free_list->size = total_size;
    new_pool->free_list->is_free = 1;
    new_pool->free_list->next = NULL;
    new_pool->next = NULL;

    if (DEBUG) {
        printf("Memory pool created with size %zu\n", total_size);
    }
    memory_pool_add(new_pool);
    return new_pool;
}

void* memory_pool_alloc(MemoryPool* pool, size_t size, const char* block_name) {
    if (!pool || size == 0 || size > pool->free_size) {
        if (DEBUG) printf("Error: Invalid allocation request.\n");
        return NULL;
    }

    Block* best_fit = NULL;
    Block* current = pool->free_list;

    while (current) {
        if (current->is_free && current->size >= size) {
            if (!best_fit || current->size < best_fit->size) {
                best_fit = current;
            }
        }
        current = current->next;
    }

    if (!best_fit) {
        if (DEBUG) printf("Error: No suitable block found for allocation.\n");
        return NULL;
    }

    if (best_fit->size > size + sizeof(Block)) {
        Block* new_block = (Block*)((char*)best_fit + sizeof(Block) + size);
        new_block->size = best_fit->size - size - sizeof(Block);
        new_block->is_free = 1;
        new_block->next = best_fit->next;
        best_fit->size = size;
        best_fit->next = new_block;
    }

    best_fit->is_free = 0;
    strncpy(best_fit->name, block_name, 32);

    pool->used_size += size;
    pool->free_size -= size;

    if (DEBUG) {
        printf("Allocated block '%s' of size %zu\n", best_fit->name, size);
    }

    return (void*)((char*)best_fit + sizeof(Block));
}

void memory_pool_free(MemoryPool* pool, void* ptr) {
    if (!pool || !ptr) {
        if (DEBUG) printf("Error: Invalid free request.\n");
        return;
    }

    Block* current = pool->free_list;
    while (current) {
        if ((void*)((char*)current + sizeof(Block)) == ptr && !current->is_free) {
            current->is_free = 1;
            pool->used_size -= current->size;
            pool->free_size += current->size;
            break;
        }
        current = current->next;
    }

    if (DEBUG) {
        printf("Freed memory at address %p\n", ptr);
    }

    current = pool->free_list;
    while (current) {
        if (current->is_free && current->next && current->next->is_free) {
            current->size += sizeof(Block) + current->next->size;
            current->next = current->next->next;
        }
        current = current->next;
    }
}

void memory_pool_destroy(MemoryPool* pool) {
    if (!pool) {
        fprintf(stderr, "Error: Attempted to destroy a null memory pool.\n");
        return;
    }

    if (!pool->free_list) {
        fprintf(stderr, "Warning: Memory pool free list is already null.\n");
    }

    Block* current = pool->free_list;
    while (current) {
        Block* next = current->next;
        if (current == next) {
            fprintf(stderr, "Error: Detected a cyclic block structure in memory pool.\n");
            break;
        }
        free(current);
        current = next;
    }

    pool->free_list = NULL;

    if (DEBUG) {
        printf("Memory pool destroyed successfully.\n");
    }
}

void memory_pool_debug(MemoryPool* pool) {
    if (!pool) {
        if (DEBUG) printf("Error: Null pool passed to debug function.\n");
        return;
    }

    printf("Memory Pool Debug Info:\n");
    printf("Total Size: %zu, Used Size: %zu, Free Size: %zu\n", pool->total_size, pool->used_size, pool->free_size);

    Block* current = pool->free_list;
    while (current) {
        printf("  Block: %s, Size: %zu, Free: %d\n", current->name, current->size, current->is_free);
        current = current->next;
    }
}

void memory_pool_clear() {
    MemoryPool* current_pool = global_pool_list;

    while (current_pool) {
        Block* current_block = current_pool->free_list;
        while (current_block) {
            Block* next_block = current_block->next;
            free(current_block);
            current_block = next_block;
        }

        MemoryPool* next_pool = current_pool->next;
        free(current_pool);
        current_pool = next_pool;
    }

    global_pool_list = NULL;

    if (DEBUG) {
        printf("All memory pools cleared.\n");
    }
}

