
#ifndef EX1_TRAINER_H
#define EX1_TRAINER_H

#include "utility.h"
#include "Gladiator.h"
#include "SplayTree.h"

class Trainer {

public:

    Trainer(TrainerID);
    ~Trainer();
    void AddGladiator(Gladiator&);

private:

    TrainerID id;
    Gladiator bestGladiator;
    SplayTree* gladiators;

};


#endif //EX1_TRAINER_H
