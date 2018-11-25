#pragma once
#ifndef OPTIMIZATION_PROBLEM_H
#define OPTIMIZATION_PROBLEM_H

#include <smoothy/optimization/state.h>

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
        , template<class> class ... Traits
    >
    class problem {
        using value_type    = Val;
        using function_type = Func<Val>;
        using criteria_type = Criteria;
        using problem_type  = problem<Func, Criteria, Val>;
        using state_type    = state<problem_type, Traits...>;

    public:
        problem(const Func<Val>&    func
              , const Criteria&     criteria
              , const Val&          guess   );

        criteria_type&	criteria()  { return m_criteria;    }
        Func<Val>&		function()  { return m_func;        }
        state_type&		current ()  { return m_state;       }

    private:
        state_type		m_state     ;
        criteria_type	m_criteria  ;
        Func<Val>		m_func      ;
    };

    template<
        template <class> class Func
        , class Criteria
        , class Val
        , template<class> class ... Traits
    >
    inline problem<Func, Criteria, Val, Traits ...>::problem(
          const Func<Val>& func
        , const Criteria& criteria
        , const Val& guess)
        : m_state()
        , m_criteria(criteria)
        , m_func(func) {}
}}

#endif
