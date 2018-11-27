#pragma once
#ifndef SMOOTHY_UNIT_TEST_SUITE_META_H
#define SMOOTHY_UNIT_TEST_SUITE_META_H

#include <boost/test/unit_test.hpp>

namespace smoothy   {
namespace testSuite {

	class meta {
	public:
        static void helloworld();
        static void curiousmixins();
        static void clockmeasurement();

		static boost::unit_test_framework::test_suite* suite();
	};
}}

#endif
