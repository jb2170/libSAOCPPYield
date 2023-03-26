#pragma once

#include <memory>
#include <vector>

#include "../../subprojects/libSAOCPPIterator/include/Iterator.hpp"
#include "../10-forward-declarations/Iterator/Iterator.hpp"
#include "../10-forward-declarations/YieldCode.hpp"
#include "../10-forward-declarations/YieldRoutine.hpp"

namespace SAO::Yield {

  template <typename TLocals, typename TYield>
  struct YieldRoutine {
    TLocals locals;                                                   /* Accessible among functions that make up the yield routine */
    TYield yielded_result;                                            /* This is the value set by yield_value_continue or yield_value_repeat */
    size_t function_to_run_index;                                     /* Keeps track of which function in `functions` to call next */
    std::vector<void (*)(YieldRoutine<TLocals, TYield> &)> functions; /* The functions that make up a YieldRoutine */
    YieldCode last_run_function_yield_code;                           /* What to do after a function in functions calls a yield method, eg yield_value_repeat */

    YieldRoutine(const std::vector<void (*)(YieldRoutine<TLocals, TYield> &)> &functions);

    void run_routines_until_yield();

    TYield next();

    /* Normal code that doesn't yield anything */
    void yield_nothing_continue();

    /* Return from the YieldRoutine and mark it as finished */
    void yield_nothing_return();

    /* Yield `value` and continue onto the next function */
    void yield_value_continue(TYield value);

    /* Yield `value` and call the same current function again */
    void yield_value_repeat(TYield value);

    /* Return an iterator to go through the values yielded to `yielded_result` by the functions in `functions` */
    SAO::Iterator::IteratorFactory<YieldRoutine<TLocals, TYield>, Iterator::Iterator<TLocals, TYield>> run();

  };

}
