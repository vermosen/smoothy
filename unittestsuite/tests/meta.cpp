#include "meta.h"
#include "../definitions.h"

#include <smoothy/definitions.h>
#include <smoothy/meta/patterns/curiousmixin.h>

namespace smoothy   {
namespace testSuite {

    boost::unit_test_framework::test_suite* meta::suite() {
        boost::unit_test_framework::test_suite* suite = BOOST_TEST_SUITE("meta");
        suite->add(BOOST_TEST_CASE(&meta::helloworld    ), 0, MAX_TIME_SEC);
        suite->add(BOOST_TEST_CASE(&meta::curiousmixins ), 0, MAX_TIME_SEC);
        return suite;
    }

	void meta::helloworld()
	{
        BOOST_TEST_MESSAGE("hello world");
	}

    template <typename Base>
    struct elem1 {
        elem1() : m_i(0) {}
        elem1(int i) : m_i(i) {}
        int m_i;
    };

    template <typename Base>
    struct elem2 {
        elem2() : m_j(0.0) {}
        elem2(double j) : m_j(j) {}
        double m_j;
    };

    struct mixin : public smoothy::meta::curiousMixin<mixin, elem1, elem2> {
        mixin() : smoothy::meta::curiousMixin<mixin, elem1, elem2>() {}
        mixin(int i, double d) : smoothy::meta::curiousMixin<mixin, elem1, elem2>(i, d) {}
    };

    void meta::curiousmixins()
    {
        // default mixin ctor
        mixin m1;

        // other ctor
        mixin m2(1, 2.0);
    }
}}
