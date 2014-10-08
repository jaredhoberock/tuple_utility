tuple_utility
=============

Utilities for C++ tuples.

`tuple_map`:

    #include "tuple_map.hpp"
    #include <iostream>
    
    int main()
    {
      auto t = std::make_tuple(0, 1, 2, 3);
    
      auto negative_t = tuple_map([](int x)
      {
        return -x;
      }, t);
    
      std::cout << "negative_t: " << std::get<0>(negative_t) << ", " << std::get<1>(negative_t) << ", " << std::get<2>(negative_t) << ", " << std::get<3>(negative_t) << std::endl;
    
      return 0;
    }

