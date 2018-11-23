#include <tests/meta.h>
#include <definitions.h>

#include <smoothy/definitions.h>

namespace smoothy   {
namespace testSuite {

    boost::unit_test_framework::test_suite* meta::suite() {
        boost::unit_test_framework::test_suite* suite = BOOST_TEST_SUITE("meta");
        suite->add(BOOST_TEST_CASE(&meta::helloworld        ), 0, MAX_TIME_SEC);
        return suite;
    }

	void meta::helloworld()
	{
        BOOST_TEST_MESSAGE("hello world");
	}
}}
