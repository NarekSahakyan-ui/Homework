#include <iostream>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <fcntl.h>

void copy_file(const char* source, const char* destination) {
    int sfd = open(source, O_RDONLY);
    if (sfd < 0) {
        std::cerr << "Error: Failed to open the source file: " << strerror(errno) << std::endl;
        exit(1);
    }

    int dfd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dfd < 0) {
        std::cerr << "Error: Failed to open the destination file: " << strerror(errno) << std::endl;
        close(sfd);
        exit(2);
    }

    char buffer[4096];

    ssize_t bytes_read, bytes_written;
    size_t total_bytes = 0;
    size_t total_dbytes = 0;
    size_t total_holes = 0;

    while ((bytes_read = read(sfd, buffer, sizeof(buffer))) > 0) {
        total_bytes += bytes_read;

        if (bytes_read < static_cast<ssize_t>(sizeof(buffer))) {
            total_holes += sizeof(buffer) - bytes_read;
        }

        bytes_written = write(dfd, buffer, bytes_read);
        if (bytes_written < 0) {
            std::cerr << "Error: Failed to write to the destination file: " << strerror(errno) << std::endl;
            close(sfd);
            close(dfd);
            exit(3);
        }
        total_dbytes += bytes_written;
    }

    if (bytes_read < 0) {
        std::cerr << "Error: Failed to read from the source file: " << strerror(errno) << std::endl;
        close(sfd);
        close(dfd);
        exit(4);
    }

    close(sfd);
    close(dfd);

    std::cout << "Successfully copied " << total_bytes << " bytes (data: " 
              << total_dbytes << ", holes: " << total_holes << ")." << std::endl;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Error: Invalid arguments" << std::endl;
        return 1;
    }

    copy_file(argv[1], argv[2]);

    return 0;
}

