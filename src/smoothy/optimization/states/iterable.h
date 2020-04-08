#pragma once
#ifndef SMOOTHY_OPTIMIZATION_STATES_ITERABLE_H
#define SMOOTHY_OPTIMIZATION_STATES_ITERABLE_H

#include <smoothy/definitions.h>
#include <smoothy/traits/fwd/problem.h>

namespace smoothy       {
namespace optimization  {
namespace states        {

	template<typename Mixin>
  class iterable {
    using problem_type = typename traits::problem<Mixin>::type;
  public:
    size m_iterations;
    size m_stationaryStates;
  };
}}}

#endif // SMOOTHY_OPTIMIZATION_STATES_DIFFERENTIABLE_H
