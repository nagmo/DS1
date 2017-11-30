
#ifndef EX1_GLADBYID_H
#define EX1_GLADBYID_H

#include "utility.h"
#include "Gladiator.h"

class GladByLevel{
public:

    ~GladByLevel(){
        delete[] gladiators;
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
