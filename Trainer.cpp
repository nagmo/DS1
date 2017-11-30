
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

/**
 * add gladiator to the tree. check if it the best so far,
 * if so update bestGladiator.
 * @param newGladiator
 */
void Trainer::AddGladiator(Gladiator &newGladiator) {
    if(newGladiator.GetLevel() > bestGladiator.GetLevel()){
        bestGladiator = Gladiator(newGladiator);
    }
    gladiators.Insert(newGladiator);
}

/**
 * return best gladiator
 * @return
 */
Gladiator& Trainer::GetBestGladiator() {
    return bestGladiator;
}

/**
 * return gladiators tree
 * @return
 */
GladiatorTree& Trainer::GetGladiatorsTree() {
    return gladiators;
}

/**
 * return trainer's id
 * @return
 */
TrainerID Trainer::GetID() {
    return id;
}