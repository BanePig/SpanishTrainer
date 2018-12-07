#include "Vocabulary.hpp"

std::vector<std::string> Vocabulary::split(std::string s, std::string delimiter)
{
    std::string string = s;
    std::vector<std::string> words;

    size_t last = 0;
    size_t next = 0;
    while ((next = s.find(delimiter, last)) != std::string::npos)
    {
        words.push_back(s.substr(last, next - last));
        last = next + 1;
    }
    auto endStr = s.substr(last, next - last);
    if (endStr != "")
        words.push_back(endStr);

    return words;
}

std::string Vocabulary::trim(const std::string &str, const std::string &whitespace)
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

Vocabulary::Vocabulary()
{
    std::ifstream file;
    file.open("..\\..\\words.txt", std::fstream::in | std::fstream::out);
    if (!file.is_open())
        std::cout << "Failed to open file";

    std::string str;
    auto line = 1;
    while (std::getline(file, str))
    {
        auto splitStr = split(str, ":");

        if (splitStr.size() != 0)
        {
            if (splitStr.size() < 2)
                std::cout << "Line " << line << " does not contain a ':' character. Line will be ignored.\n";
            else if (splitStr.size() > 2)
                std::cout << "Line " << line << " contains multiple ':' characters. Line will be ignored.\n";
            else
                definitions.push_back({trim(splitStr[1]), trim(splitStr[0])}); // Add definition if no errors on line found.
        }

        file.clear();

        line++;
    }
    file.close();
}