tuple_utility
=============

Utilities for C++ tuples.

`tuple_map`:

    #include "tuple_utility.hpp"
    
    int main()
    {
      auto t = std::make_tuple(0, 1, 2, 3);
    
      auto negative_t = tuple_map([](int x)
      {
        return -x;
      }, t);
    
      std::cout << "negative_t: ";
      tuple_print(negative_t);
      std::cout << std::endl;

      // prints 0, -1, -2, -3
    
      return 0;
    }
   
`tuple_head` & `tuple_tail`:

    #include "tuple_utility.hpp"

    int main()
    {
      auto t = std::make_tuple(0, 1, 2, 3);

      std::cout << "t's head is " << tuple_head(t) << std::endl;
      
      // prints 0

      auto t_tail = tuple_tail(t);
      std::cout << "t's tail is ";
      tuple_print(t_tail);
      std::cout << std::endl;

      // prints 1, 2, 3

      return 0;
    }

`tuple_take` & `tuple_drop`:

    #include "tuple_utility.hpp"

    int main()
    {
      auto t = std::make_tuple(0, 1, 2, 3);

      auto t_take_2 = tuple_take<2>(t);

      std::cout << "t_take_2 is ";
      tuple_print(t_take_2);
      std::cout << std::endl;

      // prints 0, 1

      auto t_drop_2 = tuple_drop<2>(t);

      std::cout << "t_drop_2 is ";
      tuple_drop<2>(t);
      std::cout << std::endl;

      // prints 2, 3

      return 0;
    }

`tuple_append`:

    #include "tuple_utility.hpp"

    int main()
    {
      auto t = std::make_tuple(0, 1, 2, 3);

      auto t_append_4 = tuple_append(t, 4);

      std::cout << "t_append_4 is ";
      tuple_print(t_append_4);
      std::cout << std::endl;

      // prints 1, 2, 3, 4

      return 0;
    }

`tuple_reduce`:

    #include "tuple_reduce.hpp"

    int main()
    {
      auto t = std::make_tuple(0, 1, 2, 3);

      auto sum = tuple_reduce(t, 0, [](int x, int y){return x + y;});

      std::cout << "sum of t's elements is " << sum << std::endl;
      // prints 6

      return 0;
    }

