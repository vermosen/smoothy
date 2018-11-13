#pragma once
#ifndef OPTIMIZATION_CRITERIA_NORMS_DETAILS_BASE_H
#define OPTIMIZATION_CRITERIA_NORMS_DETAILS_BASE_H

#include <smoothy/definitions.h>

namespace smoothy   {
namespace math      {
namespace norms     {

    enum class type {
          l1
        , l2
        , regularized
    };
}

    template <typename Val, norms::type>
    class norm;
}}

#endif
