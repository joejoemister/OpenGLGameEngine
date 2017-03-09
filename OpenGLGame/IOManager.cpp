#include "IOManager.h"

#include <fstream>

bool IOManager::readFileToBuffer(string filePath, vector<unsigned char>& buffer) {
	ifstream file(filePath, ios::binary);

	if (file.fail()) {
		perror(filePath.c_str());
		return false;
	}

	// Seek to the end
	file.seekg(0, ios::end);

	// Get file size
	int fileSize = file.tellg();
	file.seekg(0, ios::beg);

	// Reduce file size
	fileSize -= file.tellg();

	buffer.resize(fileSize);

	file.read((char *) &(buffer[0]), fileSize);
	file.close();

	return true;
}
