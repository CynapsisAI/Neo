//
// Created by alial on 2023-11-10.
//

#ifndef NEO_OPERATIONS_HPP
#define NEO_OPERATIONS_HPP
#include <iostream>
#include "tensor.hpp"


template <typename T>
class tensor;

//--------declarations-------//

template <typename T>
neo::tensor<T> adjugate(const neo::tensor<T>& matrix) {
}

/**
* Calculates the inverse of only 2D Tensors 
* @param matrix
* @return neo::tensor<T>
*/

template <typename T>
neo::tensor<T> inverse(tensor<T> &matrix);


/**
* Calculates the determinant of an nxn matrix  
* @param matrix
* @return T
*/
template <typename T>
T determinant(tensor<T> matrix);


/**
 * Recursive determinant helper, uses cofactor expansion recursively with base case of a 1x1 matrix
 * 
 * @param matrix
 * @return T
*/
template <typename T>
T DetRecHelper(const tensor<T>& matrix);

/**
 * Recursive determinant helper, uses cofactor expansion recursively with base case of a 1x1 matrix
 * 
 * @param matrix
 * @return T
*/
template <typename T>
T DetRecHelper(const tensor<T>& matrix);


//--------definitions-------//

//the inverse operator 

template <typename T>
neo::tensor<T> inverse( const neo::tensor<T> &matrix) {
    assert_check(matrix.dim() ==2, "the tensor is not of the 2nd degree");

    T det = determinant(matrix);

    //check if the matrix is invertible
    assert_check(det != 0, "Matrix is not invertible.");


    // Find the inverse using the formula: inverse(A) = adjugate(A) / det(A)
    neo::tensor<T> adj = adjugate(matrix);

    neo::tensor<T> inverted_matrix = adj/det;
    
    return inverted_matrix;


}

// Function to calculate the adjugate matrix of a matrix
template <typename T>

neo::tensor<T> adjugate(const neo::tensor<T>& matrix) {
    unsigned int size = matrix.shape()[0];

    // Create a tensor to store the adjugate matrix
    neo::tensor<T> result(neo::shape(size, size));

    for (std::size_t i = 0; i < size; ++i) {
        
        for (std::size_t j = 0; j < size; ++j) {
            // Calculate the cofactor for each element

            T cofactor = DetRecHelper(matrix.minor(i, j));

            // Assign the cofactor to the transposed position in the result matrix
            result[j][i] = (i + j) % 2 == 0 ? cofactor : -cofactor;
        }
    }

    return result;
}



template <typename T>
T DetRecHelper(const neo::tensor<T>& matrix){
unsigned int size = matrix.size();


//Base case of 1x1 matrix, return the value inside

if(size ==1) return matrix.array()[0];

T determinant = 0;


for (std::size_t col = 0; col < matrix.shape()[0]; ++col) {
        T cofactor = matrix[0][col] * DetRecHelper(matrix.get(0).get(col));
        
        determinant += (col % 2 == 0) ? cofactor : -cofactor;
    }


return determinant;


}

template <typename T>
T determinant(const neo::tensor<T>& matrix) {
    // Check if the matrix is square
    assert_check(matrix.dim() == 2 && matrix.shape()[0] == matrix.shape()[1], "Determinant can only be calculated for a square matrix.");


    return determinant_recursive(matrix);
}



#endif //NEO_OPERATIONS_HPP
