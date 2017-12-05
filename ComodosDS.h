
#ifndef EX1_COMODOSDS_H
#define EX1_COMODOSDS_H

#include "utility.h"
#include "Gladiator.h"
#include "Trainer.h"
#include "SplayTree.h"
#include "FuncWrapper_InOrder.h"

using std::exception;

class UpdateTrainersLevel;
template <class T>
class GladiatorTree{
public:
    GladiatorTree();
    void UpdateBestGladiator(Gladiator&);
    void AddGladiator(Gladiator&);
    void DeleteGladiator(Gladiator&);
    SplayTreeWrapper<Gladiator,T>& GetGladiatorsTree();
    void UpdateLevels(StimulantCode, StimulantFactor);
    void UpdateLevelsById(StimulantCode, StimulantFactor);
    bool IsNull(){ return tree.GetTree() == NULL;}
    GladiatorID GetBestGladiatorId(){ return bestGladiator.GetGladiatorID();}
private:
    SplayTreeWrapper<Gladiator,T> tree;
    Gladiator bestGladiator;

};


class TrainerTree {
public:
    TrainerTree() {
        tree = SplayTreeWrapper<Trainer, UpdateTrainersLevel>();
    }

    Trainer& getRootData(){ return tree.getRootData(); };

    Trainer& Find(Trainer& data){ return tree.Find(data); };

    void Insert(Trainer& newData){ tree.Insert(newData); };

    void Delete(Trainer& data){ tree.Delete(data); };

    int size(){ return tree.size(); }

    Trainer* GetMaxElement(){ return tree.GetMaxElement(); }

    void InOrder(StimulantCode code, StimulantFactor factor);

private:
    SplayTreeWrapper<Trainer,UpdateTrainersLevel> tree;
};

class ComodosDS {

public:

    ComodosDS();
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
    GladByLevel* GetAllGladiatorsByLevel(TrainerID);
    /**
    * change gladiator Id
    * update it in the glads tree and in the trainers tree
    * @param currGladID
    * @param newGladID
    */
    void UpgradeGladiator(GladiatorID, GladiatorID);
    //todo: implement
    void UpdateLevels(StimulantCode, StimulantFactor);

private:

    TrainerTree trainers;
    GladiatorTree<UpdateGladLevel> gladiators;
    GladiatorTree<FuncWrapper_InOrder<Gladiator> > gladiatorsByLevel;
};


#endif //EX1_COMODOSDS_H
