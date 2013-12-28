#ifndef IO_H
#define IO_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

int _open(const char* filename, int mode) {
	return open(filename, mode);
}
int _read(int fd, void* buf, int size) {
	return read(fd, buf, size);
}
int _close(int fd) {
	return close(fd);
}

#define _O_BINARY 0x0
#define _O_RDONLY O_RDONLY

#endif
