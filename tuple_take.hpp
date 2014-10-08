#pragma once

#include <tuple>
#include <utility>
#include <integer_sequence>

template<size_t... I, class Tuple>
auto __tuple_take_impl(Tuple&& t, std::index_sequence<I...>)
  -> decltype(
       std::tie(
         std::get<I>(std::forward<Tuple>(t))...
       )
     )
{
  return std::tie(std::get<I>(std::forward<Tuple>(t))...);
}

template<size_t N, class Tuple>
auto tuple_take(Tuple&& t)
  -> decltype(
       __tuple_take_impl(std::forward<Tuple>(t), std::make_index_sequence<N>())
     )
{
  return __tuple_take_impl(std::forward<Tuple>(t), std::make_index_sequence<N>());
}

