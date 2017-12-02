
#include <iostream>
#include "ComodosDS.h"

/**
 * use to create a new instant of ComodosDS
 * use inside try block
 */
ComodosDS::ComodosDS() : trainers(TrainerTree()),
                         gladiators(GladiatorTree()), gladiatorsByLevel(GladiatorTree()){
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
    try{
        trainers.Insert(newTrainer);
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
    Trainer tempTrainer = Trainer(trainID, false);
    //find the trainer
    //if doesnt exist, would throw FailureException, remove gladiator from glad tree
    try{
        Trainer& currTrainer = trainers.Find(tempTrainer);
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
        try{
            newGlad.SetFlag(true);
            gladiatorsByLevel.AddGladiator(newGlad);
        }
        catch (TreeElementAllreadyInTreeException&){
            newGlad.SetFlag(false);
            gladiators.DeleteGladiator(newGlad);
            throw FailureException();
        }
        try{
            currTrainer.AddGladiator(newGlad);
        }
        catch(TreeElementAllreadyInTreeException&){
            gladiatorsByLevel.DeleteGladiator(newGlad);
            newGlad.SetFlag(true);
            gladiators.DeleteGladiator(newGlad);
            throw FailureException();
        }
    }
        //case of trainer doesnt exist
    catch (TreeElementNotInTreeException&) {
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
    try{
        gladiators.DeleteGladiator(tempGlad);
    }
    catch (TreeElementNotInTreeException&){
        throw FailureException();
    }
    try{
        tempGlad.SetFlag(true);
        gladiatorsByLevel.DeleteGladiator(tempGlad);
    }
    catch (TreeElementNotInTreeException&){
        std::cout << " Ha Ha " << std::endl;
    }
    //remove glad from trainer
    //create an instant of trainer
    Trainer tempTrainer = Trainer(trainerID);
    //get the current trainer
    //not inside try because trainer must exists
    Trainer currTrainer = trainers.Find(tempTrainer);
    //remove gladiator from trainer
    //update the bestGlad should happen in the remove function
    currTrainer.GetGladiatorsTree()->DeleteGladiator(tempGlad);
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
        Gladiator currGlad = gladiators.GetGladiatorsTree().Find(tempGlad);

        //update gladiator level
        currGlad.IncreaseLevel(levelIncrease);
        //remove and inset from trainers tree
        currGlad.GetTrainer()->GetGladiatorsTree()->DeleteGladiator(tempGlad);
        currGlad.GetTrainer()->GetGladiatorsTree()->AddGladiator(currGlad);
    }
    catch (TreeElementNotInTreeException&){
        throw FailureException();
    }
}

GladiatorID ComodosDS::GetTopGladiator(TrainerID trainerID){
    if(trainerID == 0) throw InvalidInputException();
    if(trainerID < 0){
        return gladiatorsByLevel.GetGladiatorsTree().GetMaxElement().GetGladiatorID();
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

GladByLevel ComodosDS::GetAllGladiatorsByLevel(TrainerID trainerID){
    if(trainerID == 0) throw InvalidInputException();
    GladByLevel gladByLevel = GladByLevel();
    //get all glads
    if(trainerID<0){
        gladByLevel.SetNumOfGlads(this->gladiatorsByLevel.GetGladiatorsTree().size());
        this->gladiatorsByLevel.GetGladiatorsTree().InOrder((SplayTreeWrapper<Gladiator>::Func)&gladByLevel, true);
        return gladByLevel;
    }
    //get by trainer
    Trainer tempTrainer = Trainer(trainerID);
    try{
        Trainer currTrainer = trainers.Find(tempTrainer);
        gladByLevel.SetNumOfGlads(currTrainer.GetGladiatorsTree()->GetGladiatorsTree().size());
        currTrainer.GetGladiatorsTree()->GetGladiatorsTree().InOrder((SplayTreeWrapper<Gladiator>::Func)&gladByLevel, true);
        return gladByLevel;
    }catch (TreeElementNotInTreeException&){
        throw FailureException();
    }
}

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
        Gladiator currGlad = gladiators.GetGladiatorsTree().Find(tempGlad);

        //creating the new gladiator
        Gladiator newGlad = Gladiator(newGladID, currGlad.GetTrainer(), currGlad.GetLevel());
        //delete glad from galdiators tree
        gladiators.GetGladiatorsTree().Delete(currGlad);
        gladiators.GetGladiatorsTree().Insert(newGlad);

        //update the trainers tree
        Trainer* currTrainer = newGlad.GetTrainer();
        //delete the glad from its trainer
        currTrainer->GetGladiatorsTree()->DeleteGladiator(tempGlad);
        currTrainer->GetGladiatorsTree()->AddGladiator((newGlad));
    }
    catch (TreeElementNotInTreeException&){
        throw InvalidInputException();
    }

}
void ComodosDS::UpdateLevels(StimulantCode stimulantCode, StimulantFactor stimulantFactor){
    if(stimulantCode < 1 || stimulantFactor < 1) throw InvalidInputException();
    gladiators.UpdateLevels(stimulantCode, stimulantFactor);


}
class UpdateLevelsClass{
public:
    UpdateLevelsClass(StimulantCode code, StimulantFactor factor) : stimulantCode(code),
    stimulantFactor(factor){};
    bool operator()(Gladiator& gladiator){
        if(gladiator.GetGladiatorID()%stimulantCode == 0) {
            gladiator.MultiplyLevel(stimulantFactor);
            return true;
        }
        return false;
    };
private:
    StimulantCode stimulantCode;
    StimulantFactor stimulantFactor;
};

void GladiatorTree::UpdateLevels(StimulantCode stimulantCode, StimulantFactor stimulantFactor){
    //creating the function class
    UpdateLevelsClass updateLevels = UpdateLevelsClass(stimulantCode, stimulantFactor);

    /*
    //test
    Gladiator g = Gladiator(1);
    ((SplitAndSortTree<Gladiator>::BoolFunc)&updateLevels)(g);
    //endTest
*/

    //create a class for the inOrder traversal - OK
    SplitAndSortTree<Gladiator> sortTree =
            SplitAndSortTree<Gladiator>((SplitAndSortTree<Gladiator>::BoolFunc)&updateLevels, tree.size());
    //do inOrder traversal to create the two arrays - OK
    tree.InOrder((SplayTree<Gladiator>::Func)&sortTree);
    //create a new tree with the merged array. -> someone must delete the merges array!!
    // I added it to the destructor of the splitAndSort class.
    //the recursive function does NOT create a tree! I'll try to fix it.
    SplayTreeWrapper<Gladiator>* tempTree = sortTree.MakeTreeFromArray(sortTree.merge(), tree.size());
    //we save to tree as a value and not as pointer. so how does the old tree gets deleted and the new one os saved?
    //this syntax doesn't do it properly.
    tree = *tempTree;
}

GladiatorTree::GladiatorTree() : tree(SplayTreeWrapper<Gladiator>()), bestGladiator(Gladiator(-1)){}

void GladiatorTree::UpdateBestGladiator(Gladiator& gladiator){
    bestGladiator = Gladiator(gladiator);
}
void GladiatorTree::AddGladiator(Gladiator& gladiator) {
    tree.Insert(gladiator);
    //if is better
    if(gladiator.GetLevel() > bestGladiator.GetLevel() || (gladiator.GetLevel() == bestGladiator.GetLevel() &&
            gladiator.GetGladiatorID() < bestGladiator.GetGladiatorID())){
        bestGladiator = Gladiator(gladiator);
    }
}

void GladiatorTree::DeleteGladiator(Gladiator& gladiator){
    tree.Delete(gladiator);
    if(gladiator.GetGladiatorID() == bestGladiator.GetGladiatorID()){
        bestGladiator = Gladiator(tree.GetMaxElement());
    }
}

SplayTreeWrapper<Gladiator>& GladiatorTree::GetGladiatorsTree(){
    return tree;
}



