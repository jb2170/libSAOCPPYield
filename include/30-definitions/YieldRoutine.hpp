#pragma once

#include "../20-declarations/YieldCode.hpp"
#include "../20-declarations/YieldRoutine.hpp"

namespace SAO::Yield {

  template <typename TLocals, typename TYield>
  YieldRoutine<TLocals, TYield>::YieldRoutine(const std::vector<void(*)(YieldRoutine<TLocals, TYield> &)> &functions) :
    locals(),
    yielded_result(),
    function_to_run_index(0),
    functions(functions),
    last_run_function_yield_code() {}

  template <typename TLocals, typename TYield>
  void YieldRoutine<TLocals, TYield>::run_routines_until_yield() {
    for (; function_to_run_index < functions.size();) {
      functions.at(function_to_run_index)(*this);
      switch (last_run_function_yield_code) {
        case YieldCode::nothing_continue:
          continue;
        case YieldCode::nothing_return:
        case YieldCode::value_continue:
        case YieldCode::value_repeat:
          return;
        default:
          std::abort();
      }
    }
  }

  template <typename TLocals, typename TYield>
  TYield YieldRoutine<TLocals, TYield>::next() {
    run_routines_until_yield();
    return std::move(yielded_result);
  }

  template <typename TLocals, typename TYield>
  void YieldRoutine<TLocals, TYield>::yield_nothing_continue() {
    function_to_run_index++;
    last_run_function_yield_code = YieldCode::nothing_continue;
  }

  template <typename TLocals, typename TYield>
  void YieldRoutine<TLocals, TYield>::yield_nothing_return() {
    function_to_run_index = functions.size(); /* EOF */
    last_run_function_yield_code = YieldCode::nothing_return;
  }

  template <typename TLocals, typename TYield>
  void YieldRoutine<TLocals, TYield>::yield_value_continue(TYield value) {
    yielded_result = std::move(value);
    function_to_run_index++;
    last_run_function_yield_code = YieldCode::value_continue;
  }

  template <typename TLocals, typename TYield>
  void YieldRoutine<TLocals, TYield>::yield_value_repeat(TYield value) {
    yielded_result = std::move(value);
    last_run_function_yield_code = YieldCode::value_repeat;
  }

  template <typename TLocals, typename TYield>
  SAO::Iterator::IteratorFactory<YieldRoutine<TLocals, TYield>, Iterator::Iterator<TLocals, TYield>> YieldRoutine<TLocals, TYield>::run() {
    return SAO::Iterator::IteratorFactory<YieldRoutine<TLocals, TYield>, Iterator::Iterator<TLocals, TYield>>(*this);
  }

}
