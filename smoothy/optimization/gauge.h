#pragma once
#ifndef SMOOTHY_OPTIMIZATION_GAUGE_H
#define SMOOTHY_OPTIMIZATION_GAUGE_H

#include <smoothy/optimization/criterion.h>

namespace smoothy       {
namespace optimization  {

    template <typename State, criteria::type ... Type>
    struct gauge;

    template <
          typename State
        , criteria::type First
        , criteria::type ... Rest
    >
    struct gauge<State, First, Rest...> : public criterion<First>
                                        , public gauge<State, Rest...> {

        gauge(const typename criterion<First >::pack& first
            , const typename criterion<Rest  >::pack&... rest...)
            : gauge<State, Rest...>(rest...), criterion<First>(first) {}

        criteria::type apply(State& from, State& to) {
            if (criterion<First>::template apply<State>(from, to)) {
                return gauge<State, Rest...>::apply(from, to);
            }
            else {
                return First;
            }
        }
    };

    template <
          typename State
        , criteria::type First
    >
    struct gauge<State, First> : public criterion<First> {

        gauge(const typename criterion<First>::pack& first)
            : criterion<First>(first) {}

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
