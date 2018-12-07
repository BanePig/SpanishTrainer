#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <regex>

class Vocabulary
{
    std::vector<std::string> split(std::string s, std::string delimiter);

    
    std::string trim(const std::string& str, const std::string& whitespace = " ");

  public:
    std::vector<std::pair<std::string, std::string>> definitions;

    Vocabulary();
};

#endif //VOCABULARY_H