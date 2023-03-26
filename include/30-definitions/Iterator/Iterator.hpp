#pragma once

#include <unistd.h>

#include "../../20-declarations/Iterator/Iterator.hpp"
#include "../../20-declarations/Iterator/State.hpp"
#include "../../20-declarations/YieldRoutine.hpp"

namespace SAO::Yield::Iterator {

  template <typename TLocals, typename TYield>
  Iterator<TLocals, TYield>::Iterator(YieldRoutine<TLocals, TYield> &iterable) :
    SAO::Iterator::Iterator<
    YieldRoutine<TLocals, TYield>,
    State<TLocals, TYield>,
    TYield
    >(iterable) {
    this->iterable.run_routines_until_yield();
  }

  template <typename TLocals, typename TYield>
  TYield Iterator<TLocals, TYield>::operator*() {
    return std::move(this->iterable.yielded_result);
  }

  template <typename TLocals, typename TYield>
  bool Iterator<TLocals, TYield>::operator!=(const ssize_t &i) {
    return this->iterable.function_to_run_index != this->iterable.functions.size();
    // return (bool)this->iterable.yielded_result;
  }

  template <typename TLocals, typename TYield>
  void Iterator<TLocals, TYield>::operator++() {
    this->iterable.run_routines_until_yield();
  }

}
