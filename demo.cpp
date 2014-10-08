#include "tuple_map.hpp"
#include <iostream>

int main()
{
  auto t = std::make_tuple(0, 1, 2, 3);

  auto negative_t = tuple_map(std::negate<int>(), t);

  std::cout << "negative_t: " << std::get<0>(negative_t) << ", " << std::get<1>(negative_t) << ", " << std::get<2>(negative_t) << ", " << std::get<3>(negative_t) << std::endl;

  auto zero_t = tuple_map(std::plus<int>(), t, negative_t);

  std::cout << "zero_t: " << std::get<0>(zero_t) << ", " << std::get<1>(zero_t) << ", " << std::get<2>(zero_t) << ", " << std::get<3>(zero_t) << std::endl;

  auto one_t = std::make_tuple(1,1,1);

  auto two_t = std::make_tuple(2,2,2);

  auto three_t = std::make_tuple(3,3,3);

  auto six_t = tuple_map([](int x, int y, int z){return x + y + z;}, one_t, two_t, three_t);

  std::cout << "six_t: " << std::get<0>(six_t) << ", " << std::get<1>(six_t) << ", " << std::get<2>(six_t) << std::endl;

  return 0;
}

