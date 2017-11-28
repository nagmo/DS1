
#ifndef EX1_SPLAYTREE_H
#define EX1_SPLAYTREE_H

template <class T>
class SplayTree {

public:

    /**
     * empty tree constructor, puts null  in root.
     */
    SplayTree();

    /**
     * constructor must receive data for root.
     * type T must support a construction by reference (Copy constructor)
     * for example:
     *      new T(T&)
     *
     * must be supported!!
     */
    explicit SplayTree(T&);

    /**
     * destructor
     */
    ~SplayTree();

    /**
     *
     */
    void Insert(T&);
    void Delete(T&);
    T& Find(T&);

private:

    SplayTree* left;
    SplayTree* right;
    T* data;

    void Splay();
    void Split();
    void Join();

};


#endif //EX1_SPLAYTREE_H
