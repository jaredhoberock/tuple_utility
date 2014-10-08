#pragma once

#include <tuple>
#include <utility>

template<class Tuple>
auto tuple_head(Tuple&& t)
  -> decltype(
       std::get<0>(std::forward<Tuple>(t))
     )
{
  return std::get<0>(std::forward<Tuple>(t));
}

