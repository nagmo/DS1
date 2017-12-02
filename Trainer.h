
#ifndef EX1_TRAINER_H
#define EX1_TRAINER_H

#include "utility.h"
#include "Gladiator.h"
#include "SplayTree.h"
#include "ComodosDS.h"

class GladiatorTree;

class Trainer {

public:
    /**
    * creates a dummy "bestGladiator" with an id of -1 and level of -1.
    * @param id
    */
    explicit Trainer(TrainerID, bool = true);

    Trainer(const Trainer&);
    /**
    * default destructor is not fine here.
    */
    ~Trainer();

    /**
    * add gladiator to the tree. check if it the best so far,
    * if so update bestGladiator.
    * @param newGladiator
    */
    void AddGladiator(Gladiator&);

    /**
    * return best gladiator
    * @return
    */
    Gladiator& GetBestGladiator();

    void SetBestGladiator();
    /**
    * return gladiators tree
    * @return
    */
    GladiatorTree* GetGladiatorsTree();

    /**
    * return trainer's id
    * @return
    */
    TrainerID GetID();

    bool operator==(const Trainer& trainer){
        return id == trainer.id;
    }

    bool operator<(const Trainer& trainer){
        return id < trainer.id;
    }

    bool operator>(const Trainer& trainer){
        return !(*this==trainer || *this<trainer);
    }

private:

    TrainerID id;
    Gladiator bestGladiator;
    GladiatorTree* gladiators;

};


#endif //EX1_TRAINER_H
