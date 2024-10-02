#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstring>

void Delete(const char* path) {
    int fd = open(path, O_WRONLY);
    if (fd == -1) {
        std::cerr << "Error: Cannot open the file" << std::endl;
        return;
    }

    struct stat fileInfo;
    if (fstat(fd, &fileInfo) == -1) {
        std::cerr << "Error: Cannot get information about the file" << std::endl;
        close(fd);
        return;
    }

    off_t size = fileInfo.st_size;
    if (size > 0) {
        char* buffer = new char[size];
        memset(buffer, '\0', size);

        if (write(fd, buffer, size) != size) {
            std::cerr << "Error: Failed to write in the file" << std::endl;
        }

        delete[] buffer;
    }

    close(fd);

    if (unlink(path) == -1) {
        std::cerr << "Error: Couldn't remove the file" << std::endl;
    } else {
        std::cout << "File is successfully deleted" << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "The number of the arguments is wrong." << std::endl;
        return 1;
    }

    Delete(argv[1]);
    return 0;
}

