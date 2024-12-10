#ifndef USERPROG_PROCESS_H
#define USERPROG_PROCESS_H

#include "threads/thread.h"
#include "bitmap.h"
#include <sys/types.h>
#include "threads/vaddr.h"
#include "lib/kernel/hash.h"

tid_t process_execute (const char *file_name);
int process_wait (tid_t);
void process_exit (void);
void process_activate (void);

/* Estructura para las páginas suplementarias. */
struct suppl_page {
    void *upage;           // Dirección virtual de la página en el espacio del usuario.
    enum page_location {   // Ubicación de los datos asociados con la página.
        PAGE_FILE,
        PAGE_SWAP,
        PAGE_ZERO
    } location;            // Dónde están los datos (archivo, swap, o ceros).

    struct file *file;     // Archivo del cual cargar la página (si corresponde).
    off_t ofs;             // Offset dentro del archivo.
    uint32_t read_bytes;   // Número de bytes a leer del archivo.
    uint32_t zero_bytes;   // Número de bytes inicializados a cero.
    bool writable;         // Indica si la página puede ser modificada.
    size_t swap_index;     // Índice en el área de swap (si corresponde).

    struct hash_elem elem; // Elemento para la tabla hash.
};

/* Estructura para la tabla de swap. */
struct swap_table {
    struct block *swap_device;  // Dispositivo de swap.
    struct bitmap *swap_slots; // Mapa de bits para rastrear los slots.
};

/* Estructura para los marcos. */
struct frame {
    void *kpage;            // Dirección del marco físico (en la memoria física).
    struct thread *owner;   // Proceso propietario del marco.
    void *upage;            // Dirección virtual del usuario que ocupa este marco.
    struct list_elem elem;  // Elemento para mantener la lista de marcos.
};

#endif /* userprog/process.h */
