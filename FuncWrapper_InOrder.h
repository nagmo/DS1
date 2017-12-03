
#ifndef EX1_FUNCWRAPPER_INORDER_H
#define EX1_FUNCWRAPPER_INORDER_H

#include "SplitAndSortTree.h"
#include "GladByID.h"

template <class T>
class FuncWrapper_InOrder{
public:
    FuncWrapper_InOrder(bool flag, void* pointer=NULL):
    flag(flag), splitAndSortTree(NULL), gladByLevel(NULL){
        if(flag) splitAndSortTree = (SplitAndSortTree<T>*)pointer;
        else gladByLevel = (GladByLevel*)pointer;
    }
    void operator()(T& t){
        if(flag) (*splitAndSortTree)(t);
        else (*gladByLevel)(t);
    }

private:
    bool flag;
    SplitAndSortTree<T>* splitAndSortTree;
    GladByLevel* gladByLevel;
};
#endif //EX1_FUNCWRAPPER_INORDER_H
