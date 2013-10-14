//
//  ANMatrix.h
//  XorSystem
//
//  Created by Alex Nichol on 10/14/13.
//  Copyright (c) 2013 Alex Nichol. All rights reserved.
//

#ifndef __XorSystem__ANMatrix__
#define __XorSystem__ANMatrix__

#include <vector>
#include <sstream>

using namespace std;

class ANMatrixException : exception {
};

class ANMatrixDimensionsMismatch : public ANMatrixException {
};

class ANMatrixSingularity : public ANMatrixException {
};

/**
 * Templates are dumb, so I just went ahead and
 * defined all my methods in the declaration
 * as if I was a Java-head.
 */
template <class T>
class ANMatrix {
private:
    vector<T> matrixData;
    unsigned int rows, columns;
public:
    ANMatrix() {
    }
    
    ANMatrix(vector<T> items, unsigned int rows, unsigned int columns) {
        this->matrixData = items;
        this->rows = rows;
        this->columns = columns;
    }
    
    ANMatrix(T const * list, unsigned int rows, unsigned int columns) {
        this->rows = rows;
        this->columns = columns;
        for (int i = 0; i < rows * columns; i++) {
            this->matrixData.push_back(list[i]);
        }
    }
    
    ANMatrix(const ANMatrix<T> & matrix) {
        this->matrixData = matrix.matrixData;
        this->rows = matrix.rows;
        this->columns = matrix.columns;
    }
    
    /**
     * Create a row exchange matrix or an identity
     */
    ANMatrix(unsigned int _rows, unsigned int _columns, unsigned int source = -1, unsigned int dest = -1) {
        this->rows = _rows;
        this->columns = _columns;
        T zeroEl = (T)0;
        T oneEl = (T)1;
        for (int i = 0; i < this->rows; i++) {
            int doRow = i == source ? dest : (i == dest ? source : i);
            for (int j = 0; j < this->columns; j++) {
                if (j == doRow) {
                    this->matrixData.push_back(oneEl);
                } else {
                    this->matrixData.push_back(zeroEl);
                }
            }
        }
    }
    
    // getting information
    
    virtual T getAt(int row, int col) const {
        return this->matrixData[col + (row * this->columns)];
    }
    
    virtual string toMATLABString() const {
        ostringstream stream;
        stream << "[";
        for (int row = 0; row < this->rows; row++) {
            for (int col = 0; col < this->columns; col++) {
                if (col > 0) stream << " ";
                stream << this->getAt(row, col);
            }
            if (row < this->rows - 1) stream << "; ";
        }
        stream << "]";
        return stream.str();
    }
    
    // operations
    
    virtual ANMatrix<T>& operator=(const ANMatrix<T> & matrix) {
        this->matrixData = matrix.matrixData;
        this->rows = matrix.rows;
        this->columns = matrix.columns;
        return *this;
    }
    
    virtual ANMatrix<T>& operator+=(const ANMatrix<T> & matrix) {
        if (matrix.rows != this->rows || matrix.columns != this->columns) {
            throw new ANMatrixDimensionsMismatch();
        }
        
        // add every entry
        for (unsigned int i = 0; i < this->matrixData.size(); i++) {
            T obj1 = this->matrixData[i];
            T obj2 = matrix.matrixData[i];
            this->matrixData[i] = obj1 + obj2;
        }
        
        return *this;
    }
    
    virtual ANMatrix<T>& operator-=(const ANMatrix<T> & matrix) {
        if (matrix.rows != this->rows || matrix.columns != this->columns) {
            throw new ANMatrixDimensionsMismatch();
        }
        
        // subtract every entry
        for (unsigned int i = 0; i < this->matrixData.size(); i++) {
            T obj1 = this->matrixData[i];
            T obj2 = matrix.matrixData[i];
            this->matrixData[i] = obj1 + obj2;
        }
        
        return *this;
    }
    
    virtual ANMatrix<T> & operator*=(const ANMatrix<T> & matrix) {
        if (this->columns != matrix.rows) {
            throw new ANMatrixDimensionsMismatch;
        }
        vector<T> destVector;
        for (int row = 0; row < this->rows; row++) {
            for (int column = 0; column < matrix.columns; column++) {
                T product = (T)0;
                for (int i = 0; i < matrix.rows; i++) {
                    product += this->getAt(row, i) * matrix.getAt(i, column);
                }
                destVector.push_back(product);
            }
        }
        this->matrixData = destVector;
        this->columns = matrix.columns;
        return *this;
    }
    
    template <typename T2>
    friend ANMatrix<T2> operator+(const ANMatrix<T2> & m1, const ANMatrix<T2> & m2);
    template <typename T2>
    friend ANMatrix<T2> operator-(const ANMatrix<T2> & m1, const ANMatrix<T2> & m2);
    template <typename T2>
    friend ANMatrix<T2> operator*(const ANMatrix<T2> & m1, const ANMatrix<T2> & m2);
    
    // advanced operations
    
    /**
     * Performs gauss-jordan elimination
     */
    virtual ANMatrix<T> eliminate(ANMatrix<T> & transform, int & rank) const {
        int pivotsDone = 0;
        ANMatrix<T> working = *this;
        for (int col = 0; col < this->columns && pivotsDone < this->rows; col++) {
            int pivotRow = -1;
            for (int rowCheck = pivotsDone; rowCheck < this->rows; rowCheck++) {
                if (working.getAt(rowCheck, col) != (T)0) {
                    pivotRow = rowCheck;
                    break;
                }
            }
            if (pivotRow < 0) continue;
            if (pivotRow != pivotsDone) {
                // row exchange is necessary
                ANMatrix<T> exchange(this->rows, this->rows, pivotsDone, pivotRow);
                working = exchange * working;
                transform = exchange * transform;
            }
            
            // create an elimination matrix
            ANMatrix eliminator(this->rows, this->rows);
            T pivotValue = working.getAt(pivotsDone, col);
            for (int reduceRow = pivotsDone; reduceRow < this->rows; reduceRow++) {
                if (working.getAt(reduceRow, col) != (T)0) {
                    // supply the elimination coefficient
                    T subtractAmount = working.getAt(reduceRow, col) / pivotValue;
                    eliminator.setAt(reduceRow, pivotsDone, (T)0 - subtractAmount);
                }
            }
            
            transform = eliminator * transform;
            working = eliminator * working;
            
            pivotsDone += 1;
            rank += 1;
        }
        return working;
    }
    
    /**
     * Finds the row-reduced echelon form
     */
    virtual ANMatrix<T> rref(ANMatrix<T> & transform, int & rank) const {
        ANMatrix<T> working = eliminate(transform, rank);
        
        for (int row = this->rows - 1; row >= 0; row--) {
            int pivotColumn = -1;
            for (int i = 0; i < this->columns; i++) {
                if (working.getAt(row, i) != (T)0) {
                    pivotColumn = i;
                    break;
                }
            }
            if (pivotColumn < 0) continue;
            
            T pivotValue = working.getAt(row, pivotColumn);
            ANMatrix deduceMatrix(this->rows, this->rows);
            for (int i = row - 1; i >= 0; i--) {
                T columnValue = working.getAt(i, pivotColumn);
                T reduceScale = columnValue / pivotValue;
                deduceMatrix.setAt(i, row, (T)0 - reduceScale);
            }
            deduceMatrix.setAt(row, pivotColumn, (T)1 / pivotValue);
            transform = deduceMatrix * transform;
            working = deduceMatrix * working;
        }
        
        return working;
    }
    
    /**
     * Inverts square matrices
     */
    virtual ANMatrix<T> invert() const {
        if (this->rows != this->columns) {
            throw new ANMatrixDimensionsMismatch;
        }
        
        ANMatrix<T> mat(this->rows, this->rows);
        int rank = 0;
        
        this->rref(mat, rank);
        if (rank != this->rows) {
            throw new ANMatrixSingularity();
        }
        
        return mat;
    }
    
private:
    
    virtual void setAt(int row, int col, T value) {
        this->matrixData[col + (row * this->columns)] = value;
    }
    
};

template <class T>
ANMatrix<T> operator+(const ANMatrix<T> & m1, const ANMatrix<T> & m2) {
    ANMatrix<T> result = m1;
    result += m2;
    return result;
}

template <class T>
ANMatrix<T> operator-(const ANMatrix<T> & m1, const ANMatrix<T> & m2) {
    ANMatrix<T> result = m1;
    result -= m2;
    return result;
}

template <class T>
ANMatrix<T> operator*(const ANMatrix<T> & m1, const ANMatrix<T> & m2) {
    ANMatrix<T> result = m1;
    result *= m2;
    return result;
}

#endif /* defined(__XorSystem__ANMatrix__) */
