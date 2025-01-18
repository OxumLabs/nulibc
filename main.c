#include <nulibc.h>
#include <stdlib.h>
#include <stdio.h>


int main() {
    nstring str = nstr_new("Hello, World!");
    nprintf(STDOUT, "String: %s\n", str.str);
    ninput(&str);
    nprintf(STDOUT, "String: %s\n", str.str);
}