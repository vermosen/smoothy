#pragma once
#ifndef SMOOTHY_META_PATTERNS_CURIOUSLY_RECURRING_H
#define SMOOTHY_META_PATTERNS_CURIOUSLY_RECURRING_H

#include <smoothy/meta/patterns/fwd/curiouslyrecurring.h>

namespace smoothy   {
namespace meta      {

    /*!
     * Implementation of the curiously recurring template pattern.
     * Ref. James O.Coplien.A Curiously Recurring Template Pattern.
     * In Stanley B.Lippman, editor, C++ Gems, 135 - 144.
     * Cambridge University Press, New York, New York, 1996.
     *
     * note: the extra Base template argument may be used to
     * solve anbiguity in case the pattern is used in some
     * multi-inheritance context.
     */
	template <
          class Impl
        , class Base
    >
	class curiouslyRecurring {
	protected:
		curiouslyRecurring() {}
		virtual ~curiouslyRecurring() {}

		inline Impl& impl() {
			return static_cast<Impl&>(*this);
		}

		inline const Impl& impl() const {
			return static_cast<const Impl&>(*this);
		}
	};
}}

#endif
