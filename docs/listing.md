# List of classes and functions

 | [algorithm.hpp](#algorithmhpp) | [console.hpp](#consolehpp) | [container.hpp](#containerhpp) | [conversion.hpp](#conversionhpp) | [filesystem.hpp](#filesystemhpp) | [math.hpp](#mathhpp) | [numeric.hpp](#numerichpp) | [random.hpp](#randomhpp) | [safety.hpp](#safetyhpp) | [stopwatch.hpp](#stopwatchhpp) | [string.hpp](#stringhpp) | [type_traits.hpp](#type_traitshpp) | [utility.hpp](#utilityhpp) | [xoroshiro128plus.hpp](#xoroshiro128plushpp) | [xorshift128plus.hpp](#xorshift128plushpp) | [xoshiro256plus.hpp](#xoshiro256plushpp) |

## Statistics

There are 16 headers.

There are 10 classes.

There are 52 class member functions.

There are 116 non-member functions.

## algorithm.hpp

- `mtl::not_unique_inclusive` [(Documentation)](../mtl/algorithm.hpp#L38) [(Examples)](../tests/tests_algorithm.cpp#L41)
- `mtl::not_unique_exclusive` [(Documentation)](../mtl/algorithm.hpp#L40) [(Examples)](../tests/tests_algorithm.cpp#L226)
- `mtl::not_unique` [(Documentation)](../mtl/algorithm.hpp#L42) [(Examples)](../tests/tests_algorithm.cpp#L408)
- `mtl::keep_duplicates_inclusive` [(Documentation)](../mtl/algorithm.hpp#L460) [(Examples)](../tests/tests_algorithm.cpp#L585)
- `mtl::keep_duplicates_exclusive` [(Documentation)](../mtl/algorithm.hpp#L608) [(Examples)](../tests/tests_algorithm.cpp#L752)
- `mtl::keep_duplicates` [(Documentation)](../mtl/algorithm.hpp#L738) [(Examples)](../tests/tests_algorithm.cpp#L911)
- `mtl::keep_duplicates_inclusive_sorted` [(Documentation)](../mtl/algorithm.hpp#L458) [(Examples)](../tests/tests_algorithm.cpp#L1075)
- `mtl::keep_duplicates_exclusive_sorted` [(Documentation)](../mtl/algorithm.hpp#L606) [(Examples)](../tests/tests_algorithm.cpp#L1265)
- `mtl::keep_duplicates_sorted` [(Documentation)](../mtl/algorithm.hpp#L736) [(Examples)](../tests/tests_algorithm.cpp#L1450)
- `mtl::keep_duplicates_inclusive_preserve` [(Documentation)](../mtl/algorithm.hpp#L462) [(Examples)](../tests/tests_algorithm.cpp#L1642)
- `mtl::keep_duplicates_exclusive_preserve` [(Documentation)](../mtl/algorithm.hpp#L610) [(Examples)](../tests/tests_algorithm.cpp#L1807)
- `mtl::keep_duplicates_preserve` [(Documentation)](../mtl/algorithm.hpp#L739) [(Examples)](../tests/tests_algorithm.cpp#L1974)
- `mtl::rem_duplicates_sorted` [(Documentation)](../mtl/algorithm.hpp#L257) [(Examples)](../tests/tests_algorithm.cpp#L2136)
- `mtl::rem_duplicates` [(Documentation)](../mtl/algorithm.hpp#L258) [(Examples)](../tests/tests_algorithm.cpp#L2325)
- `mtl::rem_duplicates_preserve` [(Documentation)](../mtl/algorithm.hpp#L259) [(Examples)](../tests/tests_algorithm.cpp#L2479)
- `mtl::contains` [(Documentation)](../mtl/algorithm.hpp#L852) [(Examples)](../tests/tests_algorithm.cpp#L2642)
- `mtl::contains_all` [(Documentation)](../mtl/algorithm.hpp#L905) [(Examples)](../tests/tests_algorithm.cpp#L2790)
- `mtl::contains_all_sorted` [(Documentation)](../mtl/algorithm.hpp#L906) [(Examples)](../tests/tests_algorithm.cpp#L2951)
- `mtl::for_each` [(Documentation)](../mtl/algorithm.hpp#L988) [(Examples)](../tests/tests_algorithm.cpp#L3112)
- `mtl::for_adj_pairs` [(Documentation)](../mtl/algorithm.hpp#L1133) [(Examples)](../tests/tests_algorithm.cpp#L3607)
- `mtl::for_all_pairs` [(Documentation)](../mtl/algorithm.hpp#L1162) [(Examples)](../tests/tests_algorithm.cpp#L3695)
- `mtl::fill_range` [(Documentation)](../mtl/algorithm.hpp#L1198) [(Examples)](../tests/tests_algorithm.cpp#L3787)
- `mtl::range` [(Documentation)](../mtl/algorithm.hpp#L1241) [(Examples)](../tests/tests_algorithm.cpp#L3909)

---------------------------------------------------

## console.hpp

- `mtl::console::print` [(Documentation)](../mtl/console.hpp#L167) [(Examples)](../tests/tests_console.cpp#L72)
- `mtl::console::println` [(Documentation)](../mtl/console.hpp#L207) [(Examples)](../tests/tests_console.cpp#L72)
- `mtl::console::print_all` [(Documentation)](../mtl/console.hpp#L289) [(Examples)](../tests/tests_console.cpp#L339)
- `mtl::console::print_color` [(Documentation)](../mtl/console.hpp#L538) [(Examples)](../tests/tests_console.cpp#L672)
- `mtl::console::println_color` [(Documentation)](../mtl/console.hpp#L539) [(Examples)](../tests/tests_console.cpp#L827)
- `mtl::console::overtype` [(Documentation)](../mtl/console.hpp#L1227) [(Examples)](../tests/tests_console.cpp#L922)
- `mtl::console::clear` [(Documentation)](../mtl/console.hpp#L1285) [(Examples)](../tests/tests_console.cpp#L1302)

---------------------------------------------------

## container.hpp

- `mtl::reserve` [(Documentation)](../mtl/container.hpp#L24) [(Examples)](../tests/tests_container.cpp#L27)
- `mtl::push_back` [(Documentation)](../mtl/container.hpp#L49) [(Examples)](../tests/tests_container.cpp#L126)
- `mtl::emplace_back` [(Documentation)](../mtl/container.hpp#L73) [(Examples)](../tests/tests_container.cpp#L262)
- `mtl::slice` [(Documentation)](../mtl/container.hpp#L103) [(Examples)](../tests/tests_container.cpp#L401)
- `mtl::slice_n` [(Documentation)](../mtl/container.hpp#L104) [(Examples)](../tests/tests_container.cpp#L1281)

---------------------------------------------------

## conversion.hpp

- `mtl::to_num` [(Documentation)](../mtl/conversion.hpp#L29) [(Examples)](../tests/tests_conversion.cpp#L66)
- `mtl::to_num_noex` [(Documentation)](../mtl/conversion.hpp#L30) [(Examples)](../tests/tests_conversion.cpp#L616)
- `mtl::numeric_cast` [(Documentation)](../mtl/conversion.hpp#L720) [(Examples)](../tests/tests_conversion.cpp#L1931)
- `mtl::numeric_cast_noex` [(Documentation)](../mtl/conversion.hpp#L722) [(Examples)](../tests/tests_conversion.cpp#L2549)
- `mtl::rounding_cast` [(Documentation)](../mtl/conversion.hpp#L802) [(Examples)](../tests/tests_conversion.cpp#L5208)
- `mtl::rounding_cast_noex` [(Documentation)](../mtl/conversion.hpp#L803) [(Examples)](../tests/tests_conversion.cpp#L5301)

---------------------------------------------------

## filesystem.hpp

- `mtl::filesystem::read_file` [(Documentation)](../mtl/filesystem.hpp#L38) [(Examples)](../tests/tests_filesystem.cpp#L105)
- `mtl::filesystem::read_all_lines` [(Documentation)](../mtl/filesystem.hpp#L114) [(Examples)](../tests/tests_filesystem.cpp#L349)
- `mtl::filesystem::write_file` [(Documentation)](../mtl/filesystem.hpp#L247) [(Examples)](../tests/tests_filesystem.cpp#L76)
- `mtl::filesystem::write_all_lines` [(Documentation)](../mtl/filesystem.hpp#L286) [(Examples)](../tests/tests_filesystem.cpp#L867)

---------------------------------------------------

## math.hpp

- `mtl::approx_equal_abs` [(Documentation)](../mtl/math.hpp#L23) [(Examples)](../tests/tests_math.cpp#L26)
- `mtl::approx_equal_rel` [(Documentation)](../mtl/math.hpp#L24) [(Examples)](../tests/tests_math.cpp#L99)
- `mtl::approx_equal_comb` [(Documentation)](../mtl/math.hpp#L25) [(Examples)](../tests/tests_math.cpp#L171)
- `mtl::percent_whole` [(Documentation)](../mtl/math.hpp#L93) [(Examples)](../tests/tests_math.cpp#L282)
- `mtl::percent_portion` [(Documentation)](../mtl/math.hpp#L94) [(Examples)](../tests/tests_math.cpp#L598)
- `mtl::percent` [(Documentation)](../mtl/math.hpp#L95) [(Examples)](../tests/tests_math.cpp#L792)

---------------------------------------------------

## numeric.hpp

- `mtl::iota` [(Documentation)](../mtl/numeric.hpp#L30) [(Examples)](../tests/tests_numeric.cpp#L24)
- `mtl::frequency` [(Documentation)](../mtl/numeric.hpp#L57) [(Examples)](../tests/tests_numeric.cpp#L534)
- `mtl::mean` [(Documentation)](../mtl/numeric.hpp#L132) [(Examples)](../tests/tests_numeric.cpp#L755)
- `mtl::median` [(Documentation)](../mtl/numeric.hpp#L162) [(Examples)](../tests/tests_numeric.cpp#L1104)

---------------------------------------------------

## random.hpp

- [**CLASS**] `mtl::rng` [(Documentation)](../mtl/random.hpp#L30) [(Examples)](../tests/tests_random.cpp#L27)
  - `mtl::rng::rng` [(Documentation)](../mtl/random.hpp#L30) [(Examples)](../tests/tests_random.cpp#L29)
  - `mtl::rng::set_min_max` [(Documentation)](../mtl/random.hpp#L113) [(Examples)](../tests/tests_random.cpp#L31)
  - `mtl::rng::min` [(Documentation)](../mtl/random.hpp#L128) [(Examples)](../tests/tests_random.cpp#L33)
  - `mtl::rng::max` [(Documentation)](../mtl/random.hpp#L137) [(Examples)](../tests/tests_random.cpp#L35)
  - `mtl::rng::next` [(Documentation)](../mtl/random.hpp#L146) [(Examples)](../tests/tests_random.cpp#L37)
  - `mtl::rng::seed` [(Documentation)](../mtl/random.hpp#L155) [(Examples)](../tests/tests_random.cpp#L39)
  - `mtl::rng::seed_random` [(Documentation)](../mtl/random.hpp#L188) [(Examples)](../tests/tests_random.cpp#L41)
- `mtl::random_choice` [(Documentation)](../mtl/random.hpp#L200) [(Examples)](../tests/tests_random.cpp#L646)
- `mtl::shuffle` [(Documentation)](../mtl/random.hpp#L253) [(Examples)](../tests/tests_random.cpp#L1117)

---------------------------------------------------

## safety.hpp

- `mtl::safe_copy` [(Documentation)](../mtl/safety.hpp#L28) [(Examples)](../tests/tests_safety.cpp#L30)
- `mtl::safe_copy_n` [(Documentation)](../mtl/safety.hpp#L29) [(Examples)](../tests/tests_safety.cpp#L695)

---------------------------------------------------

## stopwatch.hpp

- [**CLASS**] `mtl::chrono::stopwatch` [(Documentation)](../mtl/stopwatch.hpp#L28) [(Examples)](../tests/tests_stopwatch.cpp#L26)
  - `mtl::chrono::stopwatch::start` [(Documentation)](../mtl/stopwatch.hpp#L41) [(Examples)](../tests/tests_stopwatch.cpp#L28)
  - `mtl::chrono::stopwatch::stop` [(Documentation)](../mtl/stopwatch.hpp#L51) [(Examples)](../tests/tests_stopwatch.cpp#L30)
  - `mtl::chrono::stopwatch::reset` [(Documentation)](../mtl/stopwatch.hpp#L61) [(Examples)](../tests/tests_stopwatch.cpp#L32)
  - `mtl::chrono::stopwatch::restart` [(Documentation)](../mtl/stopwatch.hpp#L72) [(Examples)](../tests/tests_stopwatch.cpp#L34)
  - `mtl::chrono::stopwatch::elapsed_minutes` [(Documentation)](../mtl/stopwatch.hpp#L82) [(Examples)](../tests/tests_stopwatch.cpp#L36)
  - `mtl::chrono::stopwatch::elapsed_seconds` [(Documentation)](../mtl/stopwatch.hpp#L98) [(Examples)](../tests/tests_stopwatch.cpp#L38)
  - `mtl::chrono::stopwatch::elapsed_milli` [(Documentation)](../mtl/stopwatch.hpp#L111) [(Examples)](../tests/tests_stopwatch.cpp#L40)
  - `mtl::chrono::stopwatch::elapsed_micro` [(Documentation)](../mtl/stopwatch.hpp#L124) [(Examples)](../tests/tests_stopwatch.cpp#L42)
  - `mtl::chrono::stopwatch::elapsed_nano` [(Documentation)](../mtl/stopwatch.hpp#L137) [(Examples)](../tests/tests_stopwatch.cpp#L44)

---------------------------------------------------

## string.hpp

- `mtl::string::is_upper` [(Documentation)](../mtl/string.hpp#L41) [(Examples)](../tests/tests_string.cpp#L85)
- `mtl::string::is_lower` [(Documentation)](../mtl/string.hpp#L43) [(Examples)](../tests/tests_string.cpp#L228)
- `mtl::string::to_upper` [(Documentation)](../mtl/string.hpp#L110) [(Examples)](../tests/tests_string.cpp#L371)
- `mtl::string::to_lower` [(Documentation)](../mtl/string.hpp#L112) [(Examples)](../tests/tests_string.cpp#L418)
- `mtl::string::is_ascii` [(Documentation)](../mtl/string.hpp#L161) [(Examples)](../tests/tests_string.cpp#L463)
- `mtl::string::is_alphabetic` [(Documentation)](../mtl/string.hpp#L200) [(Examples)](../tests/tests_string.cpp#L590)
- `mtl::string::is_numeric` [(Documentation)](../mtl/string.hpp#L202) [(Examples)](../tests/tests_string.cpp#L744)
- `mtl::string::is_alphanum` [(Documentation)](../mtl/string.hpp#L203) [(Examples)](../tests/tests_string.cpp#L898)
- `mtl::string::contains` [(Documentation)](../mtl/string.hpp#L301) [(Examples)](../tests/tests_string.cpp#L1050)
- `mtl::string::strip_front` [(Documentation)](../mtl/string.hpp#L371) [(Examples)](../tests/tests_string.cpp#L1126)
- `mtl::string::strip_back` [(Documentation)](../mtl/string.hpp#L372) [(Examples)](../tests/tests_string.cpp#L1126)
- `mtl::string::strip` [(Documentation)](../mtl/string.hpp#L373) [(Examples)](../tests/tests_string.cpp#L1126)
- `mtl::string::pad_front` [(Documentation)](../mtl/string.hpp#L446) [(Examples)](../tests/tests_string.cpp#L1360)
- `mtl::string::pad_back` [(Documentation)](../mtl/string.hpp#L449) [(Examples)](../tests/tests_string.cpp#L1360)
- `mtl::string::pad` [(Documentation)](../mtl/string.hpp#L452) [(Examples)](../tests/tests_string.cpp#L1360)
- `mtl::string::to_string` [(Documentation)](../mtl/string.hpp#L612) [(Examples)](../tests/tests_string.cpp#L1578)
- `mtl::string::join_all` [(Documentation)](../mtl/string.hpp#L728) [(Examples)](../tests/tests_string.cpp#L1671)
- `mtl::string::join` [(Documentation)](../mtl/string.hpp#L904) [(Examples)](../tests/tests_string.cpp#L1894)
- `mtl::string::split` [(Documentation)](../mtl/string.hpp#L1041) [(Examples)](../tests/tests_string.cpp#L1940)
- `mtl::string::replace` [(Documentation)](../mtl/string.hpp#L1179) [(Examples)](../tests/tests_string.cpp#L3048)
- `mtl::string::replace_all` [(Documentation)](../mtl/string.hpp#L1487) [(Examples)](../tests/tests_string.cpp#L3706)

---------------------------------------------------

## type_traits.hpp

- `mtl::are_same` [(Documentation)](../mtl/type_traits.hpp#L40) [(Examples)](../tests/tests_type_traits.cpp#L40)
- `mtl::has_reserve` [(Documentation)](../mtl/type_traits.hpp#L65) [(Examples)](../tests/tests_type_traits.cpp#L100)
- `mtl::has_push_back` [(Documentation)](../mtl/type_traits.hpp#L88) [(Examples)](../tests/tests_type_traits.cpp#L144)
- `mtl::has_emplace_back` [(Documentation)](../mtl/type_traits.hpp#L109) [(Examples)](../tests/tests_type_traits.cpp#L184)
- `mtl::has_size` [(Documentation)](../mtl/type_traits.hpp#L162) [(Examples)](../tests/tests_type_traits.cpp#L227)
- `mtl::has_find` [(Documentation)](../mtl/type_traits.hpp#L184) [(Examples)](../tests/tests_type_traits.cpp#L269)
- `mtl::is_sint` [(Documentation)](../mtl/type_traits.hpp#L258) [(Examples)](../tests/tests_type_traits.cpp#L324)
- `mtl::is_uint` [(Documentation)](../mtl/type_traits.hpp#L260) [(Examples)](../tests/tests_type_traits.cpp#L473)
- `mtl::is_int` [(Documentation)](../mtl/type_traits.hpp#L262) [(Examples)](../tests/tests_type_traits.cpp#L622)
- `mtl::is_float` [(Documentation)](../mtl/type_traits.hpp#L264) [(Examples)](../tests/tests_type_traits.cpp#L769)
- `mtl::is_number` [(Documentation)](../mtl/type_traits.hpp#L266) [(Examples)](../tests/tests_type_traits.cpp#L833)
- `mtl::is_char` [(Documentation)](../mtl/type_traits.hpp#L268) [(Examples)](../tests/tests_type_traits.cpp#L994)
- `mtl::is_std_array` [(Documentation)](../mtl/type_traits.hpp#L364) [(Examples)](../tests/tests_type_traits.cpp#L1063)
- `mtl::is_std_vector` [(Documentation)](../mtl/type_traits.hpp#L384) [(Examples)](../tests/tests_type_traits.cpp#L1085)
- `mtl::is_std_deque` [(Documentation)](../mtl/type_traits.hpp#L404) [(Examples)](../tests/tests_type_traits.cpp#L1107)
- `mtl::is_std_forward_list` [(Documentation)](../mtl/type_traits.hpp#L424) [(Examples)](../tests/tests_type_traits.cpp#L1129)
- `mtl::is_std_list` [(Documentation)](../mtl/type_traits.hpp#L444) [(Examples)](../tests/tests_type_traits.cpp#L1154)
- `mtl::is_std_set` [(Documentation)](../mtl/type_traits.hpp#L464) [(Examples)](../tests/tests_type_traits.cpp#L1176)
- `mtl::is_std_multiset` [(Documentation)](../mtl/type_traits.hpp#L484) [(Examples)](../tests/tests_type_traits.cpp#L1200)
- `mtl::is_std_map` [(Documentation)](../mtl/type_traits.hpp#L504) [(Examples)](../tests/tests_type_traits.cpp#L1226)
- `mtl::is_std_multimap` [(Documentation)](../mtl/type_traits.hpp#L524) [(Examples)](../tests/tests_type_traits.cpp#L1250)
- `mtl::is_std_unordered_set` [(Documentation)](../mtl/type_traits.hpp#L544) [(Examples)](../tests/tests_type_traits.cpp#L1275)
- `mtl::is_std_unordered_map` [(Documentation)](../mtl/type_traits.hpp#L564) [(Examples)](../tests/tests_type_traits.cpp#L1325)
- `mtl::is_std_unordered_multiset` [(Documentation)](../mtl/type_traits.hpp#L584) [(Examples)](../tests/tests_type_traits.cpp#L1300)
- `mtl::is_std_unordered_multimap` [(Documentation)](../mtl/type_traits.hpp#L604) [(Examples)](../tests/tests_type_traits.cpp#L1350)
- `mtl::is_std_stack` [(Documentation)](../mtl/type_traits.hpp#L624) [(Examples)](../tests/tests_type_traits.cpp#L1376)
- `mtl::is_std_queue` [(Documentation)](../mtl/type_traits.hpp#L644) [(Examples)](../tests/tests_type_traits.cpp#L1400)
- `mtl::is_std_priority_queue` [(Documentation)](../mtl/type_traits.hpp#L664) [(Examples)](../tests/tests_type_traits.cpp#L1424)
- `mtl::is_std_container` [(Documentation)](../mtl/type_traits.hpp#L684) [(Examples)](../tests/tests_type_traits.cpp#L1449)
- `mtl::is_std_pair` [(Documentation)](../mtl/type_traits.hpp#L713) [(Examples)](../tests/tests_type_traits.cpp#L1478)
- `mtl::is_std_string` [(Documentation)](../mtl/type_traits.hpp#L736) [(Examples)](../tests/tests_type_traits.cpp#L1530)
- `mtl::is_c_string` [(Documentation)](../mtl/type_traits.hpp#L756) [(Examples)](../tests/tests_type_traits.cpp#L1614)
- `mtl::is_input_iterator` [(Documentation)](../mtl/type_traits.hpp#L775) [(Examples)](../tests/tests_type_traits.cpp#L1644)
- `mtl::is_output_iterator` [(Documentation)](../mtl/type_traits.hpp#L777) [(Examples)](../tests/tests_type_traits.cpp#L1644)
- `mtl::is_iterator` [(Documentation)](../mtl/type_traits.hpp#L779) [(Examples)](../tests/tests_type_traits.cpp#L1644)

---------------------------------------------------

## utility.hpp

- `MTL_ASSERT_MSG` [(Documentation)](../mtl/utility.hpp#L23) [(Examples)](../tests/tests_utility.cpp#L20)
- [**CLASS**] `mtl::no_copy` [(Documentation)](../mtl/utility.hpp#L43) [(Examples)](../tests/tests_utility.cpp#L75)
- [**CLASS**] `mtl::no_move` [(Documentation)](../mtl/utility.hpp#L60) [(Examples)](../tests/tests_utility.cpp#L99)

---------------------------------------------------

## xoroshiro128plus.hpp

- [**CLASS**] `mtl::xoroshiro128plus_engine` [(Documentation)](../mtl/xoroshiro128plus.hpp#L31) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L30)
  - `mtl::xoroshiro128plus_engine::xoroshiro128plus_engine` [(Documentation)](../mtl/xoroshiro128plus.hpp#L31) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L32)
  - `mtl::xoroshiro128plus_engine::operator=` [(Documentation)](../mtl/xoroshiro128plus.hpp#L189) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L34)
  - `mtl::xoroshiro128plus_engine::seed` [(Documentation)](../mtl/xoroshiro128plus.hpp#L223) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L36)
  - `mtl::xoroshiro128plus_engine::min` [(Documentation)](../mtl/xoroshiro128plus.hpp#L264) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L38)
  - `mtl::xoroshiro128plus_engine::max` [(Documentation)](../mtl/xoroshiro128plus.hpp#L273) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L40)
  - `mtl::xoroshiro128plus_engine::operator()` [(Documentation)](../mtl/xoroshiro128plus.hpp#L282) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L42)
  - `mtl::xoroshiro128plus_engine::generate` [(Documentation)](../mtl/xoroshiro128plus.hpp#L300) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L44)
  - `mtl::xoroshiro128plus_engine::discard` [(Documentation)](../mtl/xoroshiro128plus.hpp#L317) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L46)
  - `mtl::xoroshiro128plus_engine::operator<<` [(Documentation)](../mtl/xoroshiro128plus.hpp#L331) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L48)
  - `mtl::xoroshiro128plus_engine::operator>>` [(Documentation)](../mtl/xoroshiro128plus.hpp#L348) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L50)
  - `mtl::xoroshiro128plus_engine::operator==` [(Documentation)](../mtl/xoroshiro128plus.hpp#L367) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L52)
  - `mtl::xoroshiro128plus_engine::operator!=` [(Documentation)](../mtl/xoroshiro128plus.hpp#L380) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L54)
- [**CLASS**] `mtl::xoroshiro128plus` [(Documentation)](../mtl/xoroshiro128plus.hpp#L395) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L56)

---------------------------------------------------

## xorshift128plus.hpp

- [**CLASS**] `mtl::xorshift128plus_engine` [(Documentation)](../mtl/xorshift128plus.hpp#L31) [(Examples)](../tests/tests_xorshift128plus.cpp#L32)
  - `mtl::xorshift128plus_engine::xorshift128plus_engine` [(Documentation)](../mtl/xorshift128plus.hpp#L31) [(Examples)](../tests/tests_xorshift128plus.cpp#L34)
  - `mtl::xorshift128plus_engine::operator=` [(Documentation)](../mtl/xorshift128plus.hpp#L192) [(Examples)](../tests/tests_xorshift128plus.cpp#L36)
  - `mtl::xorshift128plus_engine::seed` [(Documentation)](../mtl/xorshift128plus.hpp#L226) [(Examples)](../tests/tests_xorshift128plus.cpp#L38)
  - `mtl::xorshift128plus_engine::min` [(Documentation)](../mtl/xorshift128plus.hpp#L267) [(Examples)](../tests/tests_xorshift128plus.cpp#L40)
  - `mtl::xorshift128plus_engine::max` [(Documentation)](../mtl/xorshift128plus.hpp#L276) [(Examples)](../tests/tests_xorshift128plus.cpp#L42)
  - `mtl::xorshift128plus_engine::operator()` [(Documentation)](../mtl/xorshift128plus.hpp#L285) [(Examples)](../tests/tests_xorshift128plus.cpp#L44)
  - `mtl::xorshift128plus_engine::generate` [(Documentation)](../mtl/xorshift128plus.hpp#L305) [(Examples)](../tests/tests_xorshift128plus.cpp#L46)
  - `mtl::xorshift128plus_engine::discard` [(Documentation)](../mtl/xorshift128plus.hpp#L322) [(Examples)](../tests/tests_xorshift128plus.cpp#L48)
  - `mtl::xorshift128plus_engine::operator<<` [(Documentation)](../mtl/xorshift128plus.hpp#L336) [(Examples)](../tests/tests_xorshift128plus.cpp#L50)
  - `mtl::xorshift128plus_engine::operator>>` [(Documentation)](../mtl/xorshift128plus.hpp#L353) [(Examples)](../tests/tests_xorshift128plus.cpp#L52)
  - `mtl::xorshift128plus_engine::operator==` [(Documentation)](../mtl/xorshift128plus.hpp#L372) [(Examples)](../tests/tests_xorshift128plus.cpp#L54)
  - `mtl::xorshift128plus_engine::operator!=` [(Documentation)](../mtl/xorshift128plus.hpp#L385) [(Examples)](../tests/tests_xorshift128plus.cpp#L56)
- [**CLASS**] `mtl::xorshift128plus` [(Documentation)](../mtl/xorshift128plus.hpp#L399) [(Examples)](../tests/tests_xorshift128plus.cpp#L58)

---------------------------------------------------

## xoshiro256plus.hpp

- [**CLASS**] `mtl::xoshiro256plus_engine` [(Documentation)](../mtl/xoshiro256plus.hpp#L27) [(Examples)](../tests/tests_xoshiro256plus.cpp#L32)
  - `mtl::xoshiro256plus_engine::xoshiro256plus_engine` [(Documentation)](../mtl/xoshiro256plus.hpp#L27) [(Examples)](../tests/tests_xoshiro256plus.cpp#L34)
  - `mtl::xoshiro256plus_engine::operator=` [(Documentation)](../mtl/xoshiro256plus.hpp#L224) [(Examples)](../tests/tests_xoshiro256plus.cpp#L36)
  - `mtl::xoshiro256plus_engine::seed` [(Documentation)](../mtl/xoshiro256plus.hpp#L258) [(Examples)](../tests/tests_xoshiro256plus.cpp#L38)
  - `mtl::xoshiro256plus_engine::min` [(Documentation)](../mtl/xoshiro256plus.hpp#L316) [(Examples)](../tests/tests_xoshiro256plus.cpp#L40)
  - `mtl::xoshiro256plus_engine::max` [(Documentation)](../mtl/xoshiro256plus.hpp#L325) [(Examples)](../tests/tests_xoshiro256plus.cpp#L42)
  - `mtl::xoshiro256plus_engine::operator()` [(Documentation)](../mtl/xoshiro256plus.hpp#L334) [(Examples)](../tests/tests_xoshiro256plus.cpp#L44)
  - `mtl::xoshiro256plus_engine::generate` [(Documentation)](../mtl/xoshiro256plus.hpp#L355) [(Examples)](../tests/tests_xoshiro256plus.cpp#L46)
  - `mtl::xoshiro256plus_engine::discard` [(Documentation)](../mtl/xoshiro256plus.hpp#L372) [(Examples)](../tests/tests_xoshiro256plus.cpp#L48)
  - `mtl::xoshiro256plus_engine::operator<<` [(Documentation)](../mtl/xoshiro256plus.hpp#L386) [(Examples)](../tests/tests_xoshiro256plus.cpp#L50)
  - `mtl::xoshiro256plus_engine::operator>>` [(Documentation)](../mtl/xoshiro256plus.hpp#L404) [(Examples)](../tests/tests_xoshiro256plus.cpp#L52)
  - `mtl::xoshiro256plus_engine::operator==` [(Documentation)](../mtl/xoshiro256plus.hpp#L425) [(Examples)](../tests/tests_xoshiro256plus.cpp#L54)
  - `mtl::xoshiro256plus_engine::operator!=` [(Documentation)](../mtl/xoshiro256plus.hpp#L438) [(Examples)](../tests/tests_xoshiro256plus.cpp#L56)
- [**CLASS**] `mtl::xoshiro256plus` [(Documentation)](../mtl/xoshiro256plus.hpp#L452) [(Examples)](../tests/tests_xoshiro256plus.cpp#L58)
