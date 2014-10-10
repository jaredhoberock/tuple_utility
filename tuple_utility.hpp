#pragma once

#include <tuple>
#include <utility>
#include <type_traits>
#include <integer_sequence>
#include <iostream>

// allow the user to define a namespace for these functions
#ifdef TUPLE_UTILITY_NAMESPACE
namespace TUPLE_UTILITY_NAMESPACE
{
#endif // TUPLE_UTILITY_NAMESPACE


template<class Tuple>
auto tuple_head(Tuple&& t)
  -> decltype(
       std::get<0>(std::forward<Tuple>(t))
     )
{
  return std::get<0>(std::forward<Tuple>(t));
}


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


template<class Tuple, class T>
typename std::enable_if<
  std::tuple_size<Tuple>::value == 0
>::type
tuple_print(const Tuple& t, std::ostream& os, const T&)
{
}

template<class Tuple, class T>
typename std::enable_if<
  std::tuple_size<Tuple>::value == 1
>::type
tuple_print(const Tuple& t, std::ostream& os, const T&)
{
  os << std::get<0>(t);
}

template<class Tuple, class T>
typename std::enable_if<
  (std::tuple_size<Tuple>::value > 1)
>::type
  tuple_print(const Tuple& t, std::ostream& os, const T& delimiter)
{
  os << tuple_head(t) << delimiter;

  tuple_print(tuple_tail(t), os, delimiter);
}

template<class Tuple>
void tuple_print(const Tuple& t, std::ostream& os = std::cout)
{
  tuple_print(t, os, ", ");
}


#ifdef TUPLE_UTILITY_NAMESPACE
} // close namespace
#endif // TUPLE_UTILITY_NAMESPACE

