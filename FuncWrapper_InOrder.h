
#ifndef EX1_FUNCWRAPPER_INORDER_H
#define EX1_FUNCWRAPPER_INORDER_H

#include "SplitAndSortTree.h"
#include "GladByID.h"
#include "Trainer.h"


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

template <class T>
class FuncWrapper_InOrder{
public:
    FuncWrapper_InOrder(bool flag, void* pointer=NULL):
    flag(flag), splitAndSortTree(NULL), gladByLevel(NULL){
        if(flag) splitAndSortTree = (SplitAndSortTree<T, UpdateLevelsClass>*)pointer;
        else gladByLevel = (GladByLevel*)pointer;
    }
    void operator()(T& t){
        if(flag) (*splitAndSortTree)(t);
        else (*gladByLevel)(t);
    }

private:
    bool flag;
    SplitAndSortTree<T, UpdateLevelsClass>* splitAndSortTree;
    GladByLevel* gladByLevel;
};


#endif //EX1_FUNCWRAPPER_INORDER_H
