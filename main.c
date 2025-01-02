#include "nulibc.h"
#include <string.h>
int main() {
    DEBUG = 1;
    MemoryPool* j1 = memory_pool_create(2048);
    return 0;
}
