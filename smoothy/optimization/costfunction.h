#pragma once
#ifndef SMOOTHY_OPTIMIZATION_COST_FUNCTION_H
#define SMOOTHY_OPTIMIZATION_COST_FUNCTION_H

#include <smoothy/meta/patterns/curiouslyrecurring.h>
#include <smoothy/definitions.h>

#include <smoothy/traits/fwd/value.h>
#include <smoothy/traits/fwd/gradient.h>

namespace smoothy       {
namespace optimization  {

    // TODO: the function has to implement traits (for example, being differentiable)
	template<
          template<class> class Func
        , class Point
    >
	class costFunction : public meta::curiouslyRecurring<Func<Point> > {
        using child = meta::curiouslyRecurring<Func<Point>>;
	public:
        using value_type = typename smoothy::traits::value<Point>::type;
        using gradient_type = typename smoothy::traits::gradient<Point>::type;

        real operator()(const value_type& x);
        real valueAndGradient(gradient_type& grad, const value_type& x);
        void gradient(gradient_type& grad, const value_type& x);

	protected:
        real valueAndGradientImpl(gradient_type& grad, const value_type& x);           // default implementations
	};

    template<
          template<class> class Func
        , class Point
    >
    inline real costFunction<Func, Point>::operator()(const value_type& x) {
        return child::impl().valueImpl(x);
    }

    template<
          template<class> class Func
        , class Point
    >
    inline real costFunction<Func, Point>::valueAndGradient(gradient_type& grad, const value_type& x) {
        return child::impl().valueAndGradientImpl(grad, x);
    }

    template<
          template<class> class Func
        , class Point
    >
    inline void costFunction<Func, Point>::gradient(gradient_type& grad, const value_type& x) {
        return child::impl().gradientImpl(grad, x);
    }

    template<
          template<class> class Func
        , class Point
    >
    inline real costFunction<Func, Point>::valueAndGradientImpl(gradient_type& grad, const value_type& x) {
        child::impl().gradientImpl(grad, x);
        return child::impl().valueImpl();
    }
}}

#endif
