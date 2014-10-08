#pragma once

#include <utility>
#include <tuple>
#include <type_traits>

template<class Tuple>
auto tuple_last(Tuple&& t)
  -> decltype(
       std::get<
         std::tuple_size<
           typename std::decay<Tuple>::type
         >::value - 1
       >(std::forward<Tuple>(t))
     )
{
  const size_t i = std::tuple_size<typename std::decay<Tuple>::type>::value - 1;
  return std::get<i>(std::forward<Tuple>(t));
}

