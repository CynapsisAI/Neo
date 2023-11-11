//
// Created by alial on 2023-11-10.
//

#include "structs.hpp"

// Shape
std::ostream &operator<<(std::ostream &s, const neo::shape &shape){
	s<<"Shape: (";
	for (std::size_t i{}; i<shape.dim(); i++){
		if (i != shape.dim()-1)
			s<<shape.list()[i]<<", ";
		else
			s<<shape.list()[i];
	}
	s<<")";

	return s;
}