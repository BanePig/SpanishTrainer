#include <iostream>
#include "vocabulary/Vocabulary.hpp"
#include "vocabulary/Term.hpp"
#include <random>

Vocabulary &vocabulary = *new Vocabulary();

Term createTerm(std::pair<std::string, std::string> pair, bool first, int numAnswers)
{
    static auto vectorContains = [](std::vector<std::string> vec, std::string str)
    {
        for(std::string val : vec)
        {
            if(val == str) return true;
        }
        return false;
    };

    auto term = Term();
    term.string = first ? pair.first : pair.second;
    term.correctAnswer = std::rand() % numAnswers;
    for (int i = 0; i < numAnswers ; i++)
    {
        if (i == term.correctAnswer)
        {
            term.possibleAnswers.push_back(first ? pair.second : pair.first);
            continue;
        }

        std::vector<std::string> invalidAnswers = { first ? pair.second : pair.first };
        std::string possibleAnswer;
        do
        {
            auto& defPair = vocabulary.definitions[std::rand() % vocabulary.definitions.size()];
            possibleAnswer = first ? defPair.second : defPair.first;
        } while (vectorContains(invalidAnswers, possibleAnswer));
        invalidAnswers.push_back(possibleAnswer);
        term.possibleAnswers.push_back(possibleAnswer);
    }
    return term;
}

int getIntInput(int lowerBound, int upperBound)
{
    int returnVal = -1;
    while (returnVal == -1)
    {
        std::string response;
        std::cin >> response;
        try
        {
            returnVal = std::stoi(response);
            if (returnVal < lowerBound || returnVal > upperBound)
            {
                returnVal = -1;
                std::cout << "Invalid response. Number be between " + std::to_string(lowerBound) + " and " + std::to_string(upperBound) << std::endl;
            }
        }
        catch (std::invalid_argument)
        {
            std::cout << "Invalid response.\n";
        }
    }
    return returnVal;
}

int main()
{
    if (vocabulary.definitions.size() == 0)
    {
        std::cout << "No words supplied. Stopping...\n";
        return 0;
    }

    std::cout << "How many possible answers would you like?\n";
    int numAnswers = getIntInput(1, vocabulary.definitions.size() - 2);

    int round = 1;
    while (true)
    {
        std::cout << "\nRound " + std::to_string(round) + "...\n\n\n";

        std::vector<Term> remainingTerms;
        for (auto pair : vocabulary.definitions)
        {
            remainingTerms.push_back(createTerm(pair, false, numAnswers));
            remainingTerms.push_back(createTerm(pair, true, numAnswers));
        }

        while (remainingTerms.size() != 0)
        {
            auto termIndex = std::rand() % remainingTerms.size();
            auto term = remainingTerms[termIndex];

            std::cout << term.string << ":" << std::endl;

            for (int i = 0; i < term.possibleAnswers.size(); i++)
            {
                std::cout << i + 1 << ". " << term.possibleAnswers[i] << std::endl;
            }

            std::cout << "> ";

            int answer = getIntInput(1, numAnswers);
            if (answer - 1 == term.correctAnswer)
            {
                std::cout << "Correct answer.\n\n";
                remainingTerms.erase(remainingTerms.begin() + termIndex);
            }
            else
                std::cout << "Wrong answer. Correct answer is: " + std::to_string(term.correctAnswer + 1) + "\n\n";
        }

        round++;
    }
}