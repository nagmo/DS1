
#include <iostream>
#include "ComodosDS.h"

/**
 * use to create a new instant of ComodosDS
 * use inside try block
 */
ComodosDS::ComodosDS() : trainers(TrainerTree()),
                         gladiators(GladiatorTree<UpdateGladLevel>()),
                         gladiatorsByLevel(GladiatorTree<FuncWrapper_InOrder<Gladiator> >()){
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
    //check if glad exists.

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
    try{
        Gladiator& currGlad = gladiators.GetGladiatorsTree().Find(tempGlad);
        //get trainer for later
        Trainer* currTrainer = currGlad.GetTrainer();
        //increase level to use it in the next trees
        tempGlad.IncreaseLevel(currGlad.GetLevel());
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
            //std::cout << " Ha Ha " << std::endl;
        }
        //remove gladiator from trainer
        currTrainer->GetGladiatorsTree()->DeleteGladiator(tempGlad);
    }
    catch (TreeElementNotInTreeException&){
        throw FailureException();
    }
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
        Gladiator& currGlad = gladiators.GetGladiatorsTree().Find(tempGlad);
        tempGlad.IncreaseLevel(currGlad.GetLevel());
        //update gladiator level
        currGlad.IncreaseLevel(levelIncrease);
        //update glads by level
        tempGlad.SetFlag(true);
        //make a copy in order to change sort flag
        Gladiator newGlad = Gladiator(currGlad);
        newGlad.SetFlag(true);
        gladiatorsByLevel.DeleteGladiator(tempGlad);
        gladiatorsByLevel.AddGladiator(newGlad);
        //remove and inset from trainers tree
        currGlad.GetTrainer()->GetGladiatorsTree()->DeleteGladiator(tempGlad);
        currGlad.GetTrainer()->GetGladiatorsTree()->AddGladiator(newGlad);
    }
    catch (TreeElementNotInTreeException&){
        throw FailureException();
    }
}

GladiatorID ComodosDS::GetTopGladiator(TrainerID trainerID){
    if(trainerID == 0) throw InvalidInputException();
    if(gladiatorsByLevel.IsNull()) return -1;
    if(trainerID < 0){
        return gladiatorsByLevel.GetBestGladiatorId();
    }
    //search for trainer
    //create an instant of a trainer
    Trainer tempTrainer = Trainer(trainerID);
    //search in trainers tree
    try{
        //if not found, should throw exception
        Trainer& currTrainer = trainers.Find(tempTrainer);
        return currTrainer.GetGladiatorsTree()->GetBestGladiatorId();
    }
    catch (TreeElementNotInTreeException&){
        throw FailureException();
    };
}

GladByLevel* ComodosDS::GetAllGladiatorsByLevel(TrainerID trainerID){
    if(trainerID == 0) throw InvalidInputException();
    if(gladiatorsByLevel.IsNull()){
        GladByLevel* glad = new GladByLevel();
        return glad;
    }
    GladByLevel* gladByLevel = new GladByLevel();
    //get all glads
    if(trainerID<0){
        gladByLevel->SetNumOfGlads(this->gladiatorsByLevel.GetGladiatorsTree().size());
        this->gladiatorsByLevel.GetGladiatorsTree().InOrder(FuncWrapper_InOrder<Gladiator>(false, gladByLevel), true);
        return gladByLevel;
    }
    //get by trainer
    Trainer tempTrainer = Trainer(trainerID);
    try{
        Trainer& currTrainer = trainers.Find(tempTrainer);
        if(currTrainer.GetGladiatorsTree()->IsNull()){
            GladByLevel* glad = new GladByLevel();
            return glad;
        }
        gladByLevel->SetNumOfGlads(currTrainer.GetGladiatorsTree()->GetGladiatorsTree().size());
        currTrainer.GetGladiatorsTree()->GetGladiatorsTree().InOrder(FuncWrapper_InOrder<Gladiator>(false, gladByLevel), true);
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
        Gladiator testGlad = Gladiator(newGladID);
        try{
            gladiators.GetGladiatorsTree().Find(testGlad);
            throw FailureException();
        }
        catch (TreeElementNotInTreeException&){}

        Gladiator currGlad = gladiators.GetGladiatorsTree().Find(tempGlad);

        //creating the new gladiator
        Gladiator newGlad = Gladiator(newGladID, currGlad.GetTrainer(), currGlad.GetLevel());
        //delete glad from galdiators tree
        gladiators.GetGladiatorsTree().Delete(currGlad);
        gladiators.GetGladiatorsTree().Insert(newGlad);
        //update gladsByLevel
        //update the level in order to find the item in the tree
        tempGlad.SetFlag(true);
        tempGlad.IncreaseLevel(currGlad.GetLevel());
        newGlad.SetFlag(true);
        gladiatorsByLevel.DeleteGladiator(tempGlad);
        gladiatorsByLevel.AddGladiator(newGlad);
        //update the trainers tree
        Trainer* currTrainer = newGlad.GetTrainer();
        //delete the glad from its trainer
        currTrainer->GetGladiatorsTree()->DeleteGladiator(tempGlad);
        currTrainer->GetGladiatorsTree()->AddGladiator((newGlad));
    }
    catch (TreeElementNotInTreeException&){
        throw InvalidInputException();
    }catch (TreeElementAllreadyInTreeException&){
        throw FailureException();
    }

}

class UpdateTrainersLevel {
public:
    UpdateTrainersLevel(StimulantCode code, StimulantFactor factor) :
            stimulantCode(code), stimulantFactor(factor) {}

    void operator()(Trainer* trainer) {
        if(trainer->GetGladiatorsTree()->IsNull())
            return;
        trainer->GetGladiatorsTree()->UpdateLevels(stimulantCode, stimulantFactor);
    }

private:
    StimulantFactor stimulantFactor;
    StimulantCode stimulantCode;
};

void TrainerTree::InOrder(StimulantCode code, StimulantFactor factor){
    UpdateTrainersLevel update = UpdateTrainersLevel(code, factor);
    tree.InOrderP(update);
}
void ComodosDS::UpdateLevels(StimulantCode stimulantCode, StimulantFactor stimulantFactor){
    if(stimulantCode < 1 || stimulantFactor < 1) throw InvalidInputException();
    if(gladiators.IsNull()) return;
    gladiators.UpdateLevelsById(stimulantCode, stimulantFactor);
    gladiatorsByLevel.UpdateLevels(stimulantCode, stimulantFactor);
    trainers.InOrder(stimulantCode, stimulantFactor);
}

template <class T>
void GladiatorTree<T>::UpdateLevels(StimulantCode stimulantCode, StimulantFactor stimulantFactor){
    //creating the function class
    UpdateLevelsClass updateLevels = UpdateLevelsClass(stimulantCode, stimulantFactor);

    //create a class for the inOrder traversal - OK
    SplitAndSortTree<Gladiator,UpdateLevelsClass> sortTree =
            SplitAndSortTree<Gladiator,UpdateLevelsClass>(updateLevels, tree.size());
    //do inOrder traversal to create the two arrays - OK
    tree.InOrder(T(true, &sortTree));

    //alternative: added to splay tree a constructor by array.
    tree.CreateSplayTreeFromArray(sortTree.merge(), tree.size());
}

template <class T>
void GladiatorTree<T>::UpdateLevelsById(StimulantCode stimulantCode, StimulantFactor stimulantFactor){
       UpdateGladLevel updateGladLevel = UpdateGladLevel(true , NULL, stimulantCode, stimulantFactor);
    SplitAndSortTree<Gladiator, UpdateGladLevel> sortTree =
            SplitAndSortTree<Gladiator, UpdateGladLevel>(updateGladLevel, tree.size());
    tree.InOrder(updateGladLevel);
}

template <class T>
GladiatorTree<T>::GladiatorTree() : tree(SplayTreeWrapper<Gladiator,T>()), bestGladiator(Gladiator(-1)){}

template <class T>
void GladiatorTree<T>::UpdateBestGladiator(Gladiator& gladiator){
    bestGladiator = Gladiator(gladiator);
}

template <class T>
void GladiatorTree<T>::AddGladiator(Gladiator& gladiator) {
    tree.Insert(gladiator);
    //if is better
    if(gladiator.GetLevel() > bestGladiator.GetLevel() || (gladiator.GetLevel() == bestGladiator.GetLevel() &&
            gladiator.GetGladiatorID() < bestGladiator.GetGladiatorID())){
        bestGladiator = Gladiator(gladiator);
    }
}

template <class T>
void GladiatorTree<T>::DeleteGladiator(Gladiator& gladiator){
    tree.Delete(gladiator);
    if(gladiator.GetGladiatorID() == bestGladiator.GetGladiatorID()){
        Gladiator* newBest = tree.GetMaxElement();
        bestGladiator = (newBest == NULL) ? Gladiator(-1) : Gladiator(*newBest);
    }
}

template <class T>
SplayTreeWrapper<Gladiator,T>& GladiatorTree<T>::GetGladiatorsTree(){
    return tree;
}

