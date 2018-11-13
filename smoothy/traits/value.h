#pragma once
#ifndef SMOOTHY_TRAITS_VALUE_H
#define SMOOTHY_TRAITS_VALUE_H

#include <smoothy/traits/fwd/value.h>

#include <smoothy/optimization/problem.h>

namespace smoothy   {
namespace traits    {

    template<
          template <class> class Func
        , typename Criteria
        , typename Val
    >
    struct value<optimization::problem<Func, Criteria, Val>> {
        typedef Val type;
    };
}}

#endif
