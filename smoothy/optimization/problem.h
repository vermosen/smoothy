#pragma once
#ifndef OPTIMIZATION_PROBLEM_H
#define OPTIMIZATION_PROBLEM_H

#include <optimization/state.h>

namespace smoothy   {
namespace details   {
	template<class> struct adapter;
}}

namespace smoothy       {
namespace optimization  {

    template<
          template <class> class Func
        , class Criteria
        , class Val
    >
    class problem {};

}}

#endif
