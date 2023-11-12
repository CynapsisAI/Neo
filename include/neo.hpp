//
// Created by alial on 2023-11-10.
// this should be the main library import (hence why it includes anything relevant below)
//

#ifndef NEO_NEO_HPP
#define NEO_NEO_HPP

#include "./ndarray.hpp"
#include "./structs.hpp"

namespace neo
{
    // intended to include all relevant helper functions. For instance like numpy.tanspose(obj) -> neo::transpose(obj)

    template <typename T>
    void transpose(ndarray<T> ndarray)
    {
    }
}
#endif // NEO_NEO_HPP
