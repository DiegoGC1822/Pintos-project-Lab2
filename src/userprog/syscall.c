#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);

void
void syscall_init(void) {
    intr_register_int(0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void syscall_handler(struct intr_frame *f) {
    int syscall_number = *(int *)f->esp;  // Leer syscall desde la pila.
    switch (syscall_number) {
        case SYS_WRITE:  // Número definido en syscall-nr.h
            f->eax = sys_write((int *)f->esp + 1);
            break;
        default:
            printf("Unknown syscall number: %d\n", syscall_number);
            thread_exit();
    }
}

int sys_write(int fd, const void *buffer, unsigned size) {
    if (fd == 1) {  // Escribir a la consola.
        putbuf(buffer, size);  // putbuf es una función de Pintos para imprimir texto.
        return size;
    }
    return -1;  // Solo soportamos escribir a la consola por ahora.
}

if (!is_user_vaddr(buffer)) {
    thread_exit();
}

