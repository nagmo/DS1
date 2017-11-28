
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
    void DeleteSubTree();

};


#endif //EX1_SPLAYTREE_H
