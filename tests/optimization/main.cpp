
#include <gtest/gtest.h>

#include "point.h"

#include <smoothy/optimization/gauge.h>
#include <smoothy/optimization/problem.h>
#include <smoothy/optimization/state.h>
#include <smoothy/optimization/costfunction.h>
#include <smoothy/optimization/criteria/functiontolerance.h>
#include <smoothy/optimization/criteria/maxiteration.h>
#include <smoothy/optimization/states/iterable.h>
#include <smoothy/optimization/states/differentiable.h>

#include <smoothy/traits/problem.h>
#include <smoothy/traits/point.h>

#include <smoothy/optimization/methods/linesearches/strides/armijogoldstein.h>

namespace opt = smoothy::optimization;

template<class Val>
struct rosenbrock : public opt::costFunction<rosenbrock, Val> {
public:
  using value_type = typename opt::costFunction<rosenbrock, Val>::value_type;

public:
  rosenbrock(double a, double b) : m_a(a), m_b(b) {}

  smoothy::real operator()(value_type const& x) {
    return std::pow(m_a - x(0, 0), 2) + m_b *
      std::pow(x(0, 1) - x(0, 0) * x(0, 0), 2);
  }

  smoothy::real valueAndGradientImpl(value_type& grad, const value_type& x) {
    this->gradientImpl(grad, x);
    return grad(0, 1) * grad(0, 1) / (4 * m_b) + std::pow(m_a - x(0, 0), 2.0);
  }

  void gradientImpl(value_type& grad, const value_type& x) {
    grad(0, 1) = 2 * m_b * (x(0, 1) - x(0, 0) * x(0, 0));
    grad(0, 0) = x(0, 0) * (2.0 * (x(0, 0) - m_a) - grad(0, 1));
  }

  double m_a;
  double m_b;
};

//default test tolerance
#define T_TOL 10e-8

// default test timeout
#define MAX_TIME_SEC 300

TEST(unittest, create_rosenbrock) {

  using data_type = point<double, 2>;

  rosenbrock<data_type> func(1.0, 1.0);

  rosenbrock<data_type>::value_type gradient = rosenbrock<data_type>::value_type::Zero();
  rosenbrock<data_type>::value_type m_x = rosenbrock<data_type>::value_type::Zero();

  {
    m_x(0, 0) = 0.5; m_x(0, 1) = 0.5;
    auto res1 = func(m_x);
    auto res2 = func.valueAndGradient(gradient, m_x);
    EXPECT_NEAR(res1, res2, T_TOL);
  }

  {
    m_x(0, 0) = 0.0; m_x(0, 1) = 1.0;
    auto res1 = func(m_x);
    auto res2 = func.valueAndGradient(gradient, m_x);
    EXPECT_NEAR(res1, res2, T_TOL);
  }

  {
    m_x(0, 0) = 0.25; m_x(0, 1) = 0.75;
    auto res1 = func(m_x);
    auto res2 = func.valueAndGradient(gradient, m_x);
    EXPECT_NEAR(res1, res2, T_TOL);
  }
}

TEST(unittest, set_criteria) {

  using namespace smoothy::optimization;

  using criteria_type = gauge<
      criteria::type::functionTolerance
    , criteria::type::maxIterations
  >;

  criteria_type c({ 1e-8 }, { 1000 });
}

TEST(unittest, set_problem) {

  using namespace smoothy::optimization;

  using criteria_type = gauge<
    criteria::type::functionTolerance
    , criteria::type::maxIterations
  >;

  using value_type = point<double, 2>;

  using problem_type = problem<
    rosenbrock
    , criteria_type
    , value_type
    , states::iterable
    , states::differentiable
  >;

  rosenbrock<value_type> func(1.0, 1.0);
  criteria_type c({ 1e-8 }, { 1000 });
  value_type guess{ 1.0, 1.0 };
  problem_type p(func, c, guess);
}

TEST(unittest, armijogoldstein_stride) {

  using namespace smoothy::optimization;

  using criteria_type = gauge<
    criteria::type::functionTolerance
    , criteria::type::maxIterations
  >;

  using value_type = point<double, 2>;

  using problem_type = problem<
    rosenbrock
    , criteria_type
    , value_type
    , states::iterable
    , states::differentiable
  >;

  using stride_type = opt::strides::armijoGoldstein<problem_type>;

  rosenbrock<value_type> func(1.0, 1.0);
  criteria_type c({ 1e-8 }, { 1000 });
  value_type guess{ 0.5, -0.5 };
  problem_type p(func, c, guess);
  stride_type dir;
  smoothy::real v = 0.0; dir(p, v);

  EXPECT_NEAR(v, 1.025, T_TOL);
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
