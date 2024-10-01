#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstring>

void Delete(const char* path) {
	int inf = open(path, O_WRONLY);
	if(inf == -1) {
		std::cerr << "Error: Cannot open the file" << std::endl;
		return;
	}

	struct stat fileInfo;
	if(fstat(inf, &fileInfo) == -1) {
		std::cerr << "Error: Cnnot gen an information about the file" << std::endl;
		close(inf);
		return;
	}

	off_t size = fileInfo.st_size;
	char* buffer = new char[size];

	memset(buffer, '\0', size);

	if(write(inf, buffer, size) != size) {
		std::cerr << "Error. Failed to write in the file" << std::endl;
	}

	delete[] buffer;
	close(inf);

	if(unlink(path) == -1) {
		std::cerr << "Error: Couldnt remove the file" << std::endl;
	}
	else {
		std::cout << "File is successfully deleted" << std::endl;
	}

}


int main(int argc, char* argv[]) {
	if(argc != 2) {
		std::cerr << "THe number of the arguments is wrong." << std::endl;
		return 1;
	}

	Delete(argv[1]);
	return 0;

}
