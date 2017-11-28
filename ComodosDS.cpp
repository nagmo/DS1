//
// Created by Nevo Agmon on 27/11/2017.
//

#include "ComodosDS.h"


/**
 * use to create a new instant of ComodosDS
 * use inside try block
 */
ComodosDS::ComodosDS() : bestGladiator(Gladiator(1)){
    //bestGladiator with id = 1
    trainers = SplayTree<Trainer>();
    gladiators = SplayTree<Gladiator>();
    levels = SplayTree<LevelsNode>();
}

ComodosDS::~ComodosDS(){
    delete levels;
    delete gladiators;
    delete trainers;
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
void ComodosDS:: BuyGladiator(GladiatorID gladID, TrainerID trainID, Level level){
    //handle errors
    if(gladID <= 0 || trainID <= 0 || level <= 0) throw InvalidInputException();
    //create new gladiator
    Gladiator newGlad = Gladiator(gladID, level);
    //try add to gladiators tree
    //in case of an error will throw exception
    gladiators.Insert(newGlad);
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
    //update bestGlad of the trainer inside this function
    currTrainer.AddGladiator(newGlad);

    //add level to level tree
    AddGladiatorToLevelsTree(level);
    //check if is the bestGlad
    //assume that Gladiator has < operator by Id
    if(bestGladiator.GetLevel() < newGlad.GetLevel() ||
            bestGladiator.GetLevel() == newGlad.GetLevel() && bestGladiator < newGlad) {
        //replace best glad
        //copy c'tor
        bestGladiator = newGlad;
    }
}
/**
 * delete the gladiator from glads tree and from its trainer tree
 * aslo, update the levels tree
 */
void ComodosDS::FreeGladiator(GladiatorID gladID){
    if(gladID <= 0) throw InvalidInputException();
    //create an instant of glad
    Gladiator tempGlad = Gladiator(gladID);
    //get the current gladiator
    Gladiator currGlad = gladiators.Find(tempGlad);

    //create an instant of trainer
    Trainer tempTrainer = Trainer(currGlad.GetTrainerID());
    //get the current trainer
    Trainer currTrainer = trainers.Find(tempTrainer);
    //remove gladiator from trainer
    //update the bestGlad should happen in the remove function
    currTrainer.GetGladiatorsTree().Delete(currGlad);

    //decrease the level Node in the level tree
    RemoveGladiatorFromLevelsTree(currGlad.GetLevel());
}
/**
 * update the level of a Gladiator
 * update the levels tree
 * @param gladID
 * @param levelIncrease
 */
void ComodosDS::LevelUp(GladiatorID gladID, LevelIncrease levelIncrease){
    if(gladID <= 0 || levelIncrease <= 0) throw InvalidInputException();
    //get the gladiator
    Gladiator tempGlad = Gladiator(gladID);
    //if not exists should throw exception
    Gladiator currGlad = gladiators.Find(tempGlad);

    //update levels tree
    //get curr level
    RemoveGladiatorFromLevelsTree(currGlad.GetLevel());

    //update gladiator level
    currGlad.IncreaseLevel(levelIncrease);
    //update levels tree
    AddGladiatorToLevelsTree(currGlad.GetLevel());
}

GladiatorID ComodosDS::GetTopGladiator(TrainerID);

GladByLevel GetAllGladiatorsByLevel(TrainerID);
/**
 * change gladiator Id
 * update it in the glads tree and in the trainers tree
 * @param currGladID
 * @param newGladID
 */
void ComodosDS::UpgradeGladiator(GladiatorID currGladID, GladiatorID newGladID){
    if(currGladID <= 0 || newGladID <= 0) throw InvalidInputException();
    //find the glad, delete it from the tree, update its ID and add it to the tree
    Gladiator tempGlad = Gladiator(currGladID);
    Gladiator currGlad = gladiators.Find(tempGlad);
    //creating the new gladiator
    Gladiator newGlad = Gladiator(newGladID, currGlad.GetLevel(), currGlad.GetTrainerID());
    //delete glad from galdiators tree
    gladiators.Delete(currGlad);
    gladiators.Insert(newGlad);

    //update the trainers tree
    Trainer tempTrainer = Trainer(newGlad.GetTrainerID());
    Trainer currTrainer = trainers.Find(tempTrainer);
    //delete the glad from its trainer
    currTrainer.GetGladiatorsTree().Delete(currGlad);
    currTrainer.GetGladiatorsTree().Insert((newGlad));
}
void UpdateLevels(StimulantCode, StimulantFactor);

/**
 * decrease numOfGlads in the siutable level
 * if is the last glad, it deletes the Node
 */
void ComodosDS::RemoveGladiatorFromLevelsTree(Level level){
    //create an instant of a level
    LevelsNode tempLevel = LevelsNode(level);
    LevelsNode currLevel = levels.Find(tempLevel);
    currLevel.DecNumOfGladiators();
    //check if level is empty, if so delete the level
    if(currLevel.GetNumOfGladiators() == 0){
        levels.Delete(currLevel);
    }
}

void ComodosDS::AddGladiatorToLevelsTree(Level level){
    //create an instant of levelNode
    LevelsNode tempNode = LevelsNode(level);
    //declare outside of try block
    LevelsNode levelNode = nullptr;
    try{
        levelNode = levels.Find(tempNode);
        //level exists
        //increase numOfGlads
        levelNode.IncNumOfGladiators();
    }
        //level is not set
    catch (FailureException&){
        //add the new level
        levels.Insert(levelNode);
    }
}