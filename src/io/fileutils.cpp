#include "fileutils.h"
#include <fstream>
#include <sstream>

std::string FileUtils::GetFileToString(std::string filename) {
	std::ifstream inFile;
	inFile.open(filename);

	std::stringstream strStream;
	strStream << inFile.rdbuf();
	std::string str = strStream.str();
	return str;
}

void FileUtils::WriteStringToFile(std::string filename, std::string string) {
	std::ofstream file;
	file.open(filename);

	file.write(string.c_str(),string.length());
}

void FileUtils::RemoveFile(std::string filename) {
	remove(filename.c_str());
}