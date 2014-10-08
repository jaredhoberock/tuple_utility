#pragma once

#include <tuple>
#include <utility>

template<class... Args>
auto __tuple_tail_impl_impl(Args&&... args)
  -> decltype(
       std::forward_as_tuple(args...)
     )
{
  return std::forward_as_tuple(args...);
}

template<class Tuple, size_t... I>
auto __tuple_tail_impl(Tuple&& t, std::index_sequence<I...>)
  -> decltype(
       __tuple_tail_impl_impl(std::get<I>(std::forward<Tuple>(t))...)
     )
{
  return __tuple_tail_impl_impl(std::get<I+1>(std::forward<Tuple>(t))...);
}

template<class Tuple>
auto tuple_tail(Tuple&& t)
  -> decltype(
       __tuple_tail_impl(
         std::forward<Tuple>(t),
         std::make_index_sequence<
           std::tuple_size<
             typename std::decay<Tuple>::type
           >::value - 1
         >()
       )
     )
{
  using indices = std::make_index_sequence<
    std::tuple_size<
      typename std::decay<Tuple>::type
    >::value - 1
  >;
  return __tuple_tail_impl(std::forward<Tuple>(t), indices());
}

