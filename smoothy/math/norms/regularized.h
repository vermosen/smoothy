#pragma once
#ifndef RUBEDO_MATH_EXPERIMENTAL_OPTIMIZATION_CRITERIA_EXIT_H
#define RUBEDO_MATH_EXPERIMENTAL_OPTIMIZATION_CRITERIA_EXIT_H

#include <smoothy/math/norms/details/base.h>

#include <smoothy/traits/fwd/dimension.h>

#include <smoothy/math/norm.h>

namespace smoothy   {
namespace math      {

    template <typename Val>
    struct norm<Val, 1, norms::type::regularized> : public norms::base<norm<Val, 1, norms::type::regularized>> {
        using ancestor = norms::base<norm<Val, norms::type::regularized>>;

        static_assert(traits::dimension<Val>::value == 1);

        void applyImpl() { return; }
    };

    template <typename Val>
    struct norm<Val, norms::type::regularized> : public norms::base<norm<Val, norms::type::regularized>> {
        using ancestor = norms::base<norm<Val, norms::type::regularized>>;

        static_assert(traits::dimension<Val>::value == 1);

        void applyImpl() { return; }
    };

	struct no {
		static inline real compute(real fnew, real fold) {
			return std::abs(fnew - fold);
		}
	};

    template <typename Val>
    struct norm<Val, norms::type::regularized>
    struct no {
        static inline real compute(real fnew, real fold) {
            return std::abs(fnew - fold);
        }
    };

	struct l2 {
		static inline real compute(real fnew, real fold) {
			return (fnew - fold) * (fnew - fold);
		}
	};

	struct regularized {
		static inline real compute(real fnew, real fold) {
			return 2.0 * std::abs(fnew - fold) /
				(std::fabs(fnew) + std::fabs(fold) +
					std::numeric_limits<real>::epsilon());
		}
	};
}}}}

#endif
