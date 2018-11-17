#pragma once
#ifndef RUBEDO_UTILS_PATTERNS_FWD_CURIOUS_MIXINS_H
#define RUBEDO_UTILS_PATTERNS_FWD_CURIOUS_MIXINS_H

namespace smoothy   {
namespace meta      {

    template <
          class Base
        , template <class> class ... Ts
    >
    struct curiousMixin;
}}

#endif
