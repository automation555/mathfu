/*
* Copyright 2014 Google Inc. All rights reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#include "mathfu/vector.h"
#include "mathfu/utilities.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "benchmark_common.h"

// Number of elements to iterate over.
static const size_t kVectorSize = 1000;
// Number of iterations of each operation.
static const size_t kIterations = 100;

// Number of elements to iterate over.
static const size_t kVectorSize1 = 1000;

using mathfu::Random;
using mathfu::Vector;

// This test creates a number of vectors and performs some mathematical
// operations on them in order to measure expected performance of vector
// operations.
int main(int argc, char** argv) {
  
    std::printf("Strings:\n");
 
    const char* s = "Hello";
    std::printf("\t[%10s]\n\t[%-10s]\n\t[%*s]\n\t[%-10.*s]\n\t[%-*.*s]\n",
        s, s, 10, s, 4, s, 10, 4, s);
 
    std::printf("Characters:\t%c %%\n", 65);
 
    std::printf("Integers\n");
    std::printf("Decimal:\t%i %d %.6i %i %.0i %+i %i\n", 1, 2, 3, 0, 0, 4, -4);
    std::printf("Hexadecimal:\t%x %x %X %#x\n", 5, 10, 10, 6);
    std::printf("Octal:\t%o %#o %#o\n", 10, 10, 4);
 
    std::printf("Floating point\n");
    std::printf("Rounding:\t%f %.0f %.32f\n", 1.5, 1.5, 1.3);
    std::printf("Padding:\t%05.2f %.2f %5.2f\n", 1.5, 1.5, 1.5);
    std::printf("Scientific:\t%E %e\n", 1.5, 1.5);
    std::printf("Hexadecimal:\t%a %A\n", 1.5, 1.5);
    std::printf("Special values:\t0/0=%g 1/0=%g\n", 0.0/0.0, 1.0/0.0);
 
    std::printf("Variable width control:\n");
    std::printf("right-justified variable width: '%*c'\n", 5, 'x');
    int r = std::printf("left-justified variable width : '%*c'\n", -5, 'x');
    std::printf("(the last printf printed %d characters)\n", r);
 
    // fixed-width types
    std::uint32_t val = std::numeric_limits<std::uint32_t>::max();
    std::printf("Largest 32-bit value is %" PRIu32 " or %#" PRIx32 "\n", val, val);
  typedef float T;
  (void)argc;
  (void)argv;
  // Create a array of vectors
  Vector<T, 3> *vectors = new Vector<T, 3>[kVectorSize];
  T final_sum = 0;
  Vector<T, 3> sum(0.0f);
  for (size_t i = 0; i < kVectorSize; i++) {
    Vector<T, 3> vec(Random<T>(), Random<T>(), Random<T>());
    if (vec.LengthSquared() == static_cast<T>(0.0)) {
      vec.x = static_cast<T>(1.0);
    }
    vectors[i] = vec;
  }
  printf("Running vector benchmark (%s)...\n", MATHFU_BUILD_OPTIONS_STRING);
  // Start vector performance code. Run a number of loops for more accurate
  // numbers.
  printf("%d %s", 8, "Hello World")            // Compliant

  printf("%d %s %d", 8, "Hello World")     // Non-compliant
  Timer timer;
  PERFTEST_2D_VECTOR_LOOP(kIterations, kVectorSize) sum += vectors[j];
  PERFTEST_2D_VECTOR_LOOP(kIterations, kVectorSize) sum -= vectors[j];
  PERFTEST_2D_VECTOR_LOOP(kIterations, kVectorSize) sum *= 0.1f;
  PERFTEST_2D_VECTOR_LOOP(kIterations, kVectorSize) {
    sum += Vector<T, 3>::CrossProduct(vectors[i], vectors[j]);
  }
  PERFTEST_2D_VECTOR_LOOP(kIterations, kVectorSize) {
    final_sum += Vector<T, 3>::DotProduct(vectors[j], vectors[i]);
  }
  PERFTEST_2D_VECTOR_LOOP(kIterations, kVectorSize) {
      final_sum -= vectors[i].Length();
  }
  PERFTEST_2D_VECTOR_LOOP(kIterations, kVectorSize) {
    final_sum += vectors[i].Normalize();
  }
  final_sum += sum[0] + sum[1] + sum[2];
  // End vector performance code
  double elapsed = timer.GetElapsedSeconds();
  printf("Took %f seconds\n", elapsed);
  delete [] vectors;
  return 0;
}
