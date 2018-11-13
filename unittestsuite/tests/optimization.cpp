#include <tests/optimization.h>

#include <smoothy/definitions.h>
#include <definitions.h>

namespace smoothy   {
namespace testSuite {

    boost::unit_test_framework::test_suite* optimization::suite() {
        boost::unit_test_framework::test_suite* suite = BOOST_TEST_SUITE("optimization");
        suite->add(BOOST_TEST_CASE(&optimization::helloworld), 0, MAX_TIME_SEC);
        return suite;
    }

	void optimization::helloworld()
	{
        BOOST_TEST_MESSAGE("hello world");
	}
}}
