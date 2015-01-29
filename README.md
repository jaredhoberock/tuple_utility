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

`tuple_map` is variadic:

    #include "tuple_utility.hpp"
    
    int main()
    {
      auto t = std::make_tuple(0, 1, 2, 3);
    
      auto negative_t = tuple_map([](int x)
      {
        return -x;
      }, t);
    
      auto zero_t = tuple_map([](int x, int y)
      {
        return x + y;
      }, t, negative_t);

      std::cout << "zero_t: ";
      tuple_print(zero_t);
      std::cout << std::endl;

      // prints 0, 0, 0, 0
    
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

`make_from_tuple`:

    #include "tuple_utility.hpp"
    #include <vector>

    int main()
    {
      auto t = std::make_tuple(13, 13);

      auto vector_of_13s = make_from_tuple<std::vector<int>>(t);

      // vector_of_13s is a std::vector<int> containing 13
      // elements which are all equal to 13

      return 0;
    }

`tuple_reduce`:

    #include "tuple_utility.hpp"

    int main()
    {
      auto t = std::make_tuple(0, 1, 2, 3);

      auto sum = tuple_reduce(t, 0, [](int x, int y){return x + y;});

      std::cout << "sum of t's elements is " << sum << std::endl;
      // prints 6

      return 0;
    }

`tuple_for_each`:

    #include "tuple_utility.hpp"

    int main()
    {
      auto t = std::make_tuple(0, 1, 2, 3);

      auto sum = tuple_for_each([](int& x){ ++x; }, t);

      tuple_print(t);
      // prints 1, 2, 3, 4

      return 0;
    }

`tuple_filter`:

    #include "tuple_utility.hpp"
    #include <type_traits>
    #include <string>

    int main()
    {
      auto t1 = std::make_tuple(13, 3.14159, std::string("hi there"));

      auto t2 = tuple_filter<std::is_arithmetic>(t1);

      tuple_print(t2);
      std::cout << std::endl;
      // prints 13, 3.14159

      return 0;
    }

`tuple_lexicographical_compare`:

    #include "tuple_utility.hpp"

    int main()
    {
      auto t1 = std::make_tuple(0, 1, 2);
      auto t2 = std::make_tuple(3, 4);

      std::cout << "t1 is less than t2: " << tuple_lexicographical_compare(t1, t2) << std::endl;
      // prints 1

      auto t3 = std::make_tuple(5, 6, 7);
      auto t4 = std::make_tuple(0, 1, 2, 3, 4);

      std::cout << "t3 is less than t4: " << tuple_lexicographical_compare(t3, t4) << std::endl;
      // prints 0

      return 0;
    }

`std::array`s are tuples too:

    #include "tuple_utility.hpp"
    #include <array>

    int main()
    {
      std::array<int> t = {0, 1, 2, 3};
    
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

As is any type which specializes `tuple_traits`:

    #include "tuple_utility.hpp"
    #include <utility>
    
    struct my_float3
    {
      float x, y, z;
    };

    template<>
    struct tuple_traits<my_float3>
    {
      using tuple_type = my_float3;
      
      static const size_t size = 3;
      
      template<size_t i>
      using element_type = float;
      
      template<size_t i>
      static float& get(tuple_type& t)
      {
        static_assert(i < size, "i must be < size");
        return &t.x + i;
      }
      
      template<size_t i>
      static const float& get(const tuple_type& t)
      {
        static_assert(i < size, "i must be < size");
        return &t.x + i;
      }
      
      template<size_t i>
      static float&& get(tuple_type&& t)
      {
        static_assert(i < size, "i must be < size");
        return std::move(&t.x + i);
      }
    };
    
    int main()
    {
      my_float3 t = {0.f, 1.f, 2.f, 3.f};

      auto negative_t = tuple_map([](float x)
      {
        return -x;
      }, t);

      std::cout << "negative_t: ";
      tuple_print(negative_t);
      std::cout << std::endl;

      // prints 0, -1, -2, -3

      return 0;
    }
