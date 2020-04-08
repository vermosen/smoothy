#pragma once
#ifndef SMOOTHY_OPTIMIZATION_CRITERIA_MAXITERATION_H
#define SMOOTHY_OPTIMIZATION_CRITERIA_MAXITERATION_H

#include <smoothy/optimization/criterion.h>

namespace smoothy       {
namespace optimization  {

    template <>
    class criterion<criteria::type::maxIterations> {
    public:
        struct pack {
            unsigned m_max;
        };

        criterion(const pack& p) : m_pack(p) {}

    protected:
        template <typename State>
        bool apply(State& from, State& to) { return true; }
        pack m_pack;
    };
}}

#endif
