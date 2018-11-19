#pragma once
#ifndef SMOOTHY_OPTIMIZATION_CRITERION_H
#define SMOOTHY_OPTIMIZATION_CRITERION_H

namespace smoothy       {
namespace optimization  {
namespace criteria      {

    enum class type {
          functionTolerance             = 1
        , maxIterations                 = 2
        , stationaryFunctionValue       = 3
        , stationaryFunctionAccuracy    = 4
        , zeroGradientNorm              = 5
        , maxStationaryState            = 6
        , none                          = 0
    };
}

    template <
        criteria::type Type
    >
    class criterion;
}}

#endif
