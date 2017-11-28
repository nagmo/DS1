
#include "SplayTree.h"

/************************************************************************

 NOTE: the element T must support the following:
        copy Constructor
        operators overloading: ==, <, >


 ************************************************************************/

/**
 * no data constructor
 * @tparam T
 */
template <class T>
SplayTree<T>::SplayTree() : left(nullptr), right(nullptr), data(nullptr) {}

/**
 * constructor with data initiation.
 * @tparam T
 * @param data
 */
template <class T>
SplayTree<T>::SplayTree(T& data) : left(nullptr), right(nullptr), data(
        nullptr) {
    this->data = new T(data);
}

/**
 * destructor deletes data and deletes each subtree recursively.
 * @tparam T
 */
template <class T>
SplayTree<T>::~SplayTree(){
    delete data;
    delete left;
    delete right;
}

/**
 * insert to the tree, compares data to the data stored in the tree
 * and places the data in the right place.
 * to use this function the element <T> must support <,> operators.
 * @tparam T
 * @param newData
 */
template <class T>
void SplayTree<T>::Insert(T& newData) {
    if(data < newData){
        if(left == nullptr) {
            left = new SplayTree(newData);
        }
        else {
            left->Insert(newData);
        }
    }else if(data > newData){
        if(right == nullptr) {
            left = new SplayTree(newData);
        }
        else {
            right->Insert(newData);
        }
    }else{
        throw TreeElementAllreadyInTreeException();
    }
}

template <class T>
T& SplayTree<T>::Find(T& itemToFind){

}

/**
 * recursive method to splay the tree based on the value given.
 * searches the item and splaying on the path,
 * if the item was found it will be at the root at the end,
 * if not it's father will be at the root
 * (the user must check at the end of the method).
 * @tparam T
 * @param itemToFind
 * @param father
 * @param grendpa
 */
template <class T>
void SplayTree<T>::Splay(T& itemToFind, ParentWas father,
                         ParentWas grendpa){
    //stop condition: if the item was found or
    // there are no node to proceed.
    if(this->data == itemToFind){
        //rotate
        return;
    }else if(this->data < itemToFind && this->right == nullptr){
        //rotate
        return;
    }else if(this->data > itemToFind && this->left == nullptr){
        //rotate
        return;
    }
    //recursively splay to the subtree needed.
    if(this->data < itemToFind){
        this->right->Splay(itemToFind, right, father);
    }else{
        this->left->Splay(itemToFind, left, father);
    }
    //rotate
}





