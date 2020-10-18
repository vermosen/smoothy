#pragma once
#ifndef SMOOTHY_OPTIMIZATION_COST_FUNCTION_H
#define SMOOTHY_OPTIMIZATION_COST_FUNCTION_H

#include <smoothy/definitions.h>
#include <smoothy/traits/value.h>
#include <smoothy/traits/fwd/gradient.h>

namespace smoothy       {
namespace optimization  {

    // TODO: the function has to implement traits (for example, being differentiable)
	template<
      template<class> class Func
    , class Point
  >
	class costFunction {
    using child = Func<Point>;
	public:
    using value_type = typename smoothy::traits::value<Point>::type;
    using gradient_type = typename smoothy::traits::gradient<Point>::type;

  public:
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
  real costFunction<Func, Point>::operator()(const value_type& x) {
    return static_cast<child&>(*this).valueImpl(x);
  }

  template<
      template<class> class Func
    , class Point
  >
  real costFunction<Func, Point>::valueAndGradient(gradient_type& grad, const value_type& x) {
    return static_cast<child&>(*this).valueAndGradientImpl(grad, x);
  }

  template<
      template<class> class Func
    , class Point
  >
  void costFunction<Func, Point>::gradient(gradient_type& grad, const value_type& x) {
    return static_cast<child&>(*this).gradientImpl(grad, x);
  }

  template<
      template<class> class Func
    , class Point
  >
  real costFunction<Func, Point>::valueAndGradientImpl(gradient_type& grad, const value_type& x) {
    child::gradientImpl(grad, x);
    return static_cast<child&>(*this).valueImpl();
  }
}}

#endif
