tuple_map
=========

Functional map operation for C++ tuples

    #include "tuple_map.hpp"
    #include <iostream>
    
    int main()
    {
      auto t = std::make_tuple(0, 1, 2, 3);
    
      auto negative_t = tuple_map(t, [](int x)
      {
        return -x;
      });
    
      std::cout << "negative_t: " << std::get<0>(negative_t) << ", " << std::get<1>(negative_t) << ", " << std::get<2>(negative_t) << ", " << std::get<3>(negative_t) << std::endl;
    
      return 0;
    }

