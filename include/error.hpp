//
// Created by Ali A on 2023-11-17.
//

#ifndef NEO_ERROR_HPP
#define NEO_ERROR_HPP

#include <iostream>
#include <exception>

/*
 Exception types:
    logic_error
    invalid_argument
    domain_error
    length_error
    out_of_range
    future_error (since C++11)
    runtime_error
    range_error
    overflow_error
    underflow_error
    regex_error (since C++11)
    system_error (since C++11)
    ios_base::failure (since C++11)
    filesystem::filesystem_error (since C++17)
    tx_exception (TM TS)
    nonexistent_local_time (since C++20)
    ambiguous_local_time (since C++20)
    format_error (since C++20)
    bad_typeid
    bad_cast
    bad_any_cast (since C++17)
    bad_optional_access (since C++17)
    bad_expected_access (since C++23)
    bad_weak_ptr (since C++11)
    bad_function_call (since C++11)
    bad_alloc
    bad_array_new_length (since C++11)
    bad_exception
    ios_base::failure (until C++11)
    bad_variant_access (since C++17)
 */


void assert_check(bool expr, std::string message){
  if(expr) return;
  std::cout<<"Error: "<<message<<std::endl;
  exit(0);
}


#endif //NEO_ERROR_HPP
