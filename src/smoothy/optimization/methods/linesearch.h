#pragma once
#ifndef SMOOTHY_OPTIMIZATION_METHODS_LINE_SEARCH_H
#define SMOOTHY_OPTIMIZATION_METHODS_LINE_SEARCH_H

#include <smoothy/definitions.h>

#include <smoothy/traits/fwd/value.h>
#include <smoothy/traits/fwd/gradient.h>
#include <smoothy/optimization/criterion.h>

#include <smoothy/meta/patterns/curiouslyrecurring.h>

namespace smoothy       {
namespace optimization  {

	template<
		class Problem,                  // TODO: we don't need direct access to the problem here (traits)
		template <class> class Stride,
		template <class, template <class> class> class Child
	>
	class lineSearch : public meta::curiouslyRecurring<Child<Problem, Stride>> {
        using child = meta::curiouslyRecurring<Child<Problem, Stride>>;
        using array_type    = typename traits::value<Problem>::type;
		using gradient_type = typename traits::gradient<Problem>::type;

	public:
		lineSearch(const Stride<Problem>& stride)
			: m_stride(stride) {}

		criteria::type minimize(Problem& p);

	protected:
		array_type updateDirection(
			  Problem& p/*
			, real gold */
			, gradient_type& previous) {
			return child::impl().updateDirectionImpl(p/*, gold*/, previous);
		}

		Stride<Problem> m_stride;
	};

	template<
		class Problem,
		template <class> class Stride,
		template <class, template <class> class> class Child
	>
    criteria::type lineSearch<Problem, Stride, Child>::minimize(Problem& p) {

		criteria::type result = criteria::type::none;		// no criteria reached
		real t = 1.0;										// initial line search value
		auto& state = p.current();							// aliases
		auto& step = m_stride.current();

		// initial state initialization
		state.m_f = p.function().valueAndGradient(			// store the gradient and the function value
			state.m_gradient, state.m_x);
		state.m_gradientNorm = state.m_gradient.dot(		// store the gradient norm
			state.m_gradient);

		auto old = state;						            // copy the state
		step.m_x = state.m_x;					            // set the line search initial position
		step.m_direction = -state.m_gradient;	            // set the initial direction (steepest descent)
		gradient_type dir;						            // copy the direction

		for (;;) {
			dir = step.m_direction;

			result = (m_stride)(p, t);

			if ((m_stride)(p, t) != criteria::type::none)
				return result;

			state.m_x = step.m_x;							// update the state
			state.m_f = p.function().valueAndGradient(
				state.m_gradient, state.m_x);
			state.m_gradientNorm = state.m_gradient.dot(
				state.m_gradient);
			state.m_iterations++;

			// check stopping conditions
			p.criteria().check_all(old, p.current(), result);

			if (result != criteria::type::none)
				return result;

			old = state;							// update problem values with cached data
			step.m_x = state.m_x;					// set the line search initial position
			step.m_direction = updateDirection(		// update the direction
				p, dir);
		}
	}
}}

#endif
