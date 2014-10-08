#pragma once

#include <tuple>
#include <utility>
#include "tuple_take.hpp"

template<size_t N, class Tuple>
auto tuple_drop(Tuple&& t)
  -> decltype(
       tuple_take<std::tuple_size<typename std::decay<Tuple>::type>::value - N>(std::forward<Tuple>(t))
     )
{
  return tuple_take<std::tuple_size<typename std::decay<Tuple>::type>::value - N>(std::forward<Tuple>(t));
}

template<class Tuple>
auto tuple_drop_last(Tuple&& t)
  -> decltype(
       tuple_drop<1>(std::forward<Tuple>(t))
     )
{
  return tuple_drop<1>(std::forward<Tuple>(t));
}

