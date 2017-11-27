//
// Created by Nevo Agmon on 27/11/2017.
//

#include "ComodosDS.h"


/**
 * use to create a new instant of ComodosDS
 * use inside try block
 */
ComodosDS::ComodosDS(){
    trainers = SplayTree<Trainer>();
    gladiators = SplayTree<Gladiator>();
    levels = SplayTree<Level>();
    bestGladiator = nullptr;
}

ComodosDS::~ComodosDS(){
    delete levels;
    delete gladiators;
    delete trainers;
    delete bestGladiator;
}
/**
 * use inside try block
 * exceptions:
 * InvalidInputException - trainerID <= 0
 * FailureException - trainerID exists
 */
void ComodosDS::AddTrainer(TrainerID id){
    if(id <= 0) throw InvalidInputException();
    //not inside try to let exception get to 'C' function
    Trainer newTrainer = Trainer(id);
    //should throw an exception in case of an error
    trainers.Insert(newTrainer);
}
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
void ComodosDS:: BuyGladiator(GladiatorID galdID, TrainerID trainID, Level level){
    //handle errors
    if(galdID <= 0 || trainID <= 0 || level <= 0) throw InvalidInputException();
    //create new gladator
    Gladiator* newGlad = new Gladiator(galdID, level);
    //try add to gladiators tree
    //in case of an error will throw exception
    gladiators.Insert(*newGlad);
    //after insertion
    //try add to trainers
    //create instant of trainer
    Trainer tempTrainer = Trainer(trainID);
    //find the trainer
    //if doesnt exist, would throw FailureException
    Trainer currTrainer = trainers.Find(tempTrainer);
    //delete tempTrainer
    delete  tempTrainer;
    //add glad to currTrainer
    currTrainer.AddGladiator(*newGlad);

    //check if is the bestGlad
    //assume that glad has < operator
    if(bestGladiator == nullptr || bestGladiator < newGlad) {
        //replace best glad
        bestGladiator = newGlad;
    }
}
/**
 * check if is the best glad, if so look in each trainer for a new champ
 */
void FreeGladiator(GladiatorID);
void LevelUp(GladiatorID, LevelIncrease);
GladiatorID GetTopGladiator(TrainerID);
GladByLevel GetAllGladiatorsByLevel(TrainerID);
void UpgradeGladiator(GladiatorID, GladiatorID);
void UpdateLevels(StimulantCode, StimulantFactor);