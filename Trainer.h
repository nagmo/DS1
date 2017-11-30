
#ifndef EX1_TRAINER_H
#define EX1_TRAINER_H

#include "utility.h"
#include "Gladiator.h"
#include "SplayTree.h"
#include "ComodosDS.h"
//todo: Yuval - can we include comodos here? isn't it an inclusion circle?

class GladiatorTree;

class Trainer {

public:

    /**
    * creates a dummy "bestGladiator" with an id of -1 and level of -1.
    * @param id
    */
    explicit Trainer(TrainerID);
    ~Trainer() = default;
    void AddGladiator(Gladiator&);
    Gladiator& GetBestGladiator();
    GladiatorTree& GetGladiatorsTree();
    TrainerID GetID();

private:

    TrainerID id;
    Gladiator bestGladiator;
    GladiatorTree gladiators;

};


#endif //EX1_TRAINER_H
