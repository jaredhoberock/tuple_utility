#pragma once

#include <tuple>
#include <integer_sequence>
#include <type_traits>
#include <utility>

template<size_t I, typename Function, typename... Tuples>
auto __tuple_map_invoke(Function f, Tuples&&... ts)
  -> decltype(
       f(std::get<I>(std::forward<Tuples>(ts))...)
     )
{
  return f(std::get<I>(std::forward<Tuples>(ts))...);
}

template<size_t... I, typename Function1, typename Function2, typename... Tuples>
auto __tuple_map_with_make_impl(std::index_sequence<I...>, Function1 f, Function2 make, Tuples&&... ts)
  -> decltype(
       make(
         __tuple_map_invoke<I>(f, std::forward<Tuples>(ts)...)...
       )
     )
{
  return make(
    __tuple_map_invoke<I>(f, std::forward<Tuples>(ts)...)...
  );
}

template<typename Function1, typename Function2, typename Tuple, typename... Tuples>
auto tuple_map_with_make(Function1 f, Function2 make, Tuple&& t, Tuples&&... ts)
  -> decltype(
       __tuple_map_with_make_impl(
         std::make_index_sequence<
           std::tuple_size<std::decay_t<Tuple>>::value
         >(),
         f,
         make,
         std::forward<Tuple>(t),
         std::forward<Tuples>(ts)...
       )
     )
{
  return __tuple_map_with_make_impl(
    std::make_index_sequence<
      std::tuple_size<std::decay_t<Tuple>>::value
    >(),
    f,
    make,
    std::forward<Tuple>(t),
    std::forward<Tuples>(ts)...
  );
}

struct __tuple_maker
{
  template<class... T>
  auto operator()(T&&... args)
    -> decltype(
         std::make_tuple(std::forward<T>(args)...)
       )
  {
    return std::make_tuple(std::forward<T>(args)...);
  }
};

template<typename Function, typename Tuple, typename... Tuples>
auto tuple_map(Function f, Tuple&& t, Tuples&&... ts)
  -> decltype(
       tuple_map_with_make(f, __tuple_maker(), std::forward<Tuple>(t), std::forward<Tuples>(ts)...)
     )
{
  return tuple_map_with_make(f, __tuple_maker(), std::forward<Tuple>(t), std::forward<Tuples>(ts)...);
}

