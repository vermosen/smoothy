#include <tests/optimization.h>

#include <Eigen/Dense>

#include <definitions.h>

#include <smoothy/definitions.h>
#include <smoothy/traits/problem.h>
#include <smoothy/traits/point.h>
#include <smoothy/traits/gradient.h>

#include <smoothy/optimization/gauge.h>
#include <smoothy/optimization/problem.h>
#include <smoothy/optimization/state.h>
#include <smoothy/optimization/costfunction.h>
#include <smoothy/optimization/criteria/functiontolerance.h>
#include <smoothy/optimization/criteria/maxiteration.h>
#include <smoothy/optimization/states/iterable.h>
#include <smoothy/optimization/states/differentiable.h>

#include <smoothy/optimization/methods/linesearches/strides/armijogoldstein.h>
#include <smoothy/optimization/methods/linesearches/steepestdescent.h>

#include <smoothy/utils/adapter.h>

SMOOTHY_DATA_ADAPTER(
      smoothy::testSuite::point2d
    , double, m_x1, m_x2
);

SMOOTHY_DATA_ADAPTER(
      smoothy::testSuite::point3d
    , float, m_x1, m_x2, m_x3
);

namespace smoothy   {
namespace testSuite {

    namespace opt = smoothy::optimization;

    boost::unit_test_framework::test_suite* optimization::suite() {
        boost::unit_test_framework::test_suite* suite = BOOST_TEST_SUITE("optimization");
        suite->add(BOOST_TEST_CASE(&optimization::rosenbrock_values     ), 0, MAX_TIME_SEC);
        suite->add(BOOST_TEST_CASE(&optimization::set_criteria          ), 0, MAX_TIME_SEC);
        suite->add(BOOST_TEST_CASE(&optimization::set_problem           ), 0, MAX_TIME_SEC);
        suite->add(BOOST_TEST_CASE(&optimization::armijogoldstein_stride), 0, MAX_TIME_SEC);
        suite->add(BOOST_TEST_CASE(&optimization::steepest_descent      ), 0, MAX_TIME_SEC);
        return suite;
    }

    template<class Val>
    struct rosenbrock : public opt::costFunction<rosenbrock, Val> {
    public:
        using value_type = typename opt::costFunction<rosenbrock, Val>::value_type;
        using gradient_type = typename opt::costFunction<rosenbrock, Val>::gradient_type;

    public:
        rosenbrock(double a, double b) : m_a(a), m_b(b) {}

        real operator()(value_type const& x) {
            return std::pow(m_a - x(0, 0), 2) + m_b *
                std::pow(x(1, 0) - x(0, 0) * x(0, 0), 2);
        }

        real valueAndGradientImpl(gradient_type& grad, const value_type& x) {
            this->gradientImpl(grad, x);
            return grad(1, 0) * grad(1, 0) / (4 * m_b) + std::pow(m_a - x(0, 0), 2.0);
        }

        void gradientImpl(gradient_type& grad, const value_type& x) {
            grad(1, 0) = 2 * m_b * (x(1, 0) - x(0, 0) * x(0, 0));
            grad(0, 0) = x(0, 0) * (2.0 * (x(0, 0) - m_a) - grad(1, 0));
        }

        double m_a;
        double m_b;
    };

    void optimization::rosenbrock_values() {

        BOOST_TEST_MESSAGE("testing line search method...");

        rosenbrock<point2d> func(1.0, 1.0);

        rosenbrock<point2d>::value_type gradient = rosenbrock<point2d>::value_type::Zero();
        rosenbrock<point2d>::value_type m_x = rosenbrock<point2d>::value_type::Zero();

        {
            m_x(0, 0) = 0.5; m_x(1, 0) = 0.5;
            auto res1 = func(m_x);
            auto res2 = func.valueAndGradient(gradient, m_x);
            BOOST_CHECK_CLOSE(res1, res2, T_TOL);
        }

        {
            m_x(0, 0) = 0.0; m_x(1, 0) = 1.0;
            auto res1 = func(m_x);
            auto res2 = func.valueAndGradient(gradient, m_x);
            BOOST_CHECK_CLOSE(res1, res2, T_TOL);
        }

        {
            m_x(0, 0) = 0.25; m_x(1, 0) = 0.75;
            auto res1 = func(m_x);
            auto res2 = func.valueAndGradient(gradient, m_x);
            BOOST_CHECK_CLOSE(res1, res2, T_TOL);
        }
    }

    void optimization::set_criteria() {
        using namespace smoothy::optimization;

        using criteria_type = gauge<
              criteria::type::functionTolerance
            , criteria::type::maxIterations
        >;

        criteria_type c({ 1e-8 }, { 1000 });
    }

    void optimization::set_problem() {
        using namespace smoothy::optimization;

        using criteria_type = gauge<
              criteria::type::functionTolerance
            , criteria::type::maxIterations
        >;

        using value_type = point2d;

        using problem_type = problem<
              rosenbrock
            , criteria_type
            , value_type
            , states::iterable
            , states::differentiable
        >;

        rosenbrock<point2d> func(1.0, 1.0);
        criteria_type c({ 1e-8 }, { 1000 });
        point2d guess{ 1.0, 1.0 };
        problem_type p(func, c, guess);
    }

    void optimization::armijogoldstein_stride() {

        using namespace smoothy::optimization;

        using criteria_type = gauge<
              criteria::type::functionTolerance
            , criteria::type::maxIterations
        >;

        using value_type = point2d;

        using problem_type = problem<
              rosenbrock
            , criteria_type
            , value_type
            , states::iterable
            , states::differentiable
        >;

        using stride_type = strides::armijoGoldstein<problem_type>;

        rosenbrock<point2d> func(1.0, 1.0);
        criteria_type c({ 1e-8 }, { 1000 });
        point2d guess{ 0.5, -0.5 };
        problem_type p(func, c, guess);
        stride_type stride;

        Eigen::Matrix<smoothy::real, 2, 1> dir;     // set the current direction
        dir(0, 0) = 0.1; dir(1, 0) = 0.1;
        stride.direction(dir);
        real step = 1.0;                            // set the currrent step size
        auto res = stride(p, step);

        BOOST_CHECK_CLOSE(step, 0.0, T_TOL);        // here it's optimal to stay in place...
    }

    void optimization::steepest_descent() {

        using namespace smoothy::optimization;

        using criteria_type = gauge<
              criteria::type::functionTolerance
            , criteria::type::maxIterations
        >;

        using value_type = point2d;

        using problem_type = problem<
              rosenbrock
            , criteria_type
            , value_type
            , states::iterable
            , states::differentiable
        >;

        using stride_type = strides::armijoGoldstein<problem_type>;
        using method_type = steepestDescent<problem_type, strides::armijoGoldstein>;

        rosenbrock<point2d> func(1.0, 1.0);
        criteria_type c({ 1e-8 }, { 1000 });
        point2d guess{ 0.5, -0.5 };
        problem_type p(func, c, guess);
        stride_type stride;
        method_type optimizer(stride);

        Eigen::Matrix<smoothy::real, 2, 1> dir;     // set the current direction
        dir(0, 0) = 0.1; dir(1, 0) = 0.1;
        stride.direction(dir);
        real step = 1.0;                            // set the currrent step size
        auto res = stride(p, step);

        BOOST_CHECK_CLOSE(step, 0.0, T_TOL);        // here it's optimal to stay in place...
    }
}}
