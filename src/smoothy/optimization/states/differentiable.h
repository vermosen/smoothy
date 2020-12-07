#pragma once
#ifndef SMOOTHY_OPTIMIZATION_STATES_DIFFERENTIABLE_H
#define SMOOTHY_OPTIMIZATION_STATES_DIFFERENTIABLE_H

#include <smoothy/definitions.h>

#include <smoothy/traits/fwd/problem.h>
#include <smoothy/traits/fwd/gradient.h>
#include <smoothy/traits/fwd/value.h>

namespace smoothy       {
namespace optimization  {
namespace states        {

  template<typename Child>
  class differentiable {
    using problem_type  = typename traits::problem<Child>::type;
    using value_type    = typename traits::value<problem_type>::type;
    using gradient_type = typename traits::gradient<problem_type>::type;

    void update(const value_type& pos) {
      // do something
    }

  public:
    gradient_type m_gradient;
    real m_gradientNorm;
  };
}}}

#endif // SMOOTHY_OPTIMIZATION_STATES_DIFFERENTIABLE_H
