#pragma once

#include <memory>

#include "../../../subprojects/libSAOCPPIterator/include/20-declarations/Iterator.hpp"
#include "../../10-forward-declarations/Iterator/Iterator.hpp"
#include "../../10-forward-declarations/Iterator/State.hpp"
#include "../../10-forward-declarations/YieldRoutine.hpp"

namespace SAO::Yield::Iterator {

  template <typename TLocals, typename TYield>
  struct Iterator : SAO::Iterator::Iterator<
    YieldRoutine<TLocals, TYield>,
    State<TLocals, TYield>,
    TYield
  > {
    Iterator(YieldRoutine<TLocals, TYield> &iterable);

    TYield operator*();

    bool operator!=(const ssize_t &i);

    void operator++();
  };

}
