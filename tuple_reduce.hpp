#pragma once

#include "tuple_head.hpp"
#include "tuple_tail.hpp"

template<class Tuple, class T, class Function,
         class = typename std::enable_if<
           (std::tuple_size<
             typename std::decay<Tuple>::type
           >::value == 0)
         >::type>
T tuple_reduce(Tuple&&, T init, Function)
{
  return init;
}

template<class Tuple, class T, class Function,
         class = typename std::enable_if<
           (std::tuple_size<
             typename std::decay<Tuple>::type
           >::value > 0)
         >::type>
auto tuple_reduce(Tuple&& t, T init, Function f)
  -> decltype(
       f(
         tuple_head(std::forward<Tuple>(t)),
         tuple_reduce(tuple_tail(std::forward<Tuple>(t)), init, f)
       )
     )
{
  return f(
    tuple_head(std::forward<Tuple>(t)),
    tuple_reduce(tuple_tail(std::forward<Tuple>(t)), init, f)
  );
}

