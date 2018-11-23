#pragma once
#ifndef SMOOTHY_TRAITS_PROBLEM_H
#define SMOOTHY_TRAITS_PROBLEM_H

#include <smoothy/traits/fwd/problem.h>
#include <smoothy/optimization/state.h>

namespace smoothy   {
namespace traits    {

    template<
          typename Problem
        , template<class> class ... Mixins
    >
    struct problem<optimization::state<Problem, Mixins...>> {
        using type = Problem;
    };
}}

#endif
