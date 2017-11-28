
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

class LevelsNode{
public:
    LevelsNode(Level);
    int GetNumOfGladiators();
    void IncNumOfGladiators();
    void DecNumOfGladiators();
    void ResetNumOfGladiators();
private:
    Level level;
    int numOfGladiators;
};

using std::exception;

class InvalidInputException : exception{};
class FailureException : exception{};

#endif //EX1_UTILITY_H
