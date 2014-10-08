#pragma once

#include <utility>
#include <tuple>
#include <integer_sequence>

template<class T, class Tuple, size_t... I>
T make_from_tuple_impl(const Tuple& t, std::index_sequence<I...>)
{
  return T{std::get<I>(t)...};
}

template<class T, class Tuple>
T make_from_tuple(const Tuple& t)
{
  return make_from_tuple_impl<T>(t, std::make_index_sequence<std::tuple_size<Tuple>::value>());
}

