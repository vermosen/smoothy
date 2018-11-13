#include <boost/test/included/unit_test_framework.hpp>

#include <tests/optimization.h>

boost::unit_test_framework::test_suite* init_unit_test_suite(int, char*[]) {

    namespace utf = boost::unit_test;
    int argc = utf::framework::master_test_suite().argc;
    char **argv = utf::framework::master_test_suite().argv;

    utf::framework::master_test_suite().add(smoothy::testSuite::optimization::suite());
    return nullptr;
}
