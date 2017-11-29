//
// Created by Nevo Agmon on 29/11/2017.
//

#include "SplayTree.h"
#include <iostream>

int main(){
    SplayTreeWrapper<int> tree;
    for(int i=0; i<4; i++){
        tree.Insert(i);
    }
    std::cout<<tree.getRootData();
    return 0;
}