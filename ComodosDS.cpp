
#include "ComodosDS.h"

//todo: wrap wrappertree with gladiator and save max glad,override insert override delete
//todo: Yuval -> is it done? the wrappers are in the header..

/**
 * use to create a new instant of ComodosDS
 * use inside try block
 */
ComodosDS::ComodosDS() : trainers(TrainerTree()), gladiators(GladiatorTree()) {}
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
    try{
        trainers.AddTrainer(newTrainer);
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
    //check if trainer exists
    Trainer tempTrainer = Trainer(trainID);
    //find the trainer
    //if doesnt exist, would throw FailureException, remove gladiator from glad tree
    try{
        Trainer currTrainer = trainers.Find(tempTrainer);
        //add glad to currTrainer
        //create new gladiator
        Gladiator newGlad = Gladiator(gladID, &currTrainer, level);
        //try add to gladiators tree
        //in case of an error will throw exception
        try {
            gladiators.AddGladiator(newGlad);
        }
        catch (TreeElementAllreadyInTreeException&){
            throw FailureException();
        }
        currTrainer.AddGladiator(newGlad);
    }
        //case of trainer doesnt exist
    catch (TreeElementNotInTreeException&){
        throw FailureException();
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
    //save trainer id in order to find the trainer
    TrainerID trainerID = tempGlad.GetTrainer()->GetID();
    //remove glad from gald tree
    //todo: yuval - add try
    try{
        gladiators.DeleteGladiator(tempGlad);
    }
    catch (TreeElementNotInTreeException&){
        throw FailureException();
    }
    //remove glad from trainer
    //create an instant of trainer
    Trainer tempTrainer = Trainer(trainerID);
    //get the current trainer
    //not inside try because trainer must exists
    Trainer currTrainer = trainers.Find(tempTrainer);
    //remove gladiator from trainer
    //update the bestGlad should happen in the remove function
    //todo: change trainer.h
    currTrainer.GetGladiatorsTree().DeleteGladiator(tempGlad);
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
    try{
        //if not exists should throw exception
        Gladiator currGlad = gladiators.Find(tempGlad);

        //update gladiator level
        currGlad.IncreaseLevel(levelIncrease);
        //remove and inset from trainers tree
        currGlad.GetTrainer()->GetGladiatorsTree().DeleteGladiator(tempGlad);
        currGlad.GetTrainer()->GetGladiatorsTree().AddGladiator(currGlad);
    }
    catch (TreeElementNotInTreeException&){
        throw FailureException();
    }
}

GladiatorID ComodosDS::GetTopGladiator(TrainerID trainerID){
    if(trainerID == 0) throw InvalidInputException();
    if(trainerID < 0){
        return gladiators.getMaxElement().GetGladiatorID();
    }
    //search for trainer
    //create an instant of a trainer
    Trainer tempTrainer = Trainer(trainerID);
    //search in trainers tree
    try{
        //if not found, should throw exception
        Trainer currTrainer = trainers.Find(tempTrainer);
        return currTrainer.GetBestGladiator().GetGladiatorID();
    }
    catch (TreeElementNotInTreeException&){
        throw FailureException();
    };
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
    try{
        Gladiator currGlad = gladiators.Find(tempGlad);

        //creating the new gladiator
        Gladiator newGlad = Gladiator(newGladID, currGlad.GetTrainer(), currGlad.GetLevel());
        //delete glad from galdiators tree
        gladiators.Delete(currGlad);
        gladiators.Insert(newGlad);

        //update the trainers tree
        Trainer* currTrainer = newGlad.GetTrainer();
        //delete the glad from its trainer
        currTrainer->GetGladiatorsTree().DeleteGladiator(tempGlad);
        currTrainer->GetGladiatorsTree().AddGladiator((newGlad));
    }
    catch (TreeElementNotInTreeException&){
        throw InvalidInputException();
    }

}
void UpdateLevels(StimulantCode, StimulantFactor);


GladiatorTree::GladiatorTree() : SplayTreeWrapper<Gladiator>(), bestGladiator(Gladiator(1)){}

void GladiatorTree::UpdateBestGladiator(Gladiator& gladiator){
    bestGladiator = Gladiator(gladiator);
}
void GladiatorTree::AddGladiator(Gladiator& gladiator) {
    Insert(gladiator);
    //if is better
    if(gladiator.GetLevel() > bestGladiator.GetLevel() || (gladiator.GetLevel() == bestGladiator.GetLevel() &&
            gladiator.GetGladiatorID() < bestGladiator.GetGladiatorID())){
        bestGladiator = Gladiator(gladiator);
    }
}

void GladiatorTree::DeleteGladiator(Gladiator& gladiator){
    if(gladiator.GetGladiatorID() == bestGladiator.GetGladiatorID()){
        //todo: Yuval - fixed.
        bestGladiator = Gladiator(this->getMaxElement());
    }
    Delete(gladiator);

}

TrainerTree::TrainerTree() : SplayTreeWrapper<Trainer>(){};

void TrainerTree::DeleteGladiator(Gladiator& gladiator){
    //todo: after changing trainer.h->gladiators
}