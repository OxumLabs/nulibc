# NuLibC
## A Custom Minimal C Library for the [Neit Programming Language](https://oxumlabs.github.io/nsite)

NuLibC is a custom minimal C standard library designed specifically for the [Neit programming language](https://oxumlabs.github.io/nsite). It is built using **musl** for more static behavior, ensuring that it is compact and efficient. Currently, NuLibC implements the following core functionalities:

### Features

1. **`strcmp`**:
   - A function to compare two string-type values.
   
2. **`nprintf`**:
   - Allows formatted output to standard output (`stdout`), similar to `printf`. It supports format specifiers such as `%d`, `%s`, `%x`, etc., for printing integers, strings, and hexadecimal values.
   
3. **`memory_pool`**:
   - Provides functionality for creating custom memory pools, allocating and deallocating memory blocks from them, and managing the memory lifecycle.
   - It includes features for managing free and allocated blocks, memory pooling, and basic error handling for memory operations.

##### Check out the full source at [nulibc.h](nulibc.h) as well as [nulibc.c](nulibc.c) for detailed explanations, especially the `nulibc.h` which contains documentation you can read! Also you shall use the ``nulibc.zip`` file to get the latest package of NuLibC , it contains ``nulibc.a`` for static linking and ``nulibc.c`` and ``nulibc.h`` for actually using the library

##### We are aiming to add more features as this is a support library for the Neit programming language, so stay tuned for more updates! also feel free to contribute to this project by submitting pull requests or issues

---
This project is under the [MIT License](LICENSE).
