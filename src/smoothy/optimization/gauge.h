#pragma once
#ifndef SMOOTHY_OPTIMIZATION_GAUGE_H
#define SMOOTHY_OPTIMIZATION_GAUGE_H

#include <smoothy/optimization/criterion.h>

namespace smoothy      {
namespace optimization {

  template <criteria::type ... Type>
  struct gauge;

  template <
    criteria::type First
    , criteria::type ... Rest
  >
    struct gauge<First, Rest...> : public criterion<First>
    , public gauge<Rest...> {

    gauge(const typename criterion<First >::pack& first
      , const typename criterion<Rest  >::pack&... rest...)
      : gauge<Rest...>(rest...), criterion<First>(first) {}

    template <typename State>
    criteria::type apply(State& from, State& to) {
      if (criterion<First>::template apply<State>(from, to)) {
        return gauge<Rest...>::template apply<State>(from, to);
      }
      else {
        return First;
      }
    }
  };

  template <criteria::type First>
  struct gauge<First> : public criterion<First> {

    gauge(const typename criterion<First>::pack& first)
      : criterion<First>(first) {}

    template <typename State>
    criteria::type apply(State& from, State& to) {
      if (criterion<First>::template apply<State>(from, to)) {
        return criteria::type::none;
      }
      else {
        return First;
      }
    }
  };
}}

#endif
