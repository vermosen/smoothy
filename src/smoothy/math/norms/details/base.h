#pragma once
#ifndef OPTIMIZATION_CRITERIA_NORMS_DETAILS_BASE_H
#define OPTIMIZATION_CRITERIA_NORMS_DETAILS_BASE_H

namespace smoothy   {
namespace math      {
namespace norms     {

  template <typename Child>
  class base {
  public:
    /*typename traits::retval<Child>::type*/ 
    void apply(/*typename traits::arg<Child>::type vals*/) {
      return Child::impl().apply_impl(/*vals*/); // ???
    }

  protected:
    void apply_impl() {}
  };
}}}

#endif
