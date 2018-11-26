#pragma once
#ifndef SMOOTHY_OPTIMIZATION_METHODS_LINESEARCHES_STRIDES_ARMIJO_GOLDBERG_H
#define SMOOTHY_OPTIMIZATION_METHODS_LINESEARCHES_STRIDES_ARMIJO_GOLDBERG_H

#include <smoothy/optimization/methods/linesearches/stride.h>

namespace smoothy       {
namespace optimization  {
namespace lineSearches  {
namespace strides       {

	template<class Problem>
	class armijoGoldstein : public stride<armijoGoldstein, Problem> {
	private:
        using base = stride<armijoGoldstein, Problem>;

	public:
		armijoGoldstein(
		  real eps      = 1e-8
		, real alpha    = 0.05
		, real beta     = 0.65
		, size maxIter  = 200);

	protected:
		friend base;

        criteria::type computeImpl(
			  Problem& p
			, real& value);

    private:
		real m_alpha;
		real m_beta;
	};

    template<class Problem>
    armijoGoldstein<Problem>::armijoGoldstein(
          real eps, real alpha, real beta, size maxIter)
        : base(eps, maxIter )
        , m_alpha(alpha     )
        , m_beta(beta       ) {}

	template<class Problem>
	criteria::type armijoGoldstein<Problem>::computeImpl(
		  Problem& p
		, real& value) {

		// Constraint& constraint = P.constraint();
		auto& current = base::current();
		real qtold, t = value;
		size iter = 0;

		real f0 = p.current().m_f;
		real nD0 = p.current().m_gradientNorm;
        criteria::type res = criteria::type::none;

		real norm = current.m_direction.dot(
			current.m_direction);

		res = base::try_update(t/*, constraint*/);		// bondary check !!! this is computing a new m_x

		if (res != criteria::type::none)
			return res;

		real f = (p.function())(current.m_x);		// initial value

		if ((f - f0) > -t * m_alpha * norm) {
			do {
				iter++;
				t *= m_beta;							    // decrease step
				qtold = f;								    // store old value of the function
				current.m_x = p.current().m_x;			    // back to the initial position
				res = base::try_update(t/*, constraint*/);	// bondary check with new t + update x
				f = (p.function())(current.m_x);		    // compute f at the new point
			} while (
				   (((f - f0) > (-m_alpha * t * norm))
				|| ((qtold - f0) <= (-m_alpha * t * norm / m_beta)))
				&& (res == criteria::type::none)
				&& (iter < base::m_maxUpdate)
			);
		}

		value = t;

		if (iter == base::m_maxUpdate)
			return criteria::type::maxIterations;
		else
			return res;
	}
}}}}

#endif
