//
// Created by Ali A on 2023-11-13.
//

#ifndef NEO_TENSOR_HPP
#define NEO_TENSOR_HPP

#include <iostream>
#include <numeric>
#include "structs.hpp"
#include "error.hpp"


namespace neo {

  template <typename T>
  class tensor {
  private:
    unsigned int _size{1}; //!< Size of Array
    unsigned int *_shape{}; //!< Shape of Tensor
    unsigned int _rank{}; //!< Rank of tensor
    T* _array; ///< Array of all values. Not accessed directly, as the array is a single dimension wheras the tensor may be of a different rank/dimension


  public:
    // Default
    tensor(std::initializer_list<unsigned int> shape);
    tensor(T* array, unsigned int *shape, int rank, bool copy_array);

		// Copy constructor
		tensor(const tensor<T>& tensor);


    // Destructor
    ~tensor();

		// Assignment operator
		tensor<T>& operator= (const tensor<T>& tensor);
	  tensor<T>& operator= (const T val);

    // Functions
    /**
     * Get Function. Similar functionality to []
     * Variadic Arguments
     * @tparam Ta
     * @param args
     * @return tensor<T>&
     */
    template<typename... Ta>
    tensor<T>& get(Ta... args) const;

    std::pair<unsigned int, unsigned int> loc_interval(int* args, unsigned int cap) const;

    /**
     * Flattens the tensor into a rank 1 tensor
     * @param in_place if the operation should act on the original tensor
     * @return tensor<T>& of rank 1
     */
    tensor<T>& flatten(bool in_place = false);

    // Square bracket operator
    /**
     * Indexing the array. Acts recursively to access rank-n tensors
     * Const Variant
     * @param index
     * @return tensor<T>
     */
    neo::tensor<T> operator[](unsigned int index) const;

    /**
     * Indexing the array. Acts recursively to access rank-n tensors
     * @param index
     * @return tensor<T>&
     */
    neo::tensor<T>& operator[](unsigned int index);


		// Getters
		unsigned int rank() const {return _rank;}
		unsigned int size() const {return _size;}
		unsigned int* shape() const {return _shape;}
		T* array() const {return _array;}

    /**
     * Get scalar of tensor given it is a rank 0 tensor
     * @return T
     * @throws logic_error If called on a tensor that is not rank 0
     */
    T scalar() const { assert_check(_rank == 0,"Can only call scalar on tensor rank=0"); return _array[0];};


    // Operator overload
    /**
     * Scalar Addition
     * @param scalar
     * @return tensor<T>
     */
    tensor<T> operator+(const T scalar);
    /**
     * Tensor Addition
     * Add tensors element-wise
     * @param tens
     * @return tensor<T>
     */
    tensor<T> operator+(const tensor<T>& tens);

    /**
     * Scalar Multiplication
     * @param scalar
     * @return tensor<T>
     */
    tensor<T> operator*(const T scalar);

    /**
     * Scalar Division
     * @param scalar
     * @return tensor<T>
     */
    tensor<T> operator/(const T scalar);


    /**
    * Assignment Scalar Addition
    * @param scalar
    * @return tensor<T>&
    */
    tensor<T>& operator+=(const T scalar);
    /**
     * Assignment Tensor Addition
     * Add tensors element-wise
     * @param tens
     * @return tensor<T>&
     */
    tensor<T>& operator+=(const tensor<T>& tens);

    /**
     * Assignment Scalar Multiplication
     * @param scalar
     * @return tensor<T>&
     */
    tensor<T>& operator*=(const T scalar);

    /**
     * Assignment Scalar Division
     * @param scalar
     * @return tensor<T>&
     */
    tensor<T>& operator/=(const T scalar);



  };
}
// Output Operator <<
template <typename T>
std::ostream &operator<<(std::ostream &s, const neo::tensor<T> &tensor);


// Default Constructor
template <typename T>
neo::tensor<T>::tensor(std::initializer_list<unsigned int> shape) {
  _rank = shape.size();
  _shape = new unsigned int[_rank];
  std::copy(shape.begin(), shape.end(), _shape);
  _size = std::accumulate( shape.begin(), shape.end(), 1, std::multiplies<unsigned int>() );

  assert_check(_size > 0, "During Creation: Sub-dimension cannot be 0");

  // Initialize to 0s
  _array = new T[_size]{0};

}

// Constructor by copy
template <typename T>
neo::tensor<T>::tensor(T* array, unsigned int* shape, int rank, bool copy_array) {
  _rank = rank;

  // Create copy of shape and assign size
  _shape = new unsigned int[_rank];
  for (std::size_t i{}; i < rank; i++){
    _shape[i] = shape[i];
    _size *= _shape[i];
  }

  if (copy_array){
    // Create copy of array
    _array = new T[_size];
    for (std::size_t i{}; i < _size; i++){
      _array[i] = array[i];
    }

  } else {
    _array = array;
  }



}

// Copy constructor
template <typename T>
neo::tensor<T>::tensor(const tensor<T>& tensor) {
	_rank = tensor.rank();
	_shape = tensor.shape();
  _size = tensor.size();
  _array = new T[_size];
  T* array = tensor.array();
  for (std::size_t i{}; i < _size; i++){
    _array[i] = array[i];
  }
}


// Destructor
template <typename T>
neo::tensor<T>::~tensor() {
  delete[] _array;
  _array = nullptr;

  delete[] _shape;
  _shape = nullptr;

}

// Return a tuple of <starting index, ending index>
template <typename T>
inline std::pair<unsigned int, unsigned int> neo::tensor<T>::loc_interval(int* args, unsigned int cap) const{
  unsigned int size_copy{_size};

  unsigned int running_index{0};
  for(std::size_t i{}; i < cap; i++){
    size_copy/=_shape[i];
    running_index += (args[i]*size_copy);
  }

  std::pair<unsigned int, unsigned int> range(running_index, running_index+size_copy-1);
  return range;
}

// Copy assignment operator
template <typename T>
inline neo::tensor<T>& neo::tensor<T>::operator=(const tensor <T> &tensor) {
	// Self assignment check
	if (this == &tensor){
		return *this;
	}

	// Check if tensor is same size
	assert_check(_rank == tensor.rank(), "Tensors must be the same size & rank");
	unsigned int* tensor_shape = tensor.shape();

	for (std::size_t i{}; i < _rank; i++){
		assert_check(_shape[i] == tensor_shape[i], "Tensors must be the same size & rank");
	}

	T* new_array = tensor.array();

	for (std::size_t i{}; i < _size; i++)
		_array[i] = new_array[i];

	return *this;
}


template <typename T>
inline neo::tensor<T>& neo::tensor<T>::operator=(const T val) {
	for (std::size_t i{}; i < _size; i++){
		_array[i] = val;
	}

	return *this;
}


template <typename T>
template <typename... Ta>
inline neo::tensor<T>& neo::tensor<T>::get(Ta... args) const{
  constexpr unsigned int n = sizeof...(Ta);
  assert_check(n >= 1,"Must pass at least one argument");
  assert_check(n <= _rank, "Indexing deeper than number of dimensions");
  int arr[n]{args...};

  // Check that arguments are within bounds
  for (std::size_t i{}; i < n; i++){
    assert_check(arr[i]<_shape[i], "Index out of bounds for dimension");
  }

  std::pair<unsigned int, unsigned int> range = loc_interval(arr, n);
  neo::tensor<T>* new_tensor = new neo::tensor<T>(_array+range.first, _shape+n, _rank-n, false);
  return *new_tensor;
}

template <typename T>
inline neo::tensor<T>& neo::tensor<T>::operator[](unsigned int i){
  assert_check(i<_shape[0], "Index out of bounds");

  int arr[1]{(int)i};
  std::pair<unsigned int, unsigned int> range = loc_interval(arr, 1);
  neo::tensor<T>* new_tensor = new neo::tensor<T>(_array+range.first, _shape+1, _rank-1, false);

  return *new_tensor;
}

template <typename T>
inline neo::tensor<T> neo::tensor<T>::operator[](unsigned int i) const{
  assert_check(i<_shape[0],"Index out of bounds");

  int arr[1]{(int)i};
  std::pair<unsigned int, unsigned int> range = loc_interval(arr, 1);
  neo::tensor<T>* new_tensor = new neo::tensor<T>(_array+range.first, _shape+1, _rank-1, false);

  return *new_tensor;
}

template <typename T>
inline neo::tensor<T>& neo::tensor<T>::flatten(bool in_place){

	if (in_place) {
		delete[] _shape;
		_shape = new unsigned int[1]{_size};
		return *this;
	}

	// Create copy of array
	T* new_array = new T[_size];
	unsigned int* new_shape = new unsigned int[1]{_size};
	for (std::size_t i{}; i < _size; i++)
		new_array[i] = _array[i];


	neo::tensor<T>* new_tensor = new neo::tensor<T>(new_array, new_shape, 1, false);
	return *new_tensor;
}


template <typename T>
std::ostream& recurse_ostream(std::ostream &s, const neo::tensor<T> &tensor){

  unsigned int* shape = tensor.shape();
  T* tensor_array = tensor.array();

  unsigned int rank = tensor.rank();

  if (rank <= 1){
    for (std::size_t i{}; i < tensor.size(); i++){
      s<<tensor_array[i];
      if (i != (tensor.size()-1)){
        s<<", ";
      }
    }
    return s;
  }

  std::size_t width = shape[0];
  for (std::size_t i{}; i < width; i++){
    s<<"[";
    neo::tensor<T> lower_tensor = tensor.get((int)i);
    recurse_ostream(s, lower_tensor);
    //s<<lower_tensor;
    s<<"]";
    if (i != (width-1)){
      s<<", ";
    }
  }
  return s;
}

// Output Operator <<
template <typename T>
std::ostream &operator<<(std::ostream &s, const neo::tensor<T> &tensor) {
  s<<"[";
  recurse_ostream(s, tensor);
  s<<"]";
  return s;
}

// Operator Overload
template <typename T>
neo::tensor<T> neo::tensor<T>::operator+(const T scalar){
  T* new_arr = new T[size()];
  for (std::size_t i{}; i < size(); i++) {
    new_arr[i] = _array[i] + scalar;
  }

  tensor<T>* new_tens = new tensor<T>(new_arr, _shape, _rank, false);

  return *new_tens;
}

template <typename T>
neo::tensor<T> neo::tensor<T>::operator+(const tensor<T>& tens){

  if (this == &tens){
    T* array = new T[_size];

    for (std::size_t i{}; i < _size; i++){ array[i] = _array[i]*2; }

    neo::tensor<T>* new_tens = new neo::tensor<T>(array, _shape, _rank, false);

    return *new_tens;
  }


  assert_check(_rank == tens.rank(), "Tensors must be the same rank");
  unsigned int* tens_shape = tens.shape();
  for (std::size_t i{}; i < _rank; i++){
    assert_check(_shape[i] == tens_shape[i], "Tensors must be the same shape");
  }

  T* new_arr = new T[size()];
  T* tens_arr = tens.array();

  for (std::size_t i{}; i < size(); i++){
    new_arr[i] = _array[i] + tens_arr[i];
  }

  neo::tensor<T>* new_tens = new neo::tensor<T>(new_arr, _shape, _rank, false);

  return *new_tens;
}

template <typename T>
neo::tensor<T> neo::tensor<T>::operator*(const T scalar){
  T* new_arr = new T[size()];
  for (std::size_t i{}; i < size(); i++) {
    new_arr[i] = _array[i] * scalar;
  }

  tensor<T>* new_tens = new tensor<T>(new_arr, _shape, _rank, false);

  return *new_tens;
}

template <typename T>
neo::tensor<T> neo::tensor<T>::operator/(const T scalar){
  assert_check(scalar != 0, "Cannot divide by 0");
  T* new_arr = new T[size()];
  for (std::size_t i{}; i < size(); i++) {
    new_arr[i] = _array[i] / scalar;
  }

  tensor<T>* new_tens = new tensor<T>(new_arr, _shape, _rank, false);

  return *new_tens;
}

template <typename T>
neo::tensor<T>& neo::tensor<T>::operator+=(const T scalar){
  for (std::size_t i{}; i < size(); i++) {
    _array[i] += scalar;
  }

  return *this;
}


template <typename T>
neo::tensor<T>& neo::tensor<T>::operator+=(const tensor<T>& tens){
  if (this == &tens){
    for (std::size_t i{}; i < _size; i++){ _array[i] *= 2; }
    return *this;
  }

  assert_check(_rank == tens.rank(), "Tensors must be the same rank");
  unsigned int* tens_shape = tens.shape();
  for (std::size_t i{}; i < _rank; i++){
    assert_check(_shape[i] == tens_shape[i], "Tensors must be the same shape");
  }

  T* tens_arr = tens.array();

  for (std::size_t i{}; i < size(); i++){
    _array[i] += tens_arr[i];
  }

  return *this;
}

template <typename T>
neo::tensor<T>& neo::tensor<T>::operator*=(const T scalar){
  for (std::size_t i{}; i < size(); i++) {
    _array[i] *= scalar;
  }

  return *this;
}

template <typename T>
neo::tensor<T>& neo::tensor<T>::operator/=(const T scalar){
  assert_check(scalar != 0, "Cannot divide by 0");


  for (std::size_t i{}; i < size(); i++) {
    _array[i] /= scalar;
  }

  return *this;
}

#endif //NEO_TENSOR_HPP
