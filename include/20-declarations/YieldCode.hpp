#pragma once

#include "../10-forward-declarations/YieldCode.hpp"

namespace SAO::Yield {

  /* Internal enum used to tell a yield routine what to do after a function in `YieldRoutine::functions` has finished */
  enum struct YieldCode {
    nothing_continue,
    nothing_return,
    value_continue,
    value_repeat,
  };

}
