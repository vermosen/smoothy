#pragma once
#ifndef SMOOTHY_TRAITS_VALUE_H
#define SMOOTHY_TRAITS_VALUE_H

#include <Eigen/Dense>

#include <smoothy/traits/fwd/value.h>
#include <smoothy/traits/fwd/precision.h>
#include <smoothy/traits/fwd/dimension.h>

#include <smoothy/optimization/problem.h>

namespace smoothy   {
namespace traits    {

    template<typename Point>
    struct value {
        using type = Eigen::Matrix <
              typename traits::precision<Point>::type
            , traits::dimension<Point>::value, 1
        >;
    };

    template<
          template <class> class Func
        , class Criteria
        , class Point
        , template<class> class ... Traits
    >
    struct value<optimization::problem<Func, Criteria, Point, Traits...>> {
        using type = Eigen::Matrix <
            typename traits::precision<Point>::type
            , traits::dimension<Point>::value, 1
        >;
    };
}}

#endif
