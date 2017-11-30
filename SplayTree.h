
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
    * constructor with data initiation.
    * @tparam T
    * @param data
    */
    explicit SplayTree(T&, SplayTree* left = NULL,
                       SplayTree* right= NULL);
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

    T& getRootData();

    SplayTree* GetLeft(){ return left; }

    void SetLeft(SplayTree* splayTree = NULL){ left = splayTree;}

    SplayTree* GetRight(){ return right;}

    void SetRight(SplayTree* splayTree = NULL){ right = splayTree;}
    ///generic function for tree traversal.
    typedef void (*Func)(T&);

    /**
    * traversal functions for tree.
    * @tparam T
    * @param f
    */
    void InOrder(Func f, bool reverse = false);
    void PreOrder(Func f);
    void PostOrder(Func f);

private:

    SplayTree *left;
    SplayTree *right;
    T* data;
};

template <class T>
void InnerDelete(T& data, SplayTree<T>* root);
template <class T>
T& InnerFind(T& data, SplayTree<T>* root);

/**
 * insert element to the tree, the elemnt will be at the root.
 * @tparam T
 * @param newData
 * @param root
 */
template <class T>
void InnerInsert(T& newData, SplayTree<T>* root);

/**
 * function to splay tree. will be used in find, insert, delete.
 * rotates the tree so the item searched will be at the root if
 * it is in the tree, if it isn't it's parent will be at the root.
 *
 * NOTE: for this function the type T must support <,> operators.
 *
 * @tparam T
 * @param itemToFind
 * @param root
 * @return - the root of the splayed tree.
 */
template <class T>
SplayTree<T>* Splay(T& itemToFind, SplayTree<T>* root);

/**
 * helper function for right Rotation (is used after left step).
 * @tparam T
 * @param x
 * @return
 */
template <class T>
SplayTree<T>* RotateRight(SplayTree<T>* root);

/**
 * helper function for left Rotation (is used after right step).
 * @tparam T
 * @param x
 * @return
 */
template <class T>
SplayTree<T>* RotateLeft(SplayTree<T>* root);

/**
 * function to get max element of a tree.
 * @tparam T
 * @param root
 * @return
 */
template <class T>
T& getMaxElement(SplayTree<T>* root);


/*************************************************************************
 * this class wraps the splay tree in order to make all tree operations
 * appear as methods.
 * the usage of the tree shuld be only with the wrapper.
 ************************************************************************/
template <class T>
class SplayTreeWrapper{

public:

    SplayTreeWrapper() : numOfItems(0){ tree = new SplayTree<T>(); }

    ~SplayTreeWrapper(){ delete tree; }

    T& getRootData(){ return tree->getRootData(); };

    T& Find(T& data){ return InnerFind(data, tree); };

    void Insert(T& newData){
        InnerInsert(newData, tree);
        numOfItems++;
    };

    void Delete(T& data){
        InnerDelete(data, tree);
        numOfItems--;
    };

    int size(){ return numOfItems; }

    T& GetMaxElement(){ return getMaxElement(tree); }

    typedef void (*Func)(T&);

    void InOrder(Func f, bool reverse = false){
        tree->InOrder(f, reverse);
    }

    void PreOrder(Func f){
        tree->PreOrder(f);
    }

    void PostOrder(Func f){
        tree->PostOrder(f);
    }

private:
    SplayTree<T>* tree;
    int numOfItems;
};

/**
 * Tree Exceptions.
 */
class TreeInvalidInputException : InvalidInputException {};
class TreeFailureException : FailureException {};
class TreeElementAllreadyInTreeException : exception{};
class TreeElementNotInTreeException : exception{};

#endif //EX1_SPLAYTREE_H
