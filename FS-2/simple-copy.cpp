#include <iostream>
#include <fstream>
#include <string>

void copyFile(const std::string& source, const std::string& destination) {
    std::ifstream src(source, std::ios::binary);

    if (!src) {
        std::cerr << "Error: Could not open source file: " << source << std::endl;
        return;
    }

    std::ofstream dest(destination, std::ios::binary);
    if (!dest) {
        std::cerr << "Error: Could not open destination file: " << destination << std::endl;
        return;
    }

    dest << src.rdbuf();

    if (!dest) {
        std::cerr << "Error: Failed to write to destination file: " << destination << std::endl;
    } else {
        std::cout << "File copied successfully from " << source << " to " << destination << std::endl;
    }



}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Error: The number of the argumens is wrong." << std::endl;
        return 1;
    }

    std::string sourceFile = argv[1];
    std::string destFile = argv[2];

    copyFile(sourceFile, destFile);

    return 0;
}
