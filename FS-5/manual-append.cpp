#include <iostream>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <fcntl.h>

void write_lines(const char* path) {
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd < 0) {
        std::cerr << "Error: Failed to open the file: " << strerror(errno) << std::endl;
        exit(1);
    }

    int fd1 = dup(fd);
    if(fd1 < 0) {
        std::cerr << "Error: Failed to duplicate the fd: " << strerror(errno) << std::endl;
        close(fd);
        exit(2);
    }

    const char* line1 = "first line\n";
    const char* line2 = "second line\n";

    ssize_t result1 = write(fd, line1, strlen(line1));
    if(result1 < 0) {
        std::cerr << "Error: Failed to write line1: " << strerror(errno) << std::endl;
    }

    ssize_t result2 = write(fd1, line2, strlen(line2));
    if(result2 < 0) {
        std::cerr << "Error: Failed to write line2: " << strerror(errno) << std::endl;
    }

    close(fd);
    close(fd1);
}

int main(int argc, char** argv) {
    if(argc != 2) {
        std::cerr << "Error: Invalid arguments" << std::endl;
        return 1;
    }

    write_lines(argv[1]);

    return 0;
}

