#pragma once
#ifndef SMOOTHY_OPTIMIZATION_STATES_DIFFERENTIABLE_H
#define SMOOTHY_OPTIMIZATION_STATES_DIFFERENTIABLE_H

#include <smoothy/definitions.h>

#include <smoothy/traits/fwd/value.h>
#include <smoothy/traits/fwd/problem.h>

namespace smoothy       {
namespace optimization  {
namespace states        {

    template<typename Mixin>
    class differentiable {
        using problem_type = typename traits::problem<Mixin>::type;
    public:
        real m_gradientNorm;
        //typename problem_type::gradient_type m_gradient;
    };
}}}

#endif // SMOOTHY_OPTIMIZATION_STATES_DIFFERENTIABLE_H
