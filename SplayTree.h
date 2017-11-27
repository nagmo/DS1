
#ifndef EX1_SPLAYTREE_H
#define EX1_SPLAYTREE_H

template <class T>
class SplayTree {

public:

    SplayTree();
    ~SplayTree();
    void Insert(T&);
    void Delete(T&);
    T& Find(T&);

private:

    SplayTree* left;
    SplayTree* right;
    T& data;

    void Splay();
    void Split();
    void Join();

};


#endif //EX1_SPLAYTREE_H
