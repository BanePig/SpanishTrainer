#ifndef TERM_H
#define TERM_H

#include <string>
#include <vector>

struct Term {
    std::string string;
    unsigned int correctAnswer;
    std::vector<std::string> possibleAnswers;
};

#endif//TERM_H