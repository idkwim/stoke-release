// Copyright 2013-2015 Eric Schkufza, Rahul Sharma, Berkeley Churchill, Stefan Heule
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <chrono>
#include <iostream>

#include "src/ext/cpputil/include/command_line/command_line.h"
#include "src/ext/cpputil/include/signal/debug_handler.h"

#include "tools/args/benchmark.h"
#include "tools/gadgets/sandbox.h"
#include "tools/gadgets/seed.h"
#include "tools/gadgets/target.h"
#include "tools/gadgets/testcases.h"
#include "tools/ui/console.h"

using namespace cpputil;
using namespace std;
using namespace std::chrono;
using namespace stoke;

int main(int argc, char** argv) {
  CommandLineConfig::strict_with_convenience(argc, argv);
  DebugHandler::install_sigsegv();
  DebugHandler::install_sigill();

  TargetGadget target;
  SeedGadget seed;
  TestcasesGadget tcs(seed);
  SandboxGadget sb(tcs);

  if (!target.is_sound()) {
    Console::error(1) << "Target reads undefined variables, or leaves live_out undefined." << endl;
  }

  Console::msg() << "Sandbox::run()..." << endl;

  const auto start = steady_clock::now();
  for (size_t i = 0; i < benchmark_itr_arg; ++i) {
    sb.run(target);
  }
  const auto dur = duration_cast<duration<double>>(steady_clock::now() - start);
  const auto rps = benchmark_itr_arg / dur.count();

  Console::msg() << "Runtime:    " << dur.count() << " seconds" << endl;
  Console::msg() << "Throughput: " << rps << " / second" << endl;

  return 0;
}

