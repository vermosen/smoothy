#pragma once

#include <boost/pfr.hpp>

namespace smoothy   {
namespace testsuite {

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

}}