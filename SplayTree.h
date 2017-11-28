
#ifndef EX1_SPLAYTREE_H
#define EX1_SPLAYTREE_H

#include "utility.h"


/************************************************************************

 NOTE: the element T must support the following:
        copy Constructor
        operators overloading: ==, <, >


 ************************************************************************/



template <class T>
class SplayTree {

public:

    /**
    * no data constructor
    * @tparam T
    */
    SplayTree();

    /**
    * constructor with data initiation.
    * @tparam T
    * @param data
    */
    explicit SplayTree(T&);

    /**
    * destructor deletes data and deletes each subtree recursively.
    * @tparam T
    */
    ~SplayTree();

    /**
    * insert to the tree, compares data to the data stored in the tree
    * and places the data in the right place.
    * to use this function the element <T> must support <,> operators.
    * @tparam T
    * @param newData
    */
    void Insert(T&);


    void Delete(T&);
    T& Find(T&);

private:

    SplayTree *left;
    SplayTree *right;
    T* data;

    enum ParentWas {left, right, root};

    void Splay(T&, ParentWas, ParentWas);
    void Split();
    void Join();

};

class TreeInvalidInputException : InvalidInputException {};
class TreeFailureException : FailureException {};
class TreeElementAllreadyInTreeException : exception{};
class TreeElementNotInTreeException : exception{};

#endif //EX1_SPLAYTREE_H
