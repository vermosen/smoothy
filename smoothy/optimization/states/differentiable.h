#pragma once
#ifndef SMOOTHY_OPTIMIZATION_STATES_DIFFERENTIABLE_H
#define SMOOTHY_OPTIMIZATION_STATES_DIFFERENTIABLE_H

#include <smoothy/definitions.h>

#include <smoothy/traits/fwd/point.h>
#include <smoothy/traits/fwd/problem.h>
#include <smoothy/traits/fwd/gradient.h>

namespace smoothy       {
namespace optimization  {
namespace states        {

    template<typename Mixin>
    class differentiable {
        using problem_type = typename traits::problem<Mixin>::type;
        using gradient_type = typename traits::gradient<problem_type>::type;

    public:
        gradient_type m_gradient;
        real m_gradientNorm;
    };
}}}

#endif // SMOOTHY_OPTIMIZATION_STATES_DIFFERENTIABLE_H
