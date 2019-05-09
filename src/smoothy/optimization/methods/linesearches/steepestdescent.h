#pragma once
#ifndef SMOOTHY_OPTIMIZATION_METHODS_STEEPEST_DESCENT_H
#define SMOOTHY_OPTIMIZATION_METHODS_STEEPEST_DESCENT_H

#include <smoothy/optimization/methods/linesearch.h>

namespace smoothy       {
namespace optimization  {

	template<
		class Problem,
        template <class> class Stride
	>
	class steepestDescent : public lineSearch<Problem, Stride, steepestDescent> {

        using base = lineSearch<Problem, Stride, steepestDescent>;
        using value_type    = typename traits::value<Problem>::type;
		using gradient_type = typename traits::gradient<Problem>::type;

	public:
        steepestDescent(const Stride<Problem>& stride) : base(stride) {}

        gradient_type updateDirectionImpl(
			  Problem& p/*
			, real gold*/
			, gradient_type& x) {
			return -p.current().m_gradient;
		}
	};
}}

#endif // SMOOTHY_OPTIMIZATION_METHODS_STEEPEST_DESCENT_H
