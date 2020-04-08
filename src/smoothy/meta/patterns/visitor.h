#pragma once
#ifndef SMOOTHY_META_PATTERNS_VISITOR_H
#define SMOOTHY_META_PATTERNS_VISITOR_H

namespace smoothy {
namespace meta    {
namespace details {

  class visitor;

  template <class T>
  class individual;
}

  template <class ... Types>
  class visitor : public details::visitor
    , public details::individual<Types>... {};

  template <class Base>
  class visitable {
  public:
    template <typename T>
    inline void accept(T& visitor) {
      visitor.visit(Base::impl());
    }
  };

namespace details {

  class visitor {
  public:
    virtual ~visitor() {};
  };

  template <class T>
  class individual {
  public:
    virtual void visit(T&) = 0;
  };
}
}}

#endif
