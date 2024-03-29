#pragma once
#include <string>

class FileUtils {
public:
	static std::string GetFileToString(std::string filename);
	static void WriteStringToFile(std::string filename, std::string string);
	static void RemoveFile(std::string filename);
};