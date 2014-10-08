#pragma once

#include <iostream>
#include <tuple>
#include "tuple_head.hpp"
#include "tuple_tail.hpp"

template<class Tuple, class T>
typename std::enable_if<
  std::tuple_size<Tuple>::value == 0
>::type
tuple_print(std::ostream&, const Tuple& t, const T&)
{
}

template<class Tuple, class T>
typename std::enable_if<
  std::tuple_size<Tuple>::value == 1
>::type
tuple_print(std::ostream& os, const Tuple& t, const T&)
{
  os << std::get<0>(t);
}

template<class Tuple, class T>
typename std::enable_if<
  (std::tuple_size<Tuple>::value > 1)
>::type
  tuple_print(std::ostream& os, const Tuple& t, const T& delimiter)
{
  os << tuple_head(t) << delimiter;

  tuple_print(os, tuple_tail(t), delimiter);
}

template<class Tuple>
void tuple_print(std::ostream& os, const Tuple& t)
{
  tuple_print(os, t, ", ");
}

