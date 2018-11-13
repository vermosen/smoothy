#pragma once
#ifndef SMOOTHY_UNIT_TEST_SUITE_OPTIMIZATION_H
#define SMOOTHY_UNIT_TEST_SUITE_OPTIMIZATION_H

#include <boost/test/unit_test.hpp>

namespace smoothy   {
namespace testSuite {

	class optimization {
	public:
		static void helloworld();
		static boost::unit_test_framework::test_suite* suite();
	};
}}

#endif
