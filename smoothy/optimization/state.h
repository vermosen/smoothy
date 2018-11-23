#pragma once
#ifndef SMOOTHY_OPTIMIZATION_STATE_H
#define SMOOTHY_OPTIMIZATION_STATE_H

#include <smoothy/definitions.h>
#include <smoothy/meta/patterns/curiousmixin.h>
#include <smoothy/traits/fwd/value.h>

namespace smoothy       {
namespace optimization  {

	// current state of an optimization problem
	template<typename Problem, template<class> class ... Mixins>
    class state : public meta::curiousMixin<state<Problem, Mixins...>, Mixins...>{
    public:
        real m_f;
        typename traits::value<Problem>::type m_x;
    };
}}

#endif
