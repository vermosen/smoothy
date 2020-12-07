#pragma once
#ifndef SMOOTHY_OPTIMIZATION_CRITERIA_FUNCTIONTOLERANCE_H
#define SMOOTHY_OPTIMIZATION_CRITERIA_FUNCTIONTOLERANCE_H

#include <smoothy/optimization/criterion.h>

namespace smoothy       {
namespace optimization  {

    template <>
    class criterion<criteria::type::functionTolerance> {
    public:
    struct pack {
        double m_precision;
    };

        criterion(const pack& p) : m_pack(p) {}

    protected:
        template <typename State>
        bool apply(State& from, State& to) { return true; }
        pack m_pack;
    };
}}

#endif // SMOOTHY_OPTIMIZATION_CRITERIA_FUNCTIONTOLERANCE_H
