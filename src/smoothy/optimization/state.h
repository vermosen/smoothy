#pragma once
#ifndef SMOOTHY_OPTIMIZATION_STATE_H
#define SMOOTHY_OPTIMIZATION_STATE_H

#include <smoothy/definitions.h>
#include <smoothy/traits/fwd/value.h>

namespace smoothy       {
namespace optimization  {

  /*!
   * the current state of an optimization algo
   */
  template<
      typename Problem
    , template<typename> typename ... Components
  >
  class state : public Components<state<Problem, Components...>>... {
  private:
    using value_type = typename traits::value<Problem>::type;

    void update(const value_type& pos) {
      (Components<state<Problem, Components...>>::update(pos), ...);
    }

  public:
    real m_f;
    value_type m_x;
  };
}}

#endif
