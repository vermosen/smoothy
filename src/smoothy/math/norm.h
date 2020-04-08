#pragma once
#ifndef OPTIMIZATION_CRITERIA_NORM_H
#define OPTIMIZATION_CRITERIA_NORM_H

#include <smoothy/definitions.h>

namespace smoothy   {
namespace math      {
namespace norms     {

  enum class type {
      l1          = 1
    , l2          = 2
    , regularized = 3
  };
}

  template <typename Val, norms::type>
  class norm;
}}

#endif
