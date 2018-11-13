#include <tests/optimization.h>
#include <definitions.h>

#include <smoothy/definitions.h>
#include <smoothy/optimization/costfunction.h>
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
        suite->add(BOOST_TEST_CASE(&optimization::helloworld), 0, MAX_TIME_SEC);
        suite->add(BOOST_TEST_CASE(&optimization::rosenbrock_values), 0, MAX_TIME_SEC);
        return suite;
    }

    template<class Val>
    struct rosenbrock : public opt::costFunction<rosenbrock, Val> {
    public:
        typedef typename opt::costFunction<rosenbrock, Val>::arg_type arg_type;

    public:
        rosenbrock(double a, double b) : m_a(a), m_b(b) {}

        real operator()(arg_type const& x) {
            return std::pow(m_a - x(0, 0), 2) + m_b *
                std::pow(x(0, 1) - x(0, 0) * x(0, 0), 2);
        }

        real valueAndGradientImpl(arg_type& grad, const arg_type& x) {
            this->gradientImpl(grad, x);
            return grad(0, 1) * grad(0, 1) / (4 * m_b) + std::pow(m_a - x(0, 0), 2.0);
        }

        void gradientImpl(arg_type& grad, const arg_type& x) {
            grad(0, 1) = 2 * m_b * (x(0, 1) - x(0, 0) * x(0, 0));
            grad(0, 0) = x(0, 0) * (2.0 * (x(0, 0) - m_a) - grad(0, 1));
        }

        double m_a;
        double m_b;
    };

	void optimization::helloworld()
	{
        BOOST_TEST_MESSAGE("hello world");
	}

    void optimization::rosenbrock_values() {

        BOOST_TEST_MESSAGE("testing line search method...");

        rosenbrock<point2d> func(1.0, 1.0);

        rosenbrock<point2d>::arg_type gradient = rosenbrock<point2d>::arg_type::Zero();
        rosenbrock<point2d>::arg_type m_x = rosenbrock<point2d>::arg_type::Zero();

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
}}
