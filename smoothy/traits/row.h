#pragma once
#ifndef SMOOTHY_TRAITS_ROW_H
#define SMOOTHY_TRAITS_ROW_H

#include <Eigen/Dense>

#include <smoothy/traits/fwd/row.h>
#include <smoothy/traits/fwd/precision.h>
#include <smoothy/traits/fwd/dimension.h>

namespace smoothy   {
namespace traits    {

    template<typename Val>
    struct row {
        using type = Eigen::Matrix <
              typename traits::precision<Val>::type
            , 1, traits::dimension<Val>::value
        >;
    };
}}

#endif
