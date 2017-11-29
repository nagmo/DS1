
#ifndef EX1_TRAINER_H
#define EX1_TRAINER_H

#include "utility.h"
#include "Gladiator.h"
#include "SplayTree.h"
#include "NodeWrapper.h"

class Trainer {

public:

    Trainer(TrainerID);
    ~Trainer();
    //remeber to update the bestGlad of a trainer
    void AddGladiator(Gladiator&);
    Gladiator& GetBestGladiator();
    SplayTree<NodeWrapper<Gladiator>>& GetGladiatorsTree();

private:

    TrainerID id;
    Gladiator bestGladiator;
    SplayTree<Gladiator> gladiators;

};


#endif //EX1_TRAINER_H
