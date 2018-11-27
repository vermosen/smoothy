#include <tests/meta.h>
#include <definitions.h>

#include <cstdint>
#include <smoothy/definitions.h>
#include <smoothy/meta/patterns/curiousmixin.h>
#include <smoothy/meta/asm/clock.h>

namespace smoothy   {
namespace testSuite {

    boost::unit_test_framework::test_suite* meta::suite() {
        boost::unit_test_framework::test_suite* suite = BOOST_TEST_SUITE("meta");
        suite->add(BOOST_TEST_CASE(&meta::helloworld        ), 0, MAX_TIME_SEC);
        suite->add(BOOST_TEST_CASE(&meta::curiousmixins     ), 0, MAX_TIME_SEC);
        suite->add(BOOST_TEST_CASE(&meta::clockmeasurement  ), 0, MAX_TIME_SEC);
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

    void meta::curiousmixins() {
        mixin m1;           // default mixin ctor
        mixin m2(1, 2.0);   // other ctor
    }

    inline std::uint64_t fibo(unsigned t) {

        if (t < 2) {
            return 1;
        }
        else if (t == 2) {
            return 2;
        }
        else {
            std::uint64_t t1 = 1;
            std::uint64_t t2 = 1;
            for (std::size_t i = 2; i < t; i++) {
                auto tmp = t1;
                t1 = t2;
                t2 += tmp;
            }

            return t2;
        }
    }

    void meta::clockmeasurement()
    {
        using namespace ::smoothy::meta;

        cpuid();
        cpuid();
        cpuid();

        auto clock = timestamp<details::order::pre>();

        auto res = fibo(100);

        clock = timestamp<details::order::post>() - clock;

        std::stringstream sss;
        sss << "result: " << res << std::endl
            << "duration: " << clock << " ticks" << std::endl;

        BOOST_TEST_MESSAGE(sss.str());
    }
}}
