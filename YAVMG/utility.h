#ifndef UTILITY_H
#define UTILITY_H

#include <windows.h>
#include <cstdint>
#include <string>
#include <vector>

class FileUtils {
  public:
	static uint64_t filetime_to_uint64(FILETIME *ft);

};

class StrUtils {
  public:
    static std::vector<std::string> split(std::string &str, const char *delim);
    static std::string join(std::vector<std::string> &tokens, const char *delim);

};

#endif