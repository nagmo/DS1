
#ifndef EX1_COMODOSDS_H
#define EX1_COMODOSDS_H

#include "utility.h"
#include "SplayTree.h"
#include "Gladiator.h"
#include "Trainer.h"
#include "GladByID.h"

using std::exception;

class GladiatorTree : SplayTreeWrapper<Gladiator>{
public:
    GladiatorTree();
    //todo: Yuval - I think we should just ignore the destructor. and the "SplayTreeWrapper<Gladiator>"'s D'tor will be used.
    //~GladiatorTree() = default;
    void UpdateBestGladiator(Gladiator&);
    void AddGladiator(Gladiator&);
    void DeleteGladiator(Gladiator&);

private:
    Gladiator bestGladiator;

};

class TrainerTree : SplayTreeWrapper<Trainer>{
public:
    //todo: Yuval - here too.
    TrainerTree();
    //~TrainerTree() = default;
    //todo: yuval - why not use parent insert and delete? no special action needed
    void DeleteGladiator(Gladiator&);
    void AddTrainer(Trainer&);
private:
};

class ComodosDS {

public:

    ComodosDS();
    ~ComodosDS() = default;
    /**
     * use inside try block
     * exceptions:
     * InvalidInputException - trainerID <= 0
     * FailureException - trainerID exists
     */
    void AddTrainer(TrainerID);
    /**
     * add glad to galdTree
     * add it to the trainer tree
     * check if is the best glad
     *
     * exceptions:
     * InvalidInputException - trainerID || gladId || level <= 0
     * FailureException - trainerID does not exist or glad exists
     * @param galdID
     * @param trainID
     * @param level
     */
    void BuyGladiator(GladiatorID, TrainerID, Level);
    /**
     * delete the gladiator from glads tree and from its trainer tree
     * aslo, update the levels tree
     */
    void FreeGladiator(GladiatorID);
    /**
     * update the level of a Gladiator
     * update the levels tree
     * @param gladID
     * @param levelIncrease
    */
    void LevelUp(GladiatorID, LevelIncrease);
    GladiatorID GetTopGladiator(TrainerID);
    GladByLevel GetAllGladiatorsByLevel(TrainerID);
    /**
    * change gladiator Id
    * update it in the glads tree and in the trainers tree
    * @param currGladID
    * @param newGladID
    */
    void UpgradeGladiator(GladiatorID, GladiatorID);
    void UpdateLevels(StimulantCode, StimulantFactor);

private:

    TrainerTree trainers;
    GladiatorTree gladiators;
};


#endif //EX1_COMODOSDS_H
