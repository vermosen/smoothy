#include <tests/optimization.h>
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
        return suite;
    }

    template<class Val>
    struct rosenbrock : public opt::costFunction<rosenbrock, Val> {
    public:
        typedef typename opt::costFunction<rosenbrock, Val>::value_type value_type;

    public:
        rosenbrock(double a, double b) : m_a(a), m_b(b) {}

        real operator()(value_type const& x) {
            return std::pow(m_a - x(0, 0), 2) + m_b *
                std::pow(x(0, 1) - x(0, 0) * x(0, 0), 2);
        }

        real valueAndGradientImpl(value_type& grad, const value_type& x) {
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

    void optimization::rosenbrock_values() {

        BOOST_TEST_MESSAGE("testing line search method...");

        rosenbrock<point2d> func(1.0, 1.0);

        rosenbrock<point2d>::value_type gradient = rosenbrock<point2d>::value_type::Zero();
        rosenbrock<point2d>::value_type m_x = rosenbrock<point2d>::value_type::Zero();

        {
            m_x(0, 0) = 0.5; m_x(0, 1) = 0.5;
            auto res1 = func(m_x);
            auto res2 = func.valueAndGradient(gradient, m_x);
            BOOST_CHECK_CLOSE(res1, res2, T_TOL);
        }

        {
            m_x(0, 0) = 0.0; m_x(0, 1) = 1.0;
            auto res1 = func(m_x);
            auto res2 = func.valueAndGradient(gradient, m_x);
            BOOST_CHECK_CLOSE(res1, res2, T_TOL);
        }

        {
            m_x(0, 0) = 0.25; m_x(0, 1) = 0.75;
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

        using stride_type = lineSearches::strides::armijoGoldstein<problem_type>;

        rosenbrock<point2d> func(1.0, 1.0);
        criteria_type c({ 1e-8 }, { 1000 });
        point2d guess{ 0.5, -0.5 };
        problem_type p(func, c, guess);
        stride_type dir;
        real v = 0.0; dir(p, v);

        BOOST_CHECK_CLOSE(v, 1.025, T_TOL);
    }
}}
