#pragma once
#ifndef SMOOTHY_UNIT_TEST_SUITE_OPTIMIZATION_H
#define SMOOTHY_UNIT_TEST_SUITE_OPTIMIZATION_H

#include <boost/test/unit_test.hpp>

namespace smoothy   {
namespace testSuite {

    // point classes for optimization tests
    struct point2d {
        double m_x1;
        double m_x2;
    };

    struct point3d {
        double m_x1;
        double m_x2;
        double m_x3;
    };

	class optimization {
	public:
        static void helloworld();
        static void rosenbrock_values();
        static void set_criteria();

		static boost::unit_test_framework::test_suite* suite();
	};
}}

#endif
