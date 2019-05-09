#pragma once
#ifndef SMOOTHY_TRAITS_POINT_H
#define SMOOTHY_TRAITS_POINT_H

#include <smoothy/traits/fwd/point.h>

#include <smoothy/optimization/problem.h>

namespace smoothy   {
namespace traits    {

    template<
          template <class> class Func
        , typename Criteria
        , typename Point
        , template<class> class ... Traits
    >
    struct point<optimization::problem<Func, Criteria, Point, Traits...>> {
        typedef Point type;
    };
}}

#endif
