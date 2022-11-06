#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <list>
#include <string>

std::list<std::string> split(std::string line);

std::list<std::string> clear_tokens(std::list<std::string> tokens);

std::list<std::string> interpret_line(std::string line);

#endif // FILE_UTILS_H
