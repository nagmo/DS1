
#include "Trainer.h"

#define DUMMY -1

/**
 * creates a dummy "bestGladiator" with an id of -1 and level of -1.
 * @param id
 */
Trainer::Trainer(TrainerID id) : id(id){
    bestGladiator = Gladiator(DUMMY, nullptr, DUMMY);
    gladiators = GladiatorTree();
}

void Trainer::AddGladiator(Gladiator &newGladiator) {
    if(newGladiator.GetLevel() > bestGladiator.GetLevel()){
        bestGladiator = Gladiator(newGladiator);
    }
    gladiators.Insert(newGladiator);
}

Gladiator& Trainer::GetBestGladiator() {
    return bestGladiator;
}

GladiatorTree& Trainer::GetGladiatorsTree() {
    return gladiators;
}

TrainerID Trainer::GetID() {
    return id;
}