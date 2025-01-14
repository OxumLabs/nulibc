#include <nulibc.h>
#include <stdlib.h>
#include <stdio.h>


int main() {
    nsys("ls");
    __NCLRSCRN__();
    nexit(ExitStatus.SEGFAULT);
}