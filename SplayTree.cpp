
#include "SplayTree.h"

template <class T>
SplayTree<T>::SplayTree() : left(nullptr), right(nullptr), data(nullptr) {}

template <class T>
SplayTree<T>::SplayTree(T& data) : left(nullptr), right(nullptr), data(
        nullptr) {}

template <class T>
SplayTree<T>::~SplayTree(){
    delete data;
}




