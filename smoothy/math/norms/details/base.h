#pragma once
#ifndef OPTIMIZATION_CRITERIA_NORMS_DETAILS_BASE_H
#define OPTIMIZATION_CRITERIA_NORMS_DETAILS_BASE_H

#include <smoothy/meta/patterns/curiouslyrecurring.h>

namespace smoothy   {
namespace math      {
namespace norms     {

    template <typename Child>
    class base : public meta::curiouslyRecurring<Child> {
    public:
        /*typename traits::retval<Child>::type*/ void apply(/*typename traits::arg<Child>::type vals*/) {
            return meta::curiouslyRecurring<Child>::impl().applyImpl(/*vals*/);
        }
    };
}}

#endif
