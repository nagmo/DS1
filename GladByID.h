
#ifndef EX1_GLADBYID_H
#define EX1_GLADBYID_H

#include "utility.h"
#include "Gladiator.h"

class GladByLevel{
public:

    GladByLevel() : numOfGlads(0),gladiators(NULL) ,index(0){};

    ~GladByLevel(){
        delete[] gladiators;
    }

    GladByLevel(const GladByLevel& gladByLevel) : numOfGlads(gladByLevel.numOfGlads),
                                             gladiators(NULL), index(gladByLevel.index)
    {
        gladiators = new int[numOfGlads];
        for(int i=0;i<numOfGlads;i++){
            gladiators[i] = gladByLevel.gladiators[i];
        }
    }

    void operator()(Gladiator& gladiator){
        gladiators[index++] = gladiator.GetGladiatorID();
    }

    void SetNumOfGlads(int num){
        numOfGlads = num;
        gladiators = new int[num];
        index=0;
    }

    int GetNumOfGlads(){
        return numOfGlads;
    }

    int operator[](int i){
        return gladiators[i];
    }

private:
    int numOfGlads;
    int* gladiators;
    int index;
};

#endif //EX1_GLADBYID_H
