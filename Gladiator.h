//
// Created by Nevo Agmon on 27/11/2017.
//

#ifndef EX1_GLADIATOR_H
#define EX1_GLADIATOR_H

#include "utility.h"

class Gladiator {

public:

    Gladiator();
    ~Gladiator();
    Gladiator(const Gladiator);

private:

    GladiatorID id;
    Level level;
    TrainerID trainer;
};


#endif //EX1_GLADIATOR_H
