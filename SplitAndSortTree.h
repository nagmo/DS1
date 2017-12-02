
#ifndef EX1_SPLITANDSORTTREE_H
#define EX1_SPLITANDSORTTREE_H

/*************************************************************************
 * A generic class to split, sort and merge a tree based on a boolean function.
 * @tparam T - the data type that is stored inside the tree.
 *
 * NOTES:
 *      1)  if additional data is needed the BoolFunc can be a class with
 *          operator() overloaded for the calculation.
 *      2)  the construction of the class should NOT be inside the call
 *          to the tree traversal in order to create a tree afterwards.
 *          --> see merge desctiption.
 *      3)  the class cant create the new tree since the data type it gets
 *          isn't necessarily the same as the tree's data type.
 ************************************************************************/

template <class T>
class SplitAndSortTree{
public:
    typedef bool (*BoolFunc)(T&);

    /**
     * @param f - Boolean function for calculation.
     * @param size - size of the tree for array allocation.
     */
    SplitAndSortTree(BoolFunc f, int size) :
            func(f), trueArray(NULL), falseArray(NULL),
            mergedArray(NULL), iTrue(0), iFalse(0), size(size) {
        trueArray = new T*[size];
        falseArray = new T*[size];
        mergedArray = new T*[size];
    };

    /**
     * Destructor - note that the merged array is not deleted!!
     * it is the responsibility of the caller to free it.
     */
    ~SplitAndSortTree(){
        delete[] trueArray;
        delete[] falseArray;
        delete[] mergedArray;
    }

    /**
     * the function that devides the tree into two arrays.
     * @param data
     */
    void operator()(T& data){
        if(func(data)) trueArray[iTrue++] = *data;
        else falseArray[iFalse++] = *data;
    }

    /**
     * should be called after the tree traversal is finished.
     * returns a sorted array of pointers to the data in the tree.
     * caller must handel freeing of the data in the array after
     * creating the new tree.
     * @return
     */
    T** merge(){
        int iMerge = 0, iT = 0, iF = 0;
        for(;iT < iTrue && iF < iFalse; iMerge++){
            if(*trueArray[iT] < *falseArray[iF]){
                mergedArray[iMerge] = trueArray[iT++];
            }else{
                mergedArray[iMerge] = falseArray[iF++];
            }
        }
        while(iT < iTrue){ mergedArray[iMerge++] = trueArray[iT++];}
        while(iF < iFalse){ mergedArray[iMerge++] = falseArray[iF++];}
        return mergedArray;
    }

private:
    BoolFunc func;
    T* *trueArray;
    T* *falseArray;
    T* *mergedArray;
    int iTrue, iFalse, size;
};
#endif //EX1_SPLITANDSORTTREE_H
