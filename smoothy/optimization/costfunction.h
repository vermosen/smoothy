#pragma once
#ifndef SMOOTHY_OPTIMIZATION_COST_FUNCTION_H
#define SMOOTHY_OPTIMIZATION_COST_FUNCTION_H

#include <smoothy/meta/patterns/curiouslyRecurring.h>
#include <smoothy/definitions.h>
#include <smoothy/traits/fwd/row.h>

namespace smoothy       {
namespace optimization  {

	template<
          template<class> class Func
        , class Val
    >
	class costFunction : public meta::curiouslyRecurring<Func<Val> > {
        using child = meta::curiouslyRecurring<Func<Val> >;
	public:
		typedef typename smoothy::traits::row<Val>::type arg_type;

        real operator()(const arg_type& x);
        real valueAndGradient(arg_type& grad, const arg_type& x);
        void gradient(arg_type& grad, const arg_type& x);

	protected:
        real valueAndGradientImpl(arg_type& grad, const arg_type& x);           // default implementations
	};

    template<
          template<class> class Func
        , class Val
    >
    inline real costFunction<Func, Val>::operator()(const arg_type& x) {
        return child::impl().valueImpl(x);
    }

    template<
          template<class> class Func
        , class Val
    >
    inline real costFunction<Func, Val>::valueAndGradient(arg_type& grad, const arg_type& x) {
        return child::impl().valueAndGradientImpl(grad, x);
    }

    template<
          template<class> class Func
        , class Val
    >
    inline void costFunction<Func, Val>::gradient(arg_type& grad, const arg_type& x) {
        return child::impl().gradientImpl(grad, x);
    }

    template<
          template<class> class Func
        , class Val
    >
    inline real costFunction<Func, Val>::valueAndGradientImpl(arg_type& grad, const arg_type& x) {
        child::impl().gradientImpl(grad, x);
        return child::impl().valueImpl();
    }
}}

#endif
