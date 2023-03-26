#include <unistd.h>
#include <cstdlib>
#include <cstdio>

#include "Yield.hpp"

using namespace SAO::Yield;

struct ExampleYieldRoutineLocals {
  int index;
};

typedef YieldRoutine<ExampleYieldRoutineLocals, std::unique_ptr<int>> TExampleYieldRoutine;

void func1(TExampleYieldRoutine &yr) {
  return yr.yield_value_continue(std::make_unique<int>(100));
}

void func2(TExampleYieldRoutine &yr) {
  yr.locals.index = 5;
  return yr.yield_nothing_continue();
}

void func3(TExampleYieldRoutine &yr) {
  if (yr.locals.index == 200) {
    /* not going to happen... */
    return yr.yield_nothing_return();
  } else if (yr.locals.index < 10) {
    return yr.yield_value_repeat(std::make_unique<int>(yr.locals.index++));
  } else {
    return yr.yield_nothing_continue();
  }
}

int main() {
  TExampleYieldRoutine yr({ func1, func2, func3 });

  for (auto i : yr.run()) {
    std::printf("%i\n", *i);
  }

  return EXIT_SUCCESS;
}
