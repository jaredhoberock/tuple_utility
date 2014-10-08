#pragma once

#include <tuple>
#include <utility>
#include <integer_sequence>

template<class Tuple, class T, size_t... I>
auto __tuple_append_impl(Tuple&& t, T&& x, std::index_sequence<I...>)
  -> decltype(
       std::make_tuple(std::get<I>(std::forward<Tuple>(t))..., std::forward<T>(x))
     )
{
  return std::make_tuple(std::get<I>(std::forward<Tuple>(t))..., std::forward<T>(x));
}

template<class Tuple, class T>
auto tuple_append(Tuple&& t, T&& x)
  -> decltype(
       __tuple_append_impl(
         std::forward<Tuple>(t),
         std::forward<T>(x),
         std::make_index_sequence<
           std::tuple_size<
             typename std::decay<Tuple>::type
           >::value
         >()
       )
     )
{
  using indices = std::make_index_sequence<
    std::tuple_size<typename std::decay<Tuple>::type>::value
  >;
  return __tuple_append_impl(std::forward<Tuple>(t), std::forward<T>(x), indices());
}

