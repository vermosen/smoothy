#pragma once
#ifndef OPTIMIZATION_PROBLEM_H
#define OPTIMIZATION_PROBLEM_H

#include <smoothy/optimization/state.h>

namespace smoothy       {
namespace optimization  {

  template<
      template <typename> typename Func
    , typename Criteria
    , typename Point
    , template <typename> typename ... Traits
  >
  class problem {
  public:
    using value_type    = Point      ;
    using function_type = Func<Point>;
    using criteria_type = Criteria   ;
    using problem_type  = problem<Func, Criteria, Point>;
    using state_type    = state<problem_type, Traits...>;

    public:
      problem(
          const Func<Point>& func
        , const Criteria& criteria
        , const Point& guess);

      criteria_type& criteria() { return m_criteria; }
      Func<Point>&   function() { return     m_func; }
      state_type&     current() { return    m_state; }

    private:
      state_type		m_state   ;
      criteria_type	m_criteria;
      Func<Point>		m_func    ;
  };

  template<
    template <class> class Func
    , class Criteria
    , class Point
    , template<class> class ... Traits
  >
  inline problem<Func, Criteria, Point, Traits ...>::problem(
      const Func<Point>& func
    , const Criteria& criteria
    , const Point& guess)
    : m_state(/* guess */)
    , m_criteria(criteria)
    , m_func(func) {
      
      // TODO: convert guess (point type) to representation (eigen array)
      //m_state.update(guess);
    }
}}

#endif
