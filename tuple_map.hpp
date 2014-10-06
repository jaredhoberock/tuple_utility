#pragma once

#include <tuple>
#include <integer_sequence>
#include <type_traits>
#include <utility>

template<class Tuple, class Function1, class Function2, size_t... I>
auto tuple_map_impl(Tuple&& t, Function1 f, Function2 make, std::index_sequence<I...>)
  -> decltype(
       make(
         f(std::get<I>(std::forward<Tuple>(t)))...
       )
     )
{
  return make(
    f(std::get<I>(std::forward<Tuple>(t)))...
  );
}

template<class Tuple, class Function1, class Function2>
auto tuple_map(Tuple&& t, Function1 f, Function2 make)
  -> decltype(
       tuple_map_impl(
         std::forward<Tuple>(t),
         f,
         make,
         std::make_index_sequence<
           std::tuple_size<std::decay_t<Tuple>>::value
         >()
       )
     )
{
  using indices = std::make_index_sequence<
    std::tuple_size<std::decay_t<Tuple>>::value
  >;
  return tuple_map_impl(std::forward<Tuple>(t), f, make, indices());
}

struct make_tuple_functor
{
  template<class... Types>
  auto operator()(Types&&... args)
    -> decltype(
         std::make_tuple(std::forward<Types>(args)...)
       )
  {
    return std::make_tuple(std::forward<Types>(args)...);
  }
};

template<class Tuple, class Function>
auto tuple_map(Tuple&& t, Function f)
  -> decltype(
       tuple_map(
         std::forward<Tuple>(t),
         f,
         make_tuple_functor()
       )
     )
{
  return tuple_map(std::forward<Tuple>(t), f, make_tuple_functor());
}

