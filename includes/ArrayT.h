//
// Created by Saman Seifi Ph.D. on 5/11/21.
//

#ifndef SIMPLEBEAM_ARRAYT_H
#define SIMPLEBEAM_ARRAYT_H

#include "Environment.h"

#include <vector>

using namespace std;

template <class TYPE>
class ArrayT {

protected:
    int fLength;    /**< logical size (length) of the array */

    TYPE *fArray;   /**< the main data container */

public:
    // constructors
    // Default */
    /*@{*/
    ArrayT();

    /** Constructor with given array Length */
    explicit ArrayT(int length);

    /** Constructor with a given STL array */
    explicit ArrayT(const TYPE *ptrArray);

    /** Copy constructor with a given ArrayT type */
    ArrayT(const ArrayT& source);
    /*@}*/

    /* Deconstruct */
    ~ArrayT();

    /* Set the dimension */
    virtual void Dimension(int length);

    /* Returning the Length */
    int Length() const;

    /** Operators */
    /* Access/Allocation operator */
    /*@{*/
    TYPE& operator[](int index);
    const TYPE& operator[](int index) const;
    /*@}*/

    /** Assignment operators */
    /*@{*/
    /** Set all elements in the array to the given value */
    virtual ArrayT<TYPE>& operator=(const TYPE& valueRHS);
    virtual ArrayT<TYPE>& operator=(const TYPE* ptrRHS);
    ArrayT<TYPE>& operator=(const ArrayT<TYPE>& arrRHS);
    /*@}*/

    /**
     * \name return a pointer specified element in the array
     * offset must be 0 <= offset <= Length() <--- one beyond the end! */
    /*@{*/
    TYPE* Pointer(int offset = 0);
    const TYPE* Pointer(int offset = 0) const;
    /*@}*/

    /* Set the field */
    void Alias(int length, const TYPE* ptrArray);

    /* Removing the element from the vector and resize */
    void Remove(int row_num);

    /* Inserting new element to the vector  */
    void Insert(TYPE value);

};

/* Constructors */
template <class TYPE>
inline ArrayT<TYPE>::ArrayT():
    fLength(0),
    fArray(NULL)
{

}

template <class TYPE>
inline ArrayT<TYPE>::ArrayT(int length):
    fLength(0),
    fArray(NULL)
{
    Dimension(length);
}

template <class TYPE>
inline ArrayT<TYPE>::ArrayT(const TYPE* ptrArray):
    fLength(0),
    fArray(NULL)
{
    /* First finding the length of given array */
    int arrayLength = (sizeof(*ptrArray) / sizeof(ptrArray)) + 1;    // proper way of getting the length of an array

    Alias(arrayLength, ptrArray);
}

template<class TYPE>
inline ArrayT<TYPE>::ArrayT(const ArrayT &source):
    fLength(0),
    fArray(NULL)
{
    operator=(source);
}

/* Destructor */
template <class TYPE>
inline ArrayT<TYPE>::~ArrayT() {

    delete[] fArray;

    fArray = NULL;
    fLength = 0;
}

template <class TYPE>
inline void ArrayT<TYPE>::Remove(int row_num) {

    /* First check if the row exist */
    assert (row_num < fLength);

    /* Reduce the size */
    fLength -= 1;

    /* Copying over the data by memory */
    TYPE *ptrTemp_ = new TYPE[fLength];
    for (int i = 0; i < row_num-1; i++) {
        ptrTemp_[i]= fArray[i];
    }

    /* jump over the removed row */
    for (int j = row_num; j < fLength; j++){
        ptrTemp_[j-1] = fArray[j];
    }

    /* replace the array */
    delete[] fArray;
    fArray = ptrTemp_;
}

template <class TYPE>
inline void ArrayT<TYPE>::Insert(TYPE value) {

    /* Copy the elements temporary to a temp array */
    TYPE *ptrTemp_ = new TYPE[fLength + 1];

    for (int i = 0; i < fLength; i++) {
        ptrTemp_[i] = fArray[i];
    }

    /* Insert the final spot */
    ptrTemp_[fLength] = value;

    delete[] fArray;

    fArray = ptrTemp_;
    fLength += 1;
}

/** Operators */
/* element accessor */
template <class TYPE>
inline TYPE &ArrayT<TYPE>::operator[](int index) {

    /* Simple range check */
    assert(index < fLength || index >= fLength);

    return fArray[index];
}
template <class TYPE>
inline const TYPE& ArrayT<TYPE>::operator[](int index) const {

    /* Simple range check */
    assert(index < fLength || index >= fLength);

    return fArray[index];
}

/* Assignments operators */
template<class TYPE>
inline ArrayT<TYPE>& ArrayT<TYPE>::operator=(const TYPE& valueRHS) {

    TYPE* p = fArray;
    for (int i = 0; i < fLength; i++)
        *p++ = valueRHS;

    return *this;
}

template<class TYPE>
inline ArrayT<TYPE>& ArrayT<TYPE>::operator=(const TYPE* ptrRHS) {

    /* Getting the size of the STL array */
    int arrayLength = (sizeof(*ptrRHS) / sizeof(ptrRHS)) + 1;

    /* if the dimensions are not match delete the LHS and create the ArrayT of the RHS size */
    if (fLength != arrayLength) Dimension(arrayLength);

    /* assign element-by-element */
    for (int i = 0; i < fLength; i++) {
        fArray[i] = ptrRHS[i];
    }

    return *this;
}

template<class TYPE>
inline ArrayT<TYPE>& ArrayT<TYPE>::operator=(const ArrayT<TYPE>& arrRHS) {

    if (fArray != arrRHS.fArray) {

        /* Check the lengths of both arrays */
        if (fLength != arrRHS.fLength) Dimension(arrRHS.fLength);

        /* copying over by value */
        for (int i = 0; i < fLength; i++) {
            fArray[i] = arrRHS.fArray[i];
        }
    }
    return *this;
}

template<class TYPE>
inline void ArrayT<TYPE>::Alias(int length, const TYPE* ptrArray) {

    fArray = new TYPE[length];

    for (int i = 0; i < length; i++) {
        fArray[i] = ptrArray[i];
    }
    fLength = length;
}

template <class TYPE>
inline int ArrayT<TYPE>::Length() const {
    return this->fLength;
}

template<class TYPE>
inline void ArrayT<TYPE>::Dimension(int length) {

    /* do nothing if the correct length is already assigned */
    if (length != fLength) {
        delete[] fArray;

        /* Allocating new memory */
        TYPE* ptrArr = NULL;
        if (length > 0) {
            ptrArr = new TYPE[length];
        }

        fArray = ptrArr;

        /* set dimensions */
        fLength = length;
    }
}

/**
 * returns a pointer specified element in the array - offset
 * must be 0 <= offset <= Length() <--- one passed the end!
 */
template<class TYPE>
TYPE* ArrayT<TYPE>::Pointer(int offset) {
    if (offset < 0 || offset > fLength){
        cout << "ERR: Offset must be within the length of the array.";
        return nullptr;
    } else {
        return fArray + offset;
    }
}

template<class TYPE>
const TYPE* ArrayT<TYPE>::Pointer(int offset) const {
    if (offset < 0 || offset > fLength ){
        cout << "ERR: Offset must be within the length of the array.";
        return nullptr;
    } else {
        return fArray + offset;
    }
}


#endif //SIMPLEBEAM_ARRAYT_H
