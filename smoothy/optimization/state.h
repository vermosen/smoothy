#pragma once
#ifndef SMOOTHY_OPTIMIZATION_STATE_H
#define SMOOTHY_OPTIMIZATION_STATE_H

#include <smoothy/definitions.h>

#include <smoothy/traits/fwd/value.h>

namespace smoothy       {
namespace optimization  {

	// current state of an optimization problem
	template<typename Problem, template<class> class ... Mixins>
    struct state : public Mixins<state>... {

        state();

        real m_f;
        typename traits::value<Problem>::type m_x;
        size m_iterations;
    };

    template<typename Problem, template<class> class ... Mixins>
    inline state<Problem, Mixins ...>::state() : Mixins<state>()... {}
}}

#endif
