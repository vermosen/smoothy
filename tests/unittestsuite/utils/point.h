#pragma once

#include <boost/pfr.hpp>

#include <smoothy/traits/fwd/dimension.h>
#include <smoothy/traits/fwd/precision.h>

namespace smoothy::testsuite {

  template <
      typename T
    , unsigned Dim
  >
  struct point;

  template <>
  struct point<double, 2> {
    double m_x1;
    double m_x2;
  };

  template <>
  struct point<float, 3> {
    float m_x1;
    float m_x2;
    float m_x3;
  };
}

namespace smoothy::traits {

  template<typename T, unsigned Dim>
  struct precision<testsuite::point<T, Dim>> {
    using type = T;
  };

  template<typename T, unsigned Dim>
  struct dimension<testsuite::point<T, Dim>> {
    static constexpr unsigned value = Dim;
  };
}