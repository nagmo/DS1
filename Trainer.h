
#ifndef EX1_TRAINER_H
#define EX1_TRAINER_H

#include "utility.h"
#include "Gladiator.h"
#include "SplayTree.h"
class GladiatorTree;

class Trainer {

public:

    Trainer(TrainerID);
    ~Trainer();
    //remeber to update the bestGlad of a trainer
    void AddGladiator(Gladiator&);
    Gladiator& GetBestGladiator();
    GladiatorTree& GetGladiatorsTree();
    TrainerID GetID();

private:

    TrainerID id;
    Gladiator bestGladiator;
    GladiatorTree& gladiators;

};


#endif //EX1_TRAINER_H
