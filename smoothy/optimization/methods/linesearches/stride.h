#pragma once
#ifndef SMOOTHY_OPTIMIZATION_METHODS_LINESEARCHES_STRIDE_H
#define SMOOTHY_OPTIMIZATION_METHODS_LINESEARCHES_STRIDE_H

#include <smoothy/definitions.h>
#include <smoothy/optimization/criterion.h>
#include <smoothy/meta/patterns/curiouslyrecurring.h>

#include <smoothy/traits/fwd/point.h>
#include <smoothy/traits/fwd/value.h>
#include <smoothy/traits/fwd/gradient.h>

namespace smoothy       {
namespace optimization  {
namespace lineSearches  {

	template<
          template <class> class Child
        , class Problem
	>
	class stride : public meta::curiouslyRecurring<Child<Problem> > {

        using child         = meta::curiouslyRecurring<Child<Problem>>  ;
        using point_type    = typename traits::point<Problem>::type     ;
        using value_type    = typename traits::value<Problem>::type     ;
        using gradient_type = typename traits::gradient<Problem>::type  ;

	public:
		stride(
			  real eps
			, size maxUpdate = 200)
			: m_maxUpdate(maxUpdate)
			, m_eps(eps) {}

		real eps() { return m_eps; }

		criteria::type operator()(
			  Problem& p
			, real& stride) {
			return child::impl().computeImpl(p, stride);
		}

        void direction(gradient_type& direction) { m_state.m_direction = direction; }

	protected:
        // TODO: reuse problem/state class
        struct state {
            gradient_type   m_direction ;
            value_type      m_x         ;
        } m_state;

    protected:
        state& current() { return m_state; }
        void current(state const& value) { m_state = value; }

        criteria::type try_update(							// here we are only testing whether the
			real& value/*, Constraint constraint*/ ) {		// stored step will violate the constraints

			value_type pos = m_state.m_x + value * m_state.m_direction;
            criteria::type result = criteria::type::none;
			/*result = constraint.test(new_params);*/

			integer count = 0;
			while (result != criteria::type::none) {
				if (count > m_maxUpdate)
					return criteria::type::maxIterations;
				value *= 0.5;
				count++;
				pos = m_state.m_x + value * m_state.m_direction;
				/*result = constraint.test(new_params);*/
			}

			m_state.m_x += value * m_state.m_direction;
			return result;
		}

	protected:
		size m_maxUpdate;					// max attempts to update the step
		real m_eps;							// tol
	};
}}}

#endif // SMOOTHY_OPTIMIZATION_METHODS_LINESEARCHES_STRIDE_H
