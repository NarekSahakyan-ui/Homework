#include <iostream>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void initilize(int argc, char** argv) {
	if(argc != 2) {
		std::cerr << "Error: Invalid arguments" << errno << std::endl;
		exit(1);
	}

	int file = open(argv[1], O_WRONLY);
	if(file < 0) {
		std::cerr << "Error: Failed to open the file" << errno << std::endl;
		exit(2);
	}

	if (dup2(file, 0) < 0) {
		std::cerr << "Error: Failed to redirect the stream" << errno << std::endl;
		close(file);
		exit(3);

	}
	close(file);

}

int main(int argc, char** argv) {
	initilize(argc, argv);

	std::string input;
	std::cin >> input;

	std::string reversed(input.rbegin(), input.rend());

	std::cout << reversed << std::endl;

	return 0;
}
