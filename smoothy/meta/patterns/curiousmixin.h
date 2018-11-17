#pragma once
#ifndef RUBEDO_UTILS_PATTERNS_CURIOUS_MIXINS_H
#define RUBEDO_UTILS_PATTERNS_CURIOUS_MIXINS_H

#include <smoothy/meta/patterns/fwd/curiousmixin.h>

#include <smoothy/meta/patterns/curiouslyrecurring.h>

namespace smoothy   {
namespace meta      {

    /*!
     * Implementation of the curious mixins pattern.
     * Ref. C++ Templates - The Complete Guide, 2nd Edition
     * D. Vandevoorde, N. M. Josuttis & D. Gregor pp 604
     */
    template <
          class Base
        , template <class> class ... Ts
    >
    struct curiousMixin : public Ts<Base>... {

        template <typename ... Xs>
        curiousMixin(Xs&& ... xs)
            : Ts<Base>(std::forward<Xs>(xs))... {}

        template <template <class> class T>
        inline T<Base>& impl() {
            return static_cast<T<Base>&>(*this);
        }

        template <template <class> class T>
        inline const T<Base>& impl() const {
            return static_cast<const T<Base>&>(*this);
        }
    };
}}

#endif
