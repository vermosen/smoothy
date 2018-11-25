#pragma once
#ifndef SMOOTHY_UTILS_ADAPTER_H
#define SMOOTHY_UTILS_ADAPTER_H

#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>

#include <smoothy/definitions.h>

#include <smoothy/traits/value.h>

#include <smoothy/traits/fwd/dimension.h>
#include <smoothy/traits/fwd/precision.h>
#include <smoothy/utils/fwd/make_row.h>

#define INTERP_PRINT_ELEM(R, DATA, I, ELEM) \
	r(0, I) = d.ELEM;

#define INTERP_FOR_EACH_DIM(SEQ) \
    BOOST_PP_SEQ_FOR_EACH_I(INTERP_PRINT_ELEM, ~, SEQ)

#define SMOOTHY_DATA_ADAPTER_IMPL(X, P, SEQ)				\
namespace smoothy {											\
namespace traits  {											\
                                                            \
template <>													\
struct dimension<X> {								        \
	static constexpr size value = BOOST_PP_SEQ_SIZE(SEQ);	\
};                                                          \
                                                            \
template<>													\
struct precision<X> {									    \
	using type = P;											\
};															\
}                                                           \
                                                            \
template<>													\
struct make_row<X> {									    \
public:														\
	inline static typename traits::value<X>::type			\
	apply(const X& d) {								        \
	    typename traits::value<X>::type r;					\
	    INTERP_FOR_EACH_DIM(SEQ)							\
	    return r;											\
	}														\
};															\
}

#define SMOOTHY_DATA_ADAPTER(X, P, ...) \
	SMOOTHY_DATA_ADAPTER_IMPL(X, P, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

#endif
