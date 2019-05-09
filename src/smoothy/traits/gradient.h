#pragma once
#ifndef SMOOTHY_TRAITS_GRADIENT_H
#define SMOOTHY_TRAITS_GRADIENT_H

#include <smoothy/traits/fwd/value.h>
#include <smoothy/traits/fwd/gradient.h>
#include <smoothy/optimization/problem.h>

namespace smoothy   {
namespace traits    {

    template<typename Point>
    struct gradient {
        using type = typename value<Point>::type;
    };

    template<
          template <class> class Func
        , class Criteria
        , class Point
        , template<class> class ... Traits
    >
    struct gradient<smoothy::optimization::problem<Func, Criteria, Point, Traits...>> {
        using type = typename value<Point>::type;           // question: do we have a case when this is not true ?
    };
}}

#endif
