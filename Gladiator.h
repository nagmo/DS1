//
// Created by Nevo Agmon on 27/11/2017.
//

#ifndef EX1_GLADIATOR_H
#define EX1_GLADIATOR_H

#include "utility.h"

class Gladiator {

public:

    Gladiator(GladiatorID, Level = 0, TrainerID = 0);
    ~Gladiator();
    Gladiator(const Gladiator&);
    Level GetLevel();
    TrainerID GetTrainerID();
    void IncreaseLevel(LevelIncrease);
    bool operator==(Gladiator&);
    bool operator<(Gladiator&);
    bool operator>(Gladiator&);

private:

    GladiatorID id;
    Level level;
    TrainerID trainer;
};


#endif //EX1_GLADIATOR_H
