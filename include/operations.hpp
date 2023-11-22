//
// Created by alial on 2023-11-10.
//

#ifndef NEO_OPERATIONS_HPP
#define NEO_OPERATIONS_HPP
#include <iostream>
#include "tensor.hpp"
#include <iostream>
#include "tensor.hpp"

template <typename T>
class tensor;

//--------declarations-------//

template <typename T>
void inverse(tensor<T> &_tensor);

template <typename T>
int det(tensor<T> _tensor);

template <typename T>
T DetRecHelper(const tensor<T>& matrix);







//--------definitions-------//

//the inverse operator 
template <typename T>
T inverse( const neo::tensor<T> &matrix) {
    assert_check(matrix.dim() ==2, "the tensor is not of the 2nd degree");

    //check if the determinant of the matrix is nonzero, only then we attempt the inverse

}

template <typename T>
T DetRecHelper(const neo::tensor<T>& matrix){
unsigned int size = matrix.size();


//Base case of 1x1 matrix, return the value inside

if(size ==1) return matrix.array()[0];

T determinant = 0;


for (std::size_t col = 0; col < mat.shape()[0]; ++col) {
        T cofactor = mat[0][col] * DetRecHelper(mat.get(0).get(col));
        
        determinant += (col % 2 == 0) ? cofactor : -cofactor;
    }


return result;


}

template <typename T>
T determinant(const neo::tensor<T>& matrix) {
    // Check if the matrix is square
    assert_check(matrix.dim() == 2 && matrix.shape()[0] == matrix.shape()[1], "Determinant can only be calculated for a square matrix.");

    return determinant_recursive(matrix);
}



#endif //NEO_OPERATIONS_HPP
