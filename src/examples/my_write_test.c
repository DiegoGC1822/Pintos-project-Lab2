#include <syscall.h>
#include <stdio.h>

int main() {
    write(1, "Hello, Pintos!\n", 15);
    return 0;
}

