#pragma once
#ifndef SMOOTHY_MATH_NORMS_L1_H
#define SMOOTHY_MATH_NORMS_L1_H

#include <smoothy/math/norms/details/base.h>

#include <smoothy/traits/fwd/dimension.h>
#include <smoothy/traits/fwd/value.h>
#include <smoothy/math/norm.h>

namespace smoothy {
namespace math    {

  template <typename Val>
  class norm<Val, norms::type::l1> : public norms::base<norm<Val, norms::type::l1>> {
  private:
    using ancestor = norms::base<norm<Val, norms::type::regularized>>;

  public:
    using typename precision_type = traits::precision<Val>::type;
    using typename value_type = traits::value<Val>::type;
    static_assert(traits::dimension<Val>::value == 1);

  public:
    static inline precision_type apply_impl(value_type vnew, value_type vold) {
      return (fnew - fold).abs();
    }
  };
}}

#endif
