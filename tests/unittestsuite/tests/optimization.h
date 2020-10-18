#pragma once
#ifndef SMOOTHY_UNIT_TEST_SUITE_OPTIMIZATION_H
#define SMOOTHY_UNIT_TEST_SUITE_OPTIMIZATION_H

#include <boost/test/unit_test.hpp>

#include "utils/point.h"

namespace smoothy   {
namespace testsuite {

  class optimization {
  public:
    static void rosenbrock_values();
    //static void set_criteria();
    //static void set_problem();
    //static void armijogoldstein_stride();

    static boost::unit_test_framework::test_suite* suite();
  };
}}

#endif
