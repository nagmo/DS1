
#ifndef EX1_UTILITY_H
#define EX1_UTILITY_H

#include <exception>

typedef int TrainerID;
typedef int GladiatorID;
typedef int Level;
typedef int StimulantCode;
typedef int StimulantFactor;
typedef int LevelIncrease;

struct GladByLevel{
    int numOfGlads;
    int* gladiators;
};

using std::exception;

class InvalidInputException : exception{};
class FailureException : exception{};

#endif //EX1_UTILITY_H
