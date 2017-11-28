
#ifndef EX1_COMODOSDS_H
#define EX1_COMODOSDS_H

#include "utility.h"
#include "SplayTree.h"
#include "Gladiator.h"
#include "Trainer.h"

using std::exception;
class ComodosDS {

public:

    ComodosDS();
    ~ComodosDS();
    void AddTrainer(TrainerID);
    void BuyGladiator(GladiatorID, TrainerID, Level);
    void FreeGladiator(GladiatorID);
    void LevelUp(GladiatorID, LevelIncrease);
    GladiatorID GetTopGladiator(TrainerID);
    GladByLevel GetAllGladiatorsByLevel(TrainerID);
    void UpgradeGladiator(GladiatorID, GladiatorID);
    void UpdateLevels(StimulantCode, StimulantFactor);

private:

    SplayTree<Trainer> trainers;
    SplayTree<Gladiator> gladiators;
    SplayTree<LevelsNode> levels;
    Gladiator bestGladiator;
    /**
     * decrease numOfGlads in the siutable level
     * if is the last glad, it deletes the Node
     */
    void RemoveGladiatorFromLevelsTree(Level);
    void AddGladiatorToLevelsTree(Level);
};


#endif //EX1_COMODOSDS_H
