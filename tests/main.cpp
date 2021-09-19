// main function for tests by Michael Trikergiotis
// 28/05/2020
// 
// Copyright (c) Michael Trikergiotis. All Rights Reserved.
// Licensed under the MIT license. See LICENSE in the project root for license information.
// See ThirdPartyNotices.txt in the project root for third party licenses information.



// Let doctest provide the main function.
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest_include.hpp"

// Disable some asserts so we can test more thoroughly.
#define MTL_DISABLE_SOME_ASSERTS




// All headers are included twice to detect redefinition errors.
#include "../mtl/algorithm.hpp"
#include "../mtl/console.hpp"
#include "../mtl/container.hpp"
#include "../mtl/conversion.hpp"
#include "../mtl/definitions.hpp"
#include "../mtl/filesystem.hpp"
#include "../mtl/fmt_include.hpp"
#include "../mtl/math.hpp"
#include "../mtl/numeric.hpp"
#include "../mtl/random.hpp"
#include "../mtl/safety.hpp"
#include "../mtl/stopwatch.hpp"
#include "../mtl/string.hpp"
#include "../mtl/type_traits.hpp"
#include "../mtl/utility.hpp"
#include "../mtl/xoroshiro128plus.hpp"
#include "../mtl/xorshift128plus.hpp"
#include "../mtl/xoshiro256plus.hpp"


// Second inclusion of all the headers to detect redefinition errors.
#include "../mtl/algorithm.hpp"
#include "../mtl/console.hpp"
#include "../mtl/container.hpp"
#include "../mtl/conversion.hpp"
#include "../mtl/definitions.hpp"
#include "../mtl/filesystem.hpp"
#include "../mtl/fmt_include.hpp"
#include "../mtl/math.hpp"
#include "../mtl/numeric.hpp"
#include "../mtl/random.hpp"
#include "../mtl/safety.hpp"
#include "../mtl/stopwatch.hpp"
#include "../mtl/string.hpp"
#include "../mtl/type_traits.hpp"
#include "../mtl/utility.hpp"
#include "../mtl/xoroshiro128plus.hpp"
#include "../mtl/xorshift128plus.hpp"
#include "../mtl/xoshiro256plus.hpp"

