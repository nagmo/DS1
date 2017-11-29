//
// Created by yshildan on 11/29/2017.
//

#ifndef EX1_NODEWRAPPER_H
#define EX1_NODEWRAPPER_H

#include "utility.h"

template <class T>
class NodeWrapper{
public:
    NodeWrapper(T&);
    T data;
private:
    GladiatorID bestGladiator;
};


#endif //EX1_NODEWRAPPER_H
