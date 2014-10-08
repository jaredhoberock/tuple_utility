#pragma once

#include <iostream>
#include <tuple>
#include "tuple_head.hpp"
#include "tuple_tail.hpp"

template<class Tuple, class T>
typename std::enable_if<
  std::tuple_size<Tuple>::value == 0
>::type
tuple_print(const Tuple& t, std::ostream& os, const T&)
{
}

template<class Tuple, class T>
typename std::enable_if<
  std::tuple_size<Tuple>::value == 1
>::type
tuple_print(const Tuple& t, std::ostream& os, const T&)
{
  os << std::get<0>(t);
}

template<class Tuple, class T>
typename std::enable_if<
  (std::tuple_size<Tuple>::value > 1)
>::type
  tuple_print(const Tuple& t, std::ostream& os, const T& delimiter)
{
  os << tuple_head(t) << delimiter;

  tuple_print(tuple_tail(t), os, delimiter);
}

template<class Tuple>
void tuple_print(const Tuple& t, std::ostream& os = std::cout)
{
  tuple_print(t, os, ", ");
}

