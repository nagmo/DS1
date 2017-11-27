
#ifndef EX1_COMODOSDS_H
#define EX1_COMODOSDS_H

#include "utility.h"
#include "SplayTree.h"
#include "Gladiator.h"

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

    SplayTree trainers;
    SplayTree gladiators;
    SplayTree levels;
    Gladiator bestGladiator;
};


#endif //EX1_COMODOSDS_H
