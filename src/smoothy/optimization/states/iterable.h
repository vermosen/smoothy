#pragma once
#ifndef SMOOTHY_OPTIMIZATION_STATES_ITERABLE_H
#define SMOOTHY_OPTIMIZATION_STATES_ITERABLE_H

#include <smoothy/definitions.h>
#include <smoothy/traits/fwd/problem.h>
#include <smoothy/traits/fwd/value.h>

namespace smoothy       {
namespace optimization  {
namespace states        {

	template<typename Child>
  class iterable {
  public:
    using problem_type = typename traits::problem<Child>::type;
    using value_type = typename traits::value<problem_type>::type;
  public:
    
    void update(const value_type& pos) {
      // do something
    }

    size m_iterations;
    size m_stationaryStates;
  };
}}}

#endif // SMOOTHY_OPTIMIZATION_STATES_DIFFERENTIABLE_H
