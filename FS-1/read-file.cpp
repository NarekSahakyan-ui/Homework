#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: File path not provided." << std::endl;
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }

    const std::size_t buffer_size = 256;
    char buffer[buffer_size];

    ssize_t bytesRead;
    while ((bytesRead = read(fd, buffer, buffer_size)) > 0) {

        if (write(STDOUT_FILENO, buffer, bytesRead) == -1) {
            std::cerr << "Error: Failed to write to stdout." << std::endl;
            close(fd);
            return 1;
        }
    }

    if (bytesRead == -1) {
        std::cerr << "Error: Failed to read the file." << std::endl;
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}

