#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <cstring>

void copyFile(const char* source, const char* destination) {
    int src_fd = open(source, O_RDONLY);
    if (src_fd == -1) {
        std::cerr << "Error: Could not open source file: " << source << std::endl;
        return;
    }

    int dest_fd = open(destination, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        std::cerr << "Error: Could not open destination file: " << destination << std::endl;
        close(src_fd);
        return;
    }

    const std::size_t buffer_size = 256;
    char buffer[buffer_size];
    ssize_t bytesRead;

    while ((bytesRead = read(src_fd, buffer, buffer_size)) > 0) {
        if (write(dest_fd, buffer, bytesRead) == -1) {
            std::cerr << "Error: Failed to write to destination file: " << destination << std::endl;
            close(src_fd);
            close(dest_fd);
            return;
        }
    }

    if (bytesRead == -1) {
        std::cerr << "Error: Failed to read from source file: " << source << std::endl;
    } else {
        std::cout << "File copied successfully from " << source << " to " << destination << std::endl;
    }

    close(src_fd);
    close(dest_fd);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Error: The number of the arguments is wrong." << std::endl;
        return 1;
    }


    copyFile(argv[1], argv[2]);
    return 0;
}


