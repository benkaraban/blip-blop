#include <unistd.h>

#include "io.h"

int _open(const char* filename, int mode) { return open(filename, mode); }

int _read(int fd, void* buf, int size) { return read(fd, buf, size); }

int _close(int fd) { return close(fd); }
