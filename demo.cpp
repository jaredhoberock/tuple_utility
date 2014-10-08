#include <iostream>
#include <vector>
#include "tuple_map.hpp"
#include "tuple_take.hpp"
#include "tuple_drop.hpp"
#include "make_from_tuple.hpp"

int main()
{
  auto t = std::make_tuple(0, 1, 2, 3);

  // negate the elements of a tuple
  auto negative_t = tuple_map(std::negate<int>(), t);

  std::cout << "negative_t: " << std::get<0>(negative_t) << ", " << std::get<1>(negative_t) << ", " << std::get<2>(negative_t) << ", " << std::get<3>(negative_t) << std::endl;

  // add two tuples together
  auto zero_t = tuple_map(std::plus<int>(), t, negative_t);

  std::cout << "zero_t: " << std::get<0>(zero_t) << ", " << std::get<1>(zero_t) << ", " << std::get<2>(zero_t) << ", " << std::get<3>(zero_t) << std::endl;

  auto one_t = std::make_tuple(1,1,1);

  auto two_t = std::make_tuple(2,2,2);

  auto three_t = std::make_tuple(3,3,3);

  // add three tuples together
  auto six_t = tuple_map([](int x, int y, int z){return x + y + z;}, one_t, two_t, three_t);

  std::cout << "six_t: " << std::get<0>(six_t) << ", " << std::get<1>(six_t) << ", " << std::get<2>(six_t) << std::endl;

  // take the first 2 elements of six_t:
  auto six_t_first_two = tuple_take<2>(six_t);

  std::cout << "six_t_first_two: " << std::get<0>(six_t_first_two) << ", " << std::get<1>(six_t_first_two) << std::endl;

  // drop the last 2 elements of t:
  auto t_drop_2 = tuple_drop<2>(t);

  std::cout << "t_drop_2: " << std::get<0>(t_drop_2) << ", " << std::get<1>(t_drop_2) << std::endl;

  // make a std::vector from constructor arguments taken from a tuple
  auto vector_of_13s = make_from_tuple<std::vector<int>>(std::make_tuple(13,13));

  return 0;
}

