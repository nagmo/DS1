//
// Created by Nevo Agmon on 27/11/2017.
//

#include "ComodosDS.h"


/**
 * use to create a new instant of ComodosDS
 * use inside try block
 */
ComodosDS::ComodosDS(){
    //bestGladiator with id = 1
    trainers = SplayTree<NodeWrapper<Trainer>>();
    gladiators = SplayTree<NodeWrapper<Gladiator>>();
}

ComodosDS::~ComodosDS(){
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
    NodeWrapper trainerWrapper = NodeWrapper<Trainer>(newTrainer);
    //should throw an exception in case of an error
    try{
        trainers.Insert(trainerWrapper);
    }
    catch (TreeElementAllreadyInTreeException&){
        throw FailureException();
    }
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
    try {
        gladiators.Insert(newGlad);
    }
    catch (TreeElementAllreadyInTreeException&){
        throw FailureException();
    }
    //after insertion
    //try add to trainers
    //create instant of trainer
    Trainer tempTrainer = Trainer(trainID);
    NodeWrapper tempNodeTrainer = NodeWrapper<Trainer>(tempTrainer);
    //find the trainer
    //if doesnt exist, would throw FailureException
    try{
        NodeWrapper currTrainer = trainers.Find(tempNodeTrainer);
        //add glad to currTrainer
        //update bestGlad of the trainer inside this function
        currTrainer.data.AddGladiator(newGlad);
    }
        //todo: yuval - add catch
    catch (exception&){}
}
/**
 * delete the gladiator from glads tree and from its trainer tree
 * aslo, update the levels tree
 */
void ComodosDS::FreeGladiator(GladiatorID gladID){
    if(gladID <= 0) throw InvalidInputException();
    //create an instant of glad
    Gladiator tempGlad = Gladiator(gladID);
    NodeWrapper<Gladiator> tempNodeGlad = NodeWrapper<Gladiator>(tempGlad);
    //get the current gladiator
    NodeWrapper<Gladiator> currGlad = gladiators.Find(tempNodeGlad);

    //create an instant of trainer
    Trainer tempTrainer = Trainer(tempGlad.GetTrainerID());
    NodeWrapper<Trainer> tempNodeTrainer = NodeWrapper<Trainer>(tempTrainer);
    try{
        //get the current trainer
        NodeWrapper currTrainer = trainers.Find(tempNodeTrainer);
        //remove gladiator from trainer
        //update the bestGlad should happen in the remove function
        currTrainer.data.GetGladiatorsTree().Delete(currGlad);
    }
        //todo: yuval - add catch
    catch (exception&){}
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
    NodeWrapper<Gladiator> tempNodeGlad = NodeWrapper<Gladiator>(tempGlad);
    try{
        //if not exists should throw exception
        NodeWrapper<Gladiator> currGlad = gladiators.Find(tempNodeGlad);

        //update gladiator level
        currGlad.data.IncreaseLevel(levelIncrease);
    }
        //todo: yuval - add catch
    catch (exception&){}
}

GladiatorID ComodosDS::GetTopGladiator(TrainerID trainerID){
    if(trainerID == 0) throw InvalidInputException();
    if(trainerID < 0){
        //todo: yuval - reutrn data from glads tree
    }
    //search for trainer
    //create an instant of a trainer
    Trainer tempTrainer = Trainer(trainerID);
    NodeWrapper<Trainer> tempNodeTrainer = NodeWrapper<Trainer>(tempTrainer);
    //search in trainers tree
    try{
        //if not found, should throw exception
        NodeWrapper<Trainer> currTrainer = trainers.Find(tempNodeTrainer);
        //todo: - add catch
        return currTrainer.data.GetBestGladiator().GetGladiatorID();
    }
    catch (exception&){};

}

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
    NodeWrapper<Gladiator> tempNodeGlad = NodeWrapper<Gladiator>(tempGlad);
    //todo: yuval - think about it
    NodeWrapper<Gladiator> currGlad = tempNodeGlad;
    try{
        currGlad = gladiators.Find(tempNodeGlad);
    }
        //todo: yuval - add catch
    catch (exception&){}
    //creating the new gladiator
    Gladiator newGlad = Gladiator(newGladID, currGlad.data.GetLevel(), currGlad.data.GetTrainerID());
    NodeWrapper<Gladiator> newNodeGlad = NodeWrapper<Gladiator>(newGlad);
    //delete glad from galdiators tree
    gladiators.Delete(currGlad);
    gladiators.Insert(newNodeGlad);

    //update the trainers tree
    Trainer tempTrainer = Trainer(newGlad.GetTrainerID());
    NodeWrapper<Trainer> tempNodeTrainer = NodeWrapper<Trainer>(tempTrainer);
    NodeWrapper<Trainer> currTrainer = trainers.Find(tempNodeTrainer);
    //delete the glad from its trainer
    currTrainer.data.GetGladiatorsTree().Delete(currGlad);
    currTrainer.data.GetGladiatorsTree().Insert((newNodeGlad));
}
void UpdateLevels(StimulantCode, StimulantFactor);
