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