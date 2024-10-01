#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {

        if(argc < 2) {
                std::cerr << "Error: File path not provided." << std::endl;
                return 1;
        }

        std::ifstream file(argv[1], std::ios::in | std::ios::binary);
        if(!file) {
                std::cerr << "Error: Could not open the file." << std::endl;
                return 1;
        }

        std::size_t buffer_size = 256;
        char buffer[buffer_size];

        while(file.read(buffer, buffer_size) || file.gcount() > 0) {
                buffer[file.gcount()] = '\0';
                std::cout << buffer;
        }

        file.close();

        return 0;
}
