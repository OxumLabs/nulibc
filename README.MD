# NuLibC
## A custom minimal libc for the [neit programming language](https://oxumlabs.github.io/nsite)

this libc is built using musl for more static behaviour and currently implements the following functions:

1.) ``strcmp`` :~ A function to compare 2 string-type values
2.) ``nprintf`` :~ allows printing to standard out (stdout) , like the normal ``printf`` this supports formatters aswell
3.) ``memory_pool`` :~ Allows creation of custom memory pool and allocating blocks from it , writting to them freeing them and more!

##### Check out the full source at [nulibc.h](nulibc.h) as well as [nulibc.c](nulibc.c) for in detailed explanations , especially the ``nulibc.h`` contains documentations you can read!
---
This project is under the [MIT License](LICENSE)