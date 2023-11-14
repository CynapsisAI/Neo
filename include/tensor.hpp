//
// Created by Ali A on 2023-11-13.
//

#ifndef NEO_TENSOR_HPP
#define NEO_TENSOR_HPP

#include <iostream>
#include <numeric>


namespace neo {

  template <typename T>
  class tensor {
  private:

    unsigned int _size{1};
    unsigned int *_shape{};
    unsigned int _dim{};
    T* _array;


  public:
    // Default
    tensor(std::initializer_list<unsigned int> shape);
    tensor(unsigned int *shape, int dim);
    tensor(T* array, unsigned int *shape, int dim);


    // Destructor
    ~tensor();


    // Functions
    template<typename... Ta>
    tensor<T>& get(Ta... args);

    std::pair<unsigned int, unsigned int> loc_interval(int* args, unsigned int cap);




  };


}

// Default Constructor
template <typename T>
neo::tensor<T>::tensor(std::initializer_list<unsigned int> shape) {
  _dim = shape.size();
  _shape = new unsigned int[_dim];
  std::copy(shape.begin(), shape.end(), _shape);
  _size = std::accumulate( shape.begin(), shape.end(), 1, std::multiplies<unsigned int>() );

  // Initialize to 0s
  _array = new T[_size]{0};

}

// Constructor
template <typename T>
neo::tensor<T>::tensor(unsigned int *shape, int dim) {
  _dim = dim;
  _shape = shape;
  for (unsigned int i{}; i < dim; i++) {
    _size *= _shape[i];
  }

  // Initialize to 0s
  _array = new T[_size]{0};

}

// Constructor
template <typename T>
neo::tensor<T>::tensor(T* array, unsigned int* shape, int dim) {
  _dim = dim;
  _shape = shape;
  for (unsigned int i{}; i < dim; i++) {
    _size *= _shape[i];
  }

  // Initialize to 0s
  _array = array;
}


// Destructor
template <typename T>
neo::tensor<T>::~tensor() {
  std::cout<<"Tensor Destructor Called"<<std::endl;
  delete[] _array;
  _array = nullptr;
}

// Return a tuple of <starting index, ending index>
template <typename T>
inline std::pair<unsigned int, unsigned int> neo::tensor<T>::loc_interval(int* args, unsigned int cap){
  unsigned int width{1};

  for (unsigned int i{_dim-1}; i > cap-1; i--) {
    width *= _shape[i];
  }

  unsigned int running_index{0};
  for(unsigned int i{}; i < cap; i++){
    running_index += (args[i]*_shape[i]);
  }

  running_index -= 1;
  running_index *= width;

  std::pair<unsigned int, unsigned int> range(running_index, running_index+width-1);
  return range;

}

template <typename T>
template <typename... Ta>
inline neo::tensor<T>& neo::tensor<T>::get(Ta... args) {
  constexpr unsigned int n = sizeof...(Ta);
  assert_check(n >= 1, "Must pass at least one argument");
  assert_check(n <= _dim, "Indexing deeper than number of dimensions");
  int arr[n]{args...};

  std::pair<unsigned int, unsigned int> range = loc_interval(arr, n);

  neo::tensor<T> new_tensor = new neo::tensor<T>(_array+range.first, _shape+n, _dim-n);


  return *new_tensor;
}


#endif //NEO_TENSOR_HPP
