#pragma once

#include <iostream>
#include <tuple>
#include <string>
#include "tuple_head.hpp"
#include "tuple_tail.hpp"

template<class Tuple>
typename std::enable_if<
  std::tuple_size<Tuple>::value == 0
>::type
tuple_print(std::ostream&, const Tuple& t, const std::string& = ", ")
{
}

template<class Tuple>
typename std::enable_if<
  std::tuple_size<Tuple>::value == 1
>::type
tuple_print(std::ostream& os, const Tuple& t, const std::string& = ", ")
{
  os << std::get<0>(t);
}

template<class Tuple>
typename std::enable_if<
  (std::tuple_size<Tuple>::value > 1)
>::type
  tuple_print(std::ostream& os, const Tuple& t, const std::string& delimiter = ", ")
{
  os << tuple_head(t) << delimiter;

  tuple_print(os, tuple_tail(t), delimiter);
}

