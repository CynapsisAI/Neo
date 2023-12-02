#ifndef NEO_OPERATIONS_HPP
#define NEO_OPERATIONS_HPP
#include <iostream>
#include "tensor.hpp"
#include "operations.hpp"
#include <math.h>


template <typename T>
class tensor;

//base class for all activation functions 
class Activation_Functions{

    public:
        template <typename T>
        T linear(T x){
            return x;
        }
};

//sigmoid function
class sigmoid : public Activation_Functions{

    public:
    template <typename T>
    T sigmoid_function(T x){
        return (1 / (1+exp(-x)));
    }

};

//rectified linear unit function
class relu : public Activation_Functions{

};

class tanh : public Activation_Functions{

};



#endif //NEO_OPERATIONS_HPP
