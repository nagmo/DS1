
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
SplayTree<T>::SplayTree(T& data, SplayTree<T>* left = nullptr,
                        SplayTree<T>* right = nullptr) :
        left(left), right(right), data(nullptr) {
    this->data = new T(data);
}

/**
 * constructor with data initiation.
 * @tparam T
 * @param data
 */
template <class T>
SplayTree<T>::SplayTree(T& data) :
        left(nullptr), right(nullptr), data(nullptr) {
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

template <class T>
T& SplayTree::getRootData() {
    return this->data;
}

template <class T>
T& Find(T& data, SplayTree<T>* root){
    root = Splay(data, root);
    if(root->data == data){
        return root->data;
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
template <class T>
void Insert(T& newData, SplayTree<T>* root) {
    root = Splay(newData, root);
    if(root->data == newData)
        throw TreeElementAllreadyInTreeException();
    else if(root->data > newData){
        root = new SplayTree<T>(newData, root->left, root);
        root->right->left = nullptr;
    }else{
        root = new SplayTree<T>(newData, root, root->right);
        root->left->right = nullptr;
    }
}

template <class T>
friend void Delete(T& data, SplayTree<T>* root){
    root = Splay(data, root);
    if(root->data == data){
        delete root->data;
        T& maxElementInLeft = getMaxElement(root->left);
        SplayTree<T>* right = root->right;
        root->left = Splay(maxElementInLeft, root->left);
        root->right = right;
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
template <class T>
SplayTree<T>* Splay(T& itemToFind, SplayTree<T>* root){
    ///stop condition - root is null or holds the item.
    if(root == nullptr || root->data == itemToFind) return root;

    ///check if item is in the left subTree.
    if(root->data > itemToFind){
        if(root->left == nullptr) return root;
        if(root->left->data > itemToFind){ ///left->left
            root->left->left = Splay(itemToFind, root->left->left);
            root = RotateRight(root);
        }else if(root->data < itemToFind){ ///left->right
            root->left->right = Splay(itemToFind, root->left->right);
            if(root->left->right != nullptr){
                root->left= RotateLeft(root->left);
            }
        }
        return (root->left == nullptr)? root : RotateRight(root->left);
    }else{ //item is in the right subTree.
        if(root->right == nullptr) return root;
        if(root->right->data > itemToFind){ ///right->left
            root->right->left = Splay(itemToFind, root->right->left);
            if(root->right->left != nullptr){
                root->right = RotateLeft(root->right);
            }
        } else if(root->right->data < itemToFind){ ///right->right
            root->right->right = Splay(itemToFind, root->right->right);
            root = RotateLeft(root);
        }
        return (root->right == nullptr)? root : RotateLeft(root);
    }
}

/**
 * helper function for right Rotation (is used after left step).
 * @tparam T
 * @param x
 * @return
 */
template <class T>
SplayTree<T>* RotateRight(SplayTree<T>* x){
    SplayTree<T>* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

/**
 * helper function for left Rotation (is used after right step).
 * @tparam T
 * @param x
 * @return
 */
template <class T>
SplayTree<T>* RotateLeft(SplayTree<T>* x){
    SplayTree<T>* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

/**
 * function to get max element of a tree.
 * @tparam T
 * @param root
 * @return
 */
template <class T>
friend T& getMaxElement(SplayTree<T>* root){
    if(root->right == nullptr){
        return root->data;
    }else{
        return getMaxElement(root->right);
    }
}
