
#ifndef EX1_SPLAYTREE_H
#define EX1_SPLAYTREE_H

#include "utility.h"

/************************************************************************

 NOTE: the element T must support the following:
        copy Constructor
        operators overloading: ==, <, >

 ************************************************************************/
template <class T,class Func>
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

    SplayTree(T** array, int start, int end);

    /**
    * destructor deletes data and deletes each subtree recursively.
    * @tparam T
    */
    ~SplayTree();

    T& getRootData();
    T* getRootDataPointer();

    SplayTree* GetLeft(){ return left; }

    void SetLeft(SplayTree* splayTree = NULL){ left = splayTree;}

    SplayTree* GetRight(){ return right;}

    void SetRight(SplayTree* splayTree = NULL){ right = splayTree;}
    ///generic function for tree traversal.

    /**
    * traversal functions for tree.
    * @tparam T
    * @param f
    */
    void InOrder(Func f, bool reverse = false);
    void InOrderP(Func f, bool reverse = false);
    void PreOrder(Func f);
    void PostOrder(Func f);

private:

    SplayTree *left;
    SplayTree *right;
    T* data;

    SplayTree* recConstructor(T** array, int start, int end,
                              SplayTree* tree);
};

template <class T,class Func>
void InnerDelete(T& data, SplayTree<T, Func>* root);
template <class T,class Func>
T& InnerFind(T& data, SplayTree<T, Func>* root);

/**
 * insert element to the tree, the elemnt will be at the root.
 * @tparam T
 * @param newData
 * @param root
 */
template <class T,class Func>
void InnerInsert(T& newData, SplayTree<T, Func>* root);

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
template <class T,class Func>
SplayTree<T, Func>* Splay(T& itemToFind, SplayTree<T, Func>* root);

/**
 * helper function for right Rotation (is used after left step).
 * @tparam T
 * @param x
 * @return
 */
template <class T,class Func>
SplayTree<T, Func>* RotateRight(SplayTree<T, Func>*);

/**
 * helper function for left Rotation (is used after right step).
 * @tparam T
 * @param x
 * @return
 */
template <class T,class Func>
SplayTree<T, Func>* RotateLeft(SplayTree<T, Func>*);

/**
 * function to get max element of a tree.
 * @tparam T
 * @param root
 * @return
 */
template <class T,class Func>
T* getMaxElement(SplayTree<T, Func>* root);


/*************************************************************************
 * this class wraps the splay tree in order to make all tree operations
 * appear as methods.
 * the usage of the tree shuld be only with the wrapper.
 ************************************************************************/
template <class T,class Func>
class SplayTreeWrapper{

public:

    SplayTreeWrapper() : numOfItems(0), tree(NULL) { }

    virtual ~SplayTreeWrapper(){ delete tree; }

    void CreateSplayTreeFromArray(T** arr, int size){
        SplayTree<T, Func>* temp = tree;
        tree = new SplayTree<T, Func>(arr, 0,size -1);
        delete temp;
    }

    T& getRootData(){ return tree->getRootData(); };

    T& Find(T& data){
        return InnerFind(data, &tree);
    };

    void Insert(T& newData){
        if(tree == NULL) {
            tree = new SplayTree<T, Func>(newData);
            numOfItems = 0;
        }
        else InnerInsert(newData, &tree);
        numOfItems++;
    };

    void Delete(T& data){
        if(tree == NULL) return;
        InnerDelete(data, tree, *this);
        numOfItems--;
    };

    int size(){ return numOfItems; }

    T* GetMaxElement(){ return getMaxElement(tree); }

    void InOrder(Func f, bool reverse = false){
        tree->InOrder(f, reverse);
    }

    void InOrderP(Func f, bool reverse = false){
        tree->InOrderP(f, reverse);
    }
    void PreOrder(Func f){
        tree->PreOrder(f);
    }

    void PostOrder(Func f){
        tree->PostOrder(f);
    }

    void SetData(T& t){
        *(tree->getRootDataPointer()) = t;
    }
    void SetLeft(SplayTreeWrapper* t){
        tree->SetLeft(t->tree);
    }

    void SetRight(T& t){
        tree->SetRight(t);
    }
    SplayTree<T,Func>* GetTree(){
        return tree;
    }
    void SetTree(SplayTree<T,Func>* splayTree = NULL){
        //if(splayTree == NULL){
        //    delete tree;
        //}
        tree = splayTree;
    }
    SplayTreeWrapper(T** array, int size);

private:
    SplayTree<T,Func>* tree;
    int numOfItems;

};

/**
 * Tree Exceptions.
 */
class TreeInvalidInputException : InvalidInputException {};
class TreeFailureException : FailureException {};
class TreeElementAllreadyInTreeException : exception{};
class TreeElementNotInTreeException : exception{};



/************************************************************************

 NOTE: the element T must support the following:
        copy Constructor
        operators overloading: ==, <, >


 ************************************************************************/

/**
 * no data constructor
 * @tparam T
 */
template <class T,class Func>
SplayTree<T, Func>::SplayTree() : left(NULL), right(NULL), data(NULL) {}

/**
 * constructor with data initiation.
 * @tparam T
 * @param data
 */
template <class T,class Func>
SplayTree<T, Func>::SplayTree(T& data, SplayTree<T, Func>* left, SplayTree<T, Func>* right) :
        left(left), right(right), data(new T(data)) {}

/**
 * destructor deletes data and deletes each subtree recursively.
 * @tparam T
 */
template <class T,class Func>
SplayTree<T, Func>::~SplayTree(){
    if(data != NULL) delete data;
    delete left;
    delete right;
}

template <class T,class Func>
SplayTree<T, Func>::SplayTree(T** array, int start, int end) :
        data(NULL), left(NULL), right(NULL) {
    recConstructor(array, start, end, this);
}

template <class T,class Func>
SplayTree<T, Func>* SplayTree<T, Func>::recConstructor(T** array, int start, int end,
                                                       SplayTree<T, Func>* tree){
    int mid = (start+end)/2;
    tree->data = new T(*array[mid]);
    tree->left = (start > mid-1) ? NULL : new SplayTree<T, Func>(array, start, mid-1);
    tree->right = (mid+1 > end) ? NULL :new SplayTree<T, Func>(array, mid+1, end);
    return tree;
}

template <class T,class Func>
T& SplayTree<T, Func>::getRootData() {
    return *(this->data);
}

template <class T,class Func>
T* SplayTree<T, Func>::getRootDataPointer() {
    return this->data;
}

template <class T,class Func>
T& InnerFind(T& data, SplayTree<T, Func>** root){
    *root = Splay(data, *root);
    if((*root)->getRootData() == data){
        return (*root)->getRootData();
    }else{
        throw TreeElementNotInTreeException();
    }
}

/**
 * insert element to the tree, the elemnt will be at the root.
 * @tparam T
 * @param newData
 * @param root
 */
template <class T,class Func>
void InnerInsert(T& newData, SplayTree<T, Func>** root) {
    *root = Splay(newData, *root);
    if((*root)->getRootData() == newData)
        throw TreeElementAllreadyInTreeException();
    else if((*root)->getRootData() > newData){
        *root = new SplayTree<T, Func>(newData, (*root)->GetLeft(), *root);
        (*root)->GetRight()->SetLeft();
    }else{
        *root = new SplayTree<T, Func>(newData, *root, (*root)->GetRight());
        (*root)->GetLeft()->SetRight();
    }
}

template <class T,class Func>
void InnerDelete(T& data, SplayTree<T, Func>* root, SplayTreeWrapper<T, Func>& wrapper){
    root = Splay(data, root);
    if(root->getRootData() == data){
        delete root->getRootDataPointer();
        T* maxElementInLeft = getMaxElement(root->GetLeft());
        SplayTree<T, Func>* right = root->GetRight();
        SplayTree<T, Func>* left = root->GetLeft();
        if(right == NULL && left == NULL){
            //delete root;
            wrapper.SetTree();
        }
            //if only the left subTree
        else if(right == NULL && left != NULL){
            //delete root;
            wrapper.SetTree(left);
            //if only right subTree
        } else if(left == NULL && right != NULL){
            //delete root;
            wrapper.SetTree(right);
        } else{
            *wrapper.GetTree() = *(Splay(*maxElementInLeft, root->GetLeft()));
            wrapper.GetTree()->SetRight(right);
        }
        //root->SetLeft(Splay(*maxElementInLeft, root->GetLeft()));
        //root->SetRight(right);
    }else
        throw TreeElementNotInTreeException();
}

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
template <class T,class Func>
SplayTree<T, Func>* Splay(T& itemToFind, SplayTree<T, Func>* root){
    ///stop condition - root is null or holds the item.
    if(root == NULL || root->getRootData() == itemToFind) return root;

    ///check if item is in the left subTree.
    if(root->getRootData() > itemToFind){
        if(root->GetLeft() == NULL) return root;
        if(root->GetLeft()->getRootData() > itemToFind){ ///left->left
            root->GetLeft()->SetLeft(Splay(itemToFind, root->GetLeft()->GetLeft()));
            root = RotateRight(root);
        }else if(root->getRootData() < itemToFind){ ///left->right
            root->GetLeft()->SetRight(Splay(itemToFind, root->GetLeft()->GetRight()));
            if(root->GetLeft()->GetRight() != NULL){
                root->SetLeft(RotateLeft(root->GetLeft()));
            }
        }
        return (root->GetLeft() == NULL)? root : RotateRight(root); //was RotateRight(root->GetLeft()
    }else{ //item is in the right subTree.
        if(root->GetRight() == NULL) return root;
        if(root->GetRight()->getRootData() > itemToFind){ ///right->left
            root->GetRight()->SetLeft(Splay(itemToFind, root->GetRight()->GetLeft()));
            if(root->GetRight()->GetLeft() != NULL){
                root->SetRight(RotateRight(root->GetRight()));
            }
        } else if(root->GetRight()->getRootData() < itemToFind){ ///right->right
            root->GetRight()->SetRight(Splay(itemToFind, root->GetRight()->GetRight()));
            root = RotateLeft(root);
        }
        return (root->GetRight() == NULL)? root : RotateLeft(root);
    }
}

/**
 * helper function for right Rotation (is used after left step).
 * @tparam T
 * @param x
 * @return
 */
template <class T,class Func>
SplayTree<T, Func>* RotateRight(SplayTree<T, Func>* x){
    SplayTree<T, Func>* y = x->GetLeft();
    x->SetLeft(y->GetRight());
    y->SetRight(x);
    return y;
}

/**
 * helper function for left Rotation (is used after right step).
 * @tparam T
 * @param x
 * @return
 */
template <class T,class Func>
SplayTree<T, Func>* RotateLeft(SplayTree<T, Func>* x){
    SplayTree<T, Func>* y = x->GetRight();
    x->SetRight(y->GetLeft());
    y->SetLeft(x);
    return y;
}

/**
 * function to get max element of a tree.
 * @tparam T
 * @param root
 * @return
 */
template <class T,class Func>
T* getMaxElement(SplayTree<T, Func>* root){
    if(root == NULL) return NULL;
    if(root->GetRight() == NULL){
        return root->getRootDataPointer();
    }else{
        return getMaxElement(root->GetRight());
    }
}

/**
 * traversal functions for tree.
 * @tparam T
 * @param f
 */
template <class T,class Func>
void SplayTree<T, Func>::InOrder(Func f, bool reverse) {
    if (reverse) {
        if (this->right != NULL) this->right->InOrder(f, reverse);
        f(*(this->data));
        if (this->left != NULL) this->left->InOrder(f, reverse);
    } else {
        if (this->left != NULL) this->left->InOrder(f, reverse);
        f(*(this->data));
        if (this->right != NULL) this->right->InOrder(f, reverse);
    }
}

template <class T,class Func>
void SplayTree<T, Func>::InOrderP(Func f, bool reverse) {
    if (reverse) {
        if (this->right != NULL) this->right->InOrderP(f, reverse);
        f((this->data));
        if (this->left != NULL) this->left->InOrderP(f, reverse);
    } else {
        if (this->left != NULL) this->left->InOrderP(f, reverse);
        f((this->data));
        if (this->right != NULL) this->right->InOrderP(f, reverse);
    }
}

template <class T,class Func>
void SplayTree<T, Func>::PreOrder(Func f){
    f(this->data);
    if(this->left != NULL) this->left->InOrder(f);
    if(this->right != NULL) this->right->InOrder(f);
}

template <class T,class Func>
void SplayTree<T, Func>::PostOrder(Func f){
    if(this->left != NULL) this->left->InOrder(f);
    if(this->right != NULL) this->right->InOrder(f);
    f(this->data);
}

#endif //EX1_SPLAYTREE_H
 