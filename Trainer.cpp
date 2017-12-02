
#include "Trainer.h"

#define DUMMY -1
/**
 * creates a dummy "bestGladiator" with an id of -1 and level of -1.
 * @param id
 */
Trainer::Trainer(TrainerID id, bool withGladTree) :
        id(id), bestGladiator(Gladiator(DUMMY, NULL, DUMMY)){
    if(withGladTree) gladiators = new GladiatorTree();
    else gladiators = NULL;
}
/**
 * copy constructor, use only for a new trainer (without glads tree)
 * @param t
 */
Trainer::Trainer(const Trainer& t) : id(t.id), bestGladiator(t.bestGladiator){
    gladiators = new GladiatorTree();
}

Trainer::~Trainer(){
    if(gladiators != NULL) delete gladiators;
}

/**
 * add gladiator to the tree. check if it the best so far,
 * if so update bestGladiator.
 * @param newGladiator
 */
void Trainer::AddGladiator(Gladiator &newGladiator) {
    gladiators->AddGladiator(newGladiator);
    if(newGladiator.GetLevel() > bestGladiator.GetLevel()){
        bestGladiator = Gladiator(newGladiator);
    }
}

/**
 * return best gladiator
 * @return
 */
Gladiator& Trainer::GetBestGladiator() {
    return bestGladiator;
}

void Trainer::SetBestGladiator(){
    Gladiator* newBestGladiator = gladiators->GetGladiatorsTree().GetMaxElement();
    bestGladiator = (newBestGladiator == NULL) ? Gladiator(-1) : Gladiator(*newBestGladiator);
}
/**
 * return gladiators tree
 * @return
 */
GladiatorTree* Trainer::GetGladiatorsTree() {
    return gladiators;
}

/**
 * return trainer's id
 * @return
 */
TrainerID Trainer::GetID() {
    return id;
}