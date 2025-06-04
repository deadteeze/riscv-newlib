#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

#include "uart.h"

int _write(int file, char *ptr, int len) {
    if (file != STDOUT_FILENO && file != STDERR_FILENO) {
        errno = EBADF;
        return -1;
    }
    
    int i;
    for (i = 0; i < len; i++) {
        uart_putc(ptr[i]);
    }
    return len;
}

int _read(int file, char *ptr, int len) { 
    if (file != STDIN_FILENO) {
        errno = EBADF;
        return -1;
    }
    
    int i;
    for (i = 0; i < len; i++) {
        ptr[i] = uart_getc();
        if (ptr[i] == '\r' || ptr[i] == '\n') {
            i++;
            break;
        }
    }
    return i;
}

int _open(const char *name, int flags, int mode) { errno = ENOSYS; return -1; }
int _close(int file) { return -1; }
int _lseek(int file, int ptr, int dir) { return 0; }
int _fstat(int file, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}
int _isatty(int file) {
    return 1;
}

void* _sbrk(int incr) {
    extern char _end;         // Defined in linker
    extern char _stack_bottom; // Defined in linker

    static char *heap_end = &_end;
    char *prev_heap_end = heap_end;

    char *stack_limit = &_stack_bottom;

    if (heap_end + incr > stack_limit) {
        errno = ENOMEM;
        return (void*) -1; 
    }

    heap_end += incr;
    return (void*) prev_heap_end;
}

void _exit(int code) { while (1); }
int _kill(int pid, int sig) { return -1; }
int _getpid(void) { return 1; }
