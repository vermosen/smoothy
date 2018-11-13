#pragma once
#ifndef SMOOTHY_MATH_NORMS_L1_H
#define SMOOTHY_MATH_NORMS_L1_H

#include <smoothy/math/norms/details/base.h>

#include <smoothy/traits/fwd/dimension.h>
#include <smoothy/traits/fwd/row.h>
#include <smoothy/math/norm.h>

namespace smoothy   {
namespace math      {

    template <typename Val>
    class norm<Val, norms::type::l1> : public norms::base<norm<Val, norms::type::l1>> {

        using ancestor = norms::base<norm<Val, norms::type::regularized>>;
        using typename precision_type = traits::precision<Val>::type;
        using typename row_type = traits::row<Val>::type;
        static_assert(traits::dimension<Val>::value == 1);

    public:
        static inline precision_type applyImpl(row_type vnew, row_type vold) {
            return (fnew - fold).abs();
        }
    };
}}

#endif
