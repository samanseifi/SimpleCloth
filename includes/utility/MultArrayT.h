//
// Created by saman on 7/5/21.
//

#ifndef SIMPLECLOTH_MULTARRAYT_H
#define SIMPLECLOTH_MULTARRAYT_H


/* base class */
#include "ArrayT.h"

/**
 * A two-dimensional array template object with general type (TYPE)
 */
template <class TYPE>
class MultArrayT: public ArrayT<TYPE> {

protected:

    /** \name dimensions */
    /*@{*/
    int fRows;    /**< Number of rows in the matrix */
    int fCols;    /**< Number of columns in the matrix */
    /*@}*/

public:

    /** Constructors */
    /*@{*/
    /* Default constructor */
    MultArrayT();

    /* Create a matrix of rows=cols  */
    explicit MultArrayT(int size);

    /* Create a matrix of rows and cols */
    explicit MultArrayT(int rows, int cols);
    /*@}*/

    /** \name Operators */
    /* Accessors */
    /*@{*/
    /* Return a the (n_row, n_col) element in a matrix */
    TYPE& operator()(int n_row, int n_col);
    const TYPE& operator()(int n_row, int n_col) const;

    /* return a pointer a column in the matrix */
    TYPE* operator()(int ncol);
    const TYPE* operator()(int ncol) const;

    /* Assignments */
    MultArrayT<TYPE>& operator=(const TYPE& valRHS);
    MultArrayT<TYPE>& operator=(const MultArrayT<TYPE>& matRHS);
    /*@}*/

    /** Set the dimension of the square matrix */
    void Dimension(int squareMatSize);

    /** Set the dimension matrix */
    void Dimension(int numRows, int numCols);

    /** Get number of rows */
    int Rows() const {
        return fRows;
    };

    /** Get number of cols */
    int Cols() const {
        return fCols;
    };


};

// Constructors
template<class TYPE>
MultArrayT<TYPE>::MultArrayT(): fRows(0), fCols(0) { }

template<class TYPE>
MultArrayT<TYPE>::MultArrayT(int size): fRows(0), fCols(0) {

    Dimension(size);
}

template<class TYPE>
MultArrayT<TYPE>::MultArrayT(int rows, int cols): fRows(0), fCols(0) {

    Dimension(rows, cols);
}

// Setting the dimensions
template<class TYPE>
void MultArrayT<TYPE>::Dimension(int squareMatSize) {

    Dimension(squareMatSize, squareMatSize);
}

template<class TYPE>
void MultArrayT<TYPE>::Dimension(int numRows, int numCols) {

    fCols = fRows = 0;

    /* Update the length of this matrix's underlying array */
    ArrayT<TYPE>::Dimension(numRows * numCols);

    /* Update matrix dimensions */
    fRows = numRows;
    fCols = numCols;
}

// Operators
template<class TYPE>
inline TYPE& MultArrayT<TYPE>::operator()(int n_row, int n_col) {

    /* Checking the range */
    assert(n_row <= fRows && n_col <= fCols);

    /* From mapping the array with size of n_col+c_row to a matrix of n_row x n_col */
    /* (i, j) in matrix is (j*numRows + i) */
    return (this->fArray[n_col*fRows + n_row]);
}

template<class TYPE>
inline const TYPE& MultArrayT<TYPE>::operator()(int n_row, int n_col) const {

    /* Checking the range */
    assert(n_row <= fRows && n_col <= fCols);

    /**
     * From mapping the array with size of n_col+c_row to a matrix of n_row x n_col
     * (i, j) in matrix is (j*numRows + i)
     */
    return (this->fArray[n_col*fRows + n_row]);
}

/* returns a pointer to the top of the specified column */
template<class TYPE>
inline TYPE* MultArrayT<TYPE>::operator()(int ncol) {

    return(this->fArray + ncol*fRows);
}

template<class TYPE>
inline const TYPE* MultArrayT<TYPE>::operator()(int ncol) const {

    return(this->fArray + ncol*fRows);
}

template<class TYPE>
inline MultArrayT<TYPE>& MultArrayT<TYPE>::operator=(const TYPE& valRHS) {

    /* Inherited */
    ArrayT<TYPE>::operator=(valRHS);

    return (*this);
}

template<class TYPE>
inline MultArrayT<TYPE>& MultArrayT<TYPE>::operator=(const MultArrayT<TYPE>& matRHS) {

    /* Inherited */
    MultArrayT<TYPE>::operator=(matRHS);

    /* Setting dimensions */
    fRows = matRHS.fRows;
    fCols = matRHS.fCols;

    return (*this);
}


#endif //SIMPLECLOTH_MULTARRAYT_H
