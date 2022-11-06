#include "file_utils.h"

std::list<std::string> split(std::string line)
{
    std::list<std::string> tokens;

    unsigned int start = 0;
    while (line[start] == ' ' || line[start] == '\t' || line[start] == '\n' || line[start] == '\r')
        start++;
    line = line.substr(start, std::string::npos);

    if (line.length() == 1 && (line[0] == '{' || line[0] == '}')) {
        tokens.push_back(line);
        return tokens;
    }

    start = 0;
    unsigned int index_iterator = 1;
    while (index_iterator < line.length()) {

        if (line[index_iterator] == ' ') {
            while ((index_iterator + 1) < line.length() && line[index_iterator + 1] == ' ')
                index_iterator++;

            std::string new_token = line.substr(start, index_iterator - start);
            tokens.push_back(new_token);

            start = index_iterator + 1;
            index_iterator += 2;
        }

        else if (line[index_iterator] == '/') {
            std::string newToken = line.substr(start, (index_iterator - start));
            tokens.push_back(newToken);
            tokens.push_back("/");

            index_iterator++;

            if (line[index_iterator] == '/') {
                tokens.push_back("/");
                index_iterator++;
            }
            start = index_iterator;

        } else
            index_iterator++;
    }

    if (start <= line.length() - 1)
        tokens.push_back(line.substr(start, std::string::npos));

    return tokens;
}

std::list<std::string> clear_tokens(std::list<std::string> tokens)
{
    std::list<std::string>::iterator iterator = tokens.begin();
    while (iterator != tokens.end()) {
        std::string currentLine = *iterator;

        unsigned int start = 0;
        while (start < currentLine.length() && (currentLine[start] == ' ' || currentLine[start] == '(' || currentLine[start] == '\t' || currentLine[start] == '\"')) {
            start++;
        }

        int end = (int)currentLine.length() - 1;
        while (end >= 0 && (currentLine[end] == ' ' || currentLine[end] == ',' || currentLine[end] == ')' || currentLine[end] == '\t' || currentLine[end] == '\"' || currentLine[end] == '\n' || currentLine[end] == '\r')) {
            end--;
        }

        if (end < (int)start) {
            std::list<std::string>::iterator temp = iterator;
            ++iterator;
            tokens.erase(temp);
        } else {
            *iterator = currentLine.substr(start, end - start + 1);
            ++iterator;
        }
    }

    return tokens;
}

std::list<std::string> interpret_line(std::string line)
{

    // Удаляем пробелы в начале строки
    unsigned int start = 0;
    while (start < line.length() && (line[start] == ' ' || line[start] == '\t' || line[start] == '\n' || line[start] == '\r'))
        start++;
    if (start != 0)
        line = line.substr(start, std::string::npos);

    // Обработка пустых строк или комментариев:
    if (line.empty() || line[0] == '#')
        return std::list<std::string>(); // Nothing to insert: Return an empty list

    // Разбиваем строку, затем очищаем каждый токен от ненужных символов форматирования:
    std::list<std::string> tokens = clear_tokens(split(line));

    return tokens;
}
