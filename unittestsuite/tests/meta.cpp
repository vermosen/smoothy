#include <tests/meta.h>
#include <definitions.h>

#include <cstdint>
#include <smoothy/definitions.h>
#include <smoothy/meta/patterns/curiousmixin.h>

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

    std::uint64_t fibo(unsigned t) {

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
        // see https://www.intel.com/content/dam/www/public/us/en/documents/white-papers/ia-32-ia-64-benchmark-code-execution-paper.pdf
        unsigned cycles_low, cycles_high, cycles_low1, cycles_high1;

        asm volatile (
            "CPUID\n\t"
            "RDTSC\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
            "%rax", "%rbx", "%rcx", "%rdx");

        auto res = fibo(70);

        asm volatile(
            "RDTSCP\n\t"
            "mov %%edx, %0\n\t"
            "mov %%eax, %1\n\t"
            "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
            "%rax", "%rbx", "%rcx", "%rdx");

        std::stringstream sss;
        sss << "result: " << res << std::endl
            << "pre: (" << cycles_high << ", " << cycles_low << "), "
            << "post: (" << cycles_high1 << ", " << cycles_low1 << ")"
            << std::endl;

        BOOST_TEST_MESSAGE(sss.str());
    }
}}
