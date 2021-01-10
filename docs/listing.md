# List of classes and functions

 | [algorithm.hpp](#algorithmhpp) | [console.hpp](#consolehpp) | [container.hpp](#containerhpp) | [conversion.hpp](#conversionhpp) | [filesystem.hpp](#filesystemhpp) | [math.hpp](#mathhpp) | [numeric.hpp](#numerichpp) | [random.hpp](#randomhpp) | [safety.hpp](#safetyhpp) | [stopwatch.hpp](#stopwatchhpp) | [string.hpp](#stringhpp) | [type_traits.hpp](#type_traitshpp) | [utility.hpp](#utilityhpp) | [xoroshiro128plus.hpp](#xoroshiro128plushpp) | [xorshift128plus.hpp](#xorshift128plushpp) | [xoshiro256plus.hpp](#xoshiro256plushpp) |

## Statistics

There are 16 headers.

There are 10 classes.

There are 52 class member functions.

There are 116 non-member functions.

## algorithm.hpp

- `mtl::not_unique_inclusive` [(Documentation)](../mtl/algorithm.hpp#L35) [(Examples)](../tests/tests_algorithm.cpp#L40)
- `mtl::not_unique_exclusive` [(Documentation)](../mtl/algorithm.hpp#L37) [(Examples)](../tests/tests_algorithm.cpp#L225)
- `mtl::not_unique` [(Documentation)](../mtl/algorithm.hpp#L39) [(Examples)](../tests/tests_algorithm.cpp#L407)
- `mtl::keep_duplicates_inclusive` [(Documentation)](../mtl/algorithm.hpp#L457) [(Examples)](../tests/tests_algorithm.cpp#L584)
- `mtl::keep_duplicates_exclusive` [(Documentation)](../mtl/algorithm.hpp#L605) [(Examples)](../tests/tests_algorithm.cpp#L751)
- `mtl::keep_duplicates` [(Documentation)](../mtl/algorithm.hpp#L735) [(Examples)](../tests/tests_algorithm.cpp#L910)
- `mtl::keep_duplicates_inclusive_sorted` [(Documentation)](../mtl/algorithm.hpp#L455) [(Examples)](../tests/tests_algorithm.cpp#L1074)
- `mtl::keep_duplicates_exclusive_sorted` [(Documentation)](../mtl/algorithm.hpp#L603) [(Examples)](../tests/tests_algorithm.cpp#L1264)
- `mtl::keep_duplicates_sorted` [(Documentation)](../mtl/algorithm.hpp#L733) [(Examples)](../tests/tests_algorithm.cpp#L1449)
- `mtl::keep_duplicates_inclusive_preserve` [(Documentation)](../mtl/algorithm.hpp#L459) [(Examples)](../tests/tests_algorithm.cpp#L1641)
- `mtl::keep_duplicates_exclusive_preserve` [(Documentation)](../mtl/algorithm.hpp#L607) [(Examples)](../tests/tests_algorithm.cpp#L1806)
- `mtl::keep_duplicates_preserve` [(Documentation)](../mtl/algorithm.hpp#L736) [(Examples)](../tests/tests_algorithm.cpp#L1973)
- `mtl::rem_duplicates_sorted` [(Documentation)](../mtl/algorithm.hpp#L254) [(Examples)](../tests/tests_algorithm.cpp#L2135)
- `mtl::rem_duplicates` [(Documentation)](../mtl/algorithm.hpp#L255) [(Examples)](../tests/tests_algorithm.cpp#L2324)
- `mtl::rem_duplicates_preserve` [(Documentation)](../mtl/algorithm.hpp#L256) [(Examples)](../tests/tests_algorithm.cpp#L2478)
- `mtl::contains` [(Documentation)](../mtl/algorithm.hpp#L849) [(Examples)](../tests/tests_algorithm.cpp#L2641)
- `mtl::contains_all` [(Documentation)](../mtl/algorithm.hpp#L902) [(Examples)](../tests/tests_algorithm.cpp#L2789)
- `mtl::contains_all_sorted` [(Documentation)](../mtl/algorithm.hpp#L903) [(Examples)](../tests/tests_algorithm.cpp#L2950)
- `mtl::for_each` [(Documentation)](../mtl/algorithm.hpp#L985) [(Examples)](../tests/tests_algorithm.cpp#L3111)
- `mtl::for_adj_pairs` [(Documentation)](../mtl/algorithm.hpp#L1070) [(Examples)](../tests/tests_algorithm.cpp#L3186)
- `mtl::for_all_pairs` [(Documentation)](../mtl/algorithm.hpp#L1099) [(Examples)](../tests/tests_algorithm.cpp#L3274)
- `mtl::fill_range` [(Documentation)](../mtl/algorithm.hpp#L1135) [(Examples)](../tests/tests_algorithm.cpp#L3366)
- `mtl::range` [(Documentation)](../mtl/algorithm.hpp#L1178) [(Examples)](../tests/tests_algorithm.cpp#L3488)

---------------------------------------------------

## console.hpp

- `mtl::console::print` [(Documentation)](../mtl/console.hpp#L165) [(Examples)](../tests/tests_console.cpp#L71)
- `mtl::console::println` [(Documentation)](../mtl/console.hpp#L194) [(Examples)](../tests/tests_console.cpp#L71)
- `mtl::console::print_all` [(Documentation)](../mtl/console.hpp#L228) [(Examples)](../tests/tests_console.cpp#L338)
- `mtl::console::print_color` [(Documentation)](../mtl/console.hpp#L481) [(Examples)](../tests/tests_console.cpp#L605)
- `mtl::console::println_color` [(Documentation)](../mtl/console.hpp#L482) [(Examples)](../tests/tests_console.cpp#L854)
- `mtl::console::overtype` [(Documentation)](../mtl/console.hpp#L1170) [(Examples)](../tests/tests_console.cpp#L1016)
- `mtl::console::clear` [(Documentation)](../mtl/console.hpp#L1228) [(Examples)](../tests/tests_console.cpp#L1396)

---------------------------------------------------

## container.hpp

- `mtl::reserve` [(Documentation)](../mtl/container.hpp#L21) [(Examples)](../tests/tests_container.cpp#L27)
- `mtl::push_back` [(Documentation)](../mtl/container.hpp#L46) [(Examples)](../tests/tests_container.cpp#L126)
- `mtl::emplace_back` [(Documentation)](../mtl/container.hpp#L70) [(Examples)](../tests/tests_container.cpp#L262)
- `mtl::slice` [(Documentation)](../mtl/container.hpp#L100) [(Examples)](../tests/tests_container.cpp#L401)
- `mtl::slice_n` [(Documentation)](../mtl/container.hpp#L101) [(Examples)](../tests/tests_container.cpp#L1281)

---------------------------------------------------

## conversion.hpp

- `mtl::to_num` [(Documentation)](../mtl/conversion.hpp#L26) [(Examples)](../tests/tests_conversion.cpp#L66)
- `mtl::to_num_noex` [(Documentation)](../mtl/conversion.hpp#L27) [(Examples)](../tests/tests_conversion.cpp#L481)
- `mtl::numeric_cast` [(Documentation)](../mtl/conversion.hpp#L717) [(Examples)](../tests/tests_conversion.cpp#L1511)
- `mtl::numeric_cast_noex` [(Documentation)](../mtl/conversion.hpp#L719) [(Examples)](../tests/tests_conversion.cpp#L2129)
- `mtl::rounding_cast` [(Documentation)](../mtl/conversion.hpp#L799) [(Examples)](../tests/tests_conversion.cpp#L4788)
- `mtl::rounding_cast_noex` [(Documentation)](../mtl/conversion.hpp#L800) [(Examples)](../tests/tests_conversion.cpp#L4881)

---------------------------------------------------

## filesystem.hpp

- `mtl::filesystem::read_file` [(Documentation)](../mtl/filesystem.hpp#L35) [(Examples)](../tests/tests_filesystem.cpp#L105)
- `mtl::filesystem::read_all_lines` [(Documentation)](../mtl/filesystem.hpp#L111) [(Examples)](../tests/tests_filesystem.cpp#L349)
- `mtl::filesystem::write_file` [(Documentation)](../mtl/filesystem.hpp#L244) [(Examples)](../tests/tests_filesystem.cpp#L76)
- `mtl::filesystem::write_all_lines` [(Documentation)](../mtl/filesystem.hpp#L283) [(Examples)](../tests/tests_filesystem.cpp#L867)

---------------------------------------------------

## math.hpp

- `mtl::approx_equal_abs` [(Documentation)](../mtl/math.hpp#L22) [(Examples)](../tests/tests_math.cpp#L26)
- `mtl::approx_equal_rel` [(Documentation)](../mtl/math.hpp#L23) [(Examples)](../tests/tests_math.cpp#L99)
- `mtl::approx_equal_comb` [(Documentation)](../mtl/math.hpp#L24) [(Examples)](../tests/tests_math.cpp#L171)
- `mtl::percent_whole` [(Documentation)](../mtl/math.hpp#L92) [(Examples)](../tests/tests_math.cpp#L282)
- `mtl::percent_portion` [(Documentation)](../mtl/math.hpp#L93) [(Examples)](../tests/tests_math.cpp#L598)
- `mtl::percent` [(Documentation)](../mtl/math.hpp#L94) [(Examples)](../tests/tests_math.cpp#L792)

---------------------------------------------------

## numeric.hpp

- `mtl::iota` [(Documentation)](../mtl/numeric.hpp#L27) [(Examples)](../tests/tests_numeric.cpp#L24)
- `mtl::frequency` [(Documentation)](../mtl/numeric.hpp#L54) [(Examples)](../tests/tests_numeric.cpp#L534)
- `mtl::mean` [(Documentation)](../mtl/numeric.hpp#L129) [(Examples)](../tests/tests_numeric.cpp#L755)
- `mtl::median` [(Documentation)](../mtl/numeric.hpp#L159) [(Examples)](../tests/tests_numeric.cpp#L1104)

---------------------------------------------------

## random.hpp

- [**CLASS**] `mtl::rng` [(Documentation)](../mtl/random.hpp#L27) [(Examples)](../tests/tests_random.cpp#L27)
  - `mtl::rng::rng` [(Documentation)](../mtl/random.hpp#L27) [(Examples)](../tests/tests_random.cpp#L29)
  - `mtl::rng::set_min_max` [(Documentation)](../mtl/random.hpp#L110) [(Examples)](../tests/tests_random.cpp#L31)
  - `mtl::rng::min` [(Documentation)](../mtl/random.hpp#L125) [(Examples)](../tests/tests_random.cpp#L33)
  - `mtl::rng::max` [(Documentation)](../mtl/random.hpp#L134) [(Examples)](../tests/tests_random.cpp#L35)
  - `mtl::rng::next` [(Documentation)](../mtl/random.hpp#L143) [(Examples)](../tests/tests_random.cpp#L37)
  - `mtl::rng::seed` [(Documentation)](../mtl/random.hpp#L152) [(Examples)](../tests/tests_random.cpp#L39)
  - `mtl::rng::seed_random` [(Documentation)](../mtl/random.hpp#L185) [(Examples)](../tests/tests_random.cpp#L41)
- `mtl::random_choice` [(Documentation)](../mtl/random.hpp#L197) [(Examples)](../tests/tests_random.cpp#L646)
- `mtl::shuffle` [(Documentation)](../mtl/random.hpp#L250) [(Examples)](../tests/tests_random.cpp#L1117)

---------------------------------------------------

## safety.hpp

- `mtl::safe_copy` [(Documentation)](../mtl/safety.hpp#L25) [(Examples)](../tests/tests_safety.cpp#L30)
- `mtl::safe_copy_n` [(Documentation)](../mtl/safety.hpp#L26) [(Examples)](../tests/tests_safety.cpp#L695)

---------------------------------------------------

## stopwatch.hpp

- [**CLASS**] `mtl::chrono::stopwatch` [(Documentation)](../mtl/stopwatch.hpp#L25) [(Examples)](../tests/tests_stopwatch.cpp#L26)
  - `mtl::chrono::stopwatch::start` [(Documentation)](../mtl/stopwatch.hpp#L38) [(Examples)](../tests/tests_stopwatch.cpp#L28)
  - `mtl::chrono::stopwatch::stop` [(Documentation)](../mtl/stopwatch.hpp#L48) [(Examples)](../tests/tests_stopwatch.cpp#L30)
  - `mtl::chrono::stopwatch::reset` [(Documentation)](../mtl/stopwatch.hpp#L58) [(Examples)](../tests/tests_stopwatch.cpp#L32)
  - `mtl::chrono::stopwatch::restart` [(Documentation)](../mtl/stopwatch.hpp#L69) [(Examples)](../tests/tests_stopwatch.cpp#L34)
  - `mtl::chrono::stopwatch::elapsed_minutes` [(Documentation)](../mtl/stopwatch.hpp#L79) [(Examples)](../tests/tests_stopwatch.cpp#L36)
  - `mtl::chrono::stopwatch::elapsed_seconds` [(Documentation)](../mtl/stopwatch.hpp#L95) [(Examples)](../tests/tests_stopwatch.cpp#L38)
  - `mtl::chrono::stopwatch::elapsed_milli` [(Documentation)](../mtl/stopwatch.hpp#L108) [(Examples)](../tests/tests_stopwatch.cpp#L40)
  - `mtl::chrono::stopwatch::elapsed_micro` [(Documentation)](../mtl/stopwatch.hpp#L121) [(Examples)](../tests/tests_stopwatch.cpp#L42)
  - `mtl::chrono::stopwatch::elapsed_nano` [(Documentation)](../mtl/stopwatch.hpp#L134) [(Examples)](../tests/tests_stopwatch.cpp#L44)

---------------------------------------------------

## string.hpp

- `mtl::string::is_upper` [(Documentation)](../mtl/string.hpp#L40) [(Examples)](../tests/tests_string.cpp#L85)
- `mtl::string::is_lower` [(Documentation)](../mtl/string.hpp#L42) [(Examples)](../tests/tests_string.cpp#L85)
- `mtl::string::to_upper` [(Documentation)](../mtl/string.hpp#L113) [(Examples)](../tests/tests_string.cpp#L153)
- `mtl::string::to_lower` [(Documentation)](../mtl/string.hpp#L115) [(Examples)](../tests/tests_string.cpp#L153)
- `mtl::string::is_ascii` [(Documentation)](../mtl/string.hpp#L168) [(Examples)](../tests/tests_string.cpp#L241)
- `mtl::string::is_alphabetic` [(Documentation)](../mtl/string.hpp#L220) [(Examples)](../tests/tests_string.cpp#L289)
- `mtl::string::is_numeric` [(Documentation)](../mtl/string.hpp#L222) [(Examples)](../tests/tests_string.cpp#L289)
- `mtl::string::is_alphanum` [(Documentation)](../mtl/string.hpp#L223) [(Examples)](../tests/tests_string.cpp#L289)
- `mtl::string::contains` [(Documentation)](../mtl/string.hpp#L327) [(Examples)](../tests/tests_string.cpp#L396)
- `mtl::string::strip_front` [(Documentation)](../mtl/string.hpp#L397) [(Examples)](../tests/tests_string.cpp#L472)
- `mtl::string::strip_back` [(Documentation)](../mtl/string.hpp#L398) [(Examples)](../tests/tests_string.cpp#L472)
- `mtl::string::strip` [(Documentation)](../mtl/string.hpp#L399) [(Examples)](../tests/tests_string.cpp#L472)
- `mtl::string::pad_front` [(Documentation)](../mtl/string.hpp#L472) [(Examples)](../tests/tests_string.cpp#L706)
- `mtl::string::pad_back` [(Documentation)](../mtl/string.hpp#L475) [(Examples)](../tests/tests_string.cpp#L706)
- `mtl::string::pad` [(Documentation)](../mtl/string.hpp#L478) [(Examples)](../tests/tests_string.cpp#L706)
- `mtl::string::to_string` [(Documentation)](../mtl/string.hpp#L638) [(Examples)](../tests/tests_string.cpp#L924)
- `mtl::string::join_all` [(Documentation)](../mtl/string.hpp#L754) [(Examples)](../tests/tests_string.cpp#L1017)
- `mtl::string::join` [(Documentation)](../mtl/string.hpp#L930) [(Examples)](../tests/tests_string.cpp#L1240)
- `mtl::string::split` [(Documentation)](../mtl/string.hpp#L1067) [(Examples)](../tests/tests_string.cpp#L1286)
- `mtl::string::replace` [(Documentation)](../mtl/string.hpp#L1205) [(Examples)](../tests/tests_string.cpp#L2394)
- `mtl::string::replace_all` [(Documentation)](../mtl/string.hpp#L1513) [(Examples)](../tests/tests_string.cpp#L3052)

---------------------------------------------------

## type_traits.hpp

- `mtl::are_same` [(Documentation)](../mtl/type_traits.hpp#L36) [(Examples)](../tests/tests_type_traits.cpp#L40)
- `mtl::has_reserve` [(Documentation)](../mtl/type_traits.hpp#L61) [(Examples)](../tests/tests_type_traits.cpp#L100)
- `mtl::has_push_back` [(Documentation)](../mtl/type_traits.hpp#L84) [(Examples)](../tests/tests_type_traits.cpp#L144)
- `mtl::has_emplace_back` [(Documentation)](../mtl/type_traits.hpp#L105) [(Examples)](../tests/tests_type_traits.cpp#L184)
- `mtl::has_size` [(Documentation)](../mtl/type_traits.hpp#L158) [(Examples)](../tests/tests_type_traits.cpp#L227)
- `mtl::has_find` [(Documentation)](../mtl/type_traits.hpp#L180) [(Examples)](../tests/tests_type_traits.cpp#L269)
- `mtl::is_sint` [(Documentation)](../mtl/type_traits.hpp#L254) [(Examples)](../tests/tests_type_traits.cpp#L324)
- `mtl::is_uint` [(Documentation)](../mtl/type_traits.hpp#L256) [(Examples)](../tests/tests_type_traits.cpp#L473)
- `mtl::is_int` [(Documentation)](../mtl/type_traits.hpp#L258) [(Examples)](../tests/tests_type_traits.cpp#L622)
- `mtl::is_float` [(Documentation)](../mtl/type_traits.hpp#L260) [(Examples)](../tests/tests_type_traits.cpp#L769)
- `mtl::is_number` [(Documentation)](../mtl/type_traits.hpp#L262) [(Examples)](../tests/tests_type_traits.cpp#L833)
- `mtl::is_char` [(Documentation)](../mtl/type_traits.hpp#L264) [(Examples)](../tests/tests_type_traits.cpp#L994)
- `mtl::is_std_array` [(Documentation)](../mtl/type_traits.hpp#L360) [(Examples)](../tests/tests_type_traits.cpp#L1063)
- `mtl::is_std_vector` [(Documentation)](../mtl/type_traits.hpp#L380) [(Examples)](../tests/tests_type_traits.cpp#L1085)
- `mtl::is_std_deque` [(Documentation)](../mtl/type_traits.hpp#L400) [(Examples)](../tests/tests_type_traits.cpp#L1107)
- `mtl::is_std_forward_list` [(Documentation)](../mtl/type_traits.hpp#L420) [(Examples)](../tests/tests_type_traits.cpp#L1129)
- `mtl::is_std_list` [(Documentation)](../mtl/type_traits.hpp#L440) [(Examples)](../tests/tests_type_traits.cpp#L1154)
- `mtl::is_std_set` [(Documentation)](../mtl/type_traits.hpp#L460) [(Examples)](../tests/tests_type_traits.cpp#L1176)
- `mtl::is_std_multiset` [(Documentation)](../mtl/type_traits.hpp#L480) [(Examples)](../tests/tests_type_traits.cpp#L1200)
- `mtl::is_std_map` [(Documentation)](../mtl/type_traits.hpp#L500) [(Examples)](../tests/tests_type_traits.cpp#L1226)
- `mtl::is_std_multimap` [(Documentation)](../mtl/type_traits.hpp#L520) [(Examples)](../tests/tests_type_traits.cpp#L1250)
- `mtl::is_std_unordered_set` [(Documentation)](../mtl/type_traits.hpp#L540) [(Examples)](../tests/tests_type_traits.cpp#L1275)
- `mtl::is_std_unordered_map` [(Documentation)](../mtl/type_traits.hpp#L560) [(Examples)](../tests/tests_type_traits.cpp#L1325)
- `mtl::is_std_unordered_multiset` [(Documentation)](../mtl/type_traits.hpp#L580) [(Examples)](../tests/tests_type_traits.cpp#L1300)
- `mtl::is_std_unordered_multimap` [(Documentation)](../mtl/type_traits.hpp#L600) [(Examples)](../tests/tests_type_traits.cpp#L1350)
- `mtl::is_std_stack` [(Documentation)](../mtl/type_traits.hpp#L620) [(Examples)](../tests/tests_type_traits.cpp#L1376)
- `mtl::is_std_queue` [(Documentation)](../mtl/type_traits.hpp#L640) [(Examples)](../tests/tests_type_traits.cpp#L1400)
- `mtl::is_std_priority_queue` [(Documentation)](../mtl/type_traits.hpp#L660) [(Examples)](../tests/tests_type_traits.cpp#L1424)
- `mtl::is_std_container` [(Documentation)](../mtl/type_traits.hpp#L680) [(Examples)](../tests/tests_type_traits.cpp#L1449)
- `mtl::is_std_pair` [(Documentation)](../mtl/type_traits.hpp#L709) [(Examples)](../tests/tests_type_traits.cpp#L1478)
- `mtl::is_std_string` [(Documentation)](../mtl/type_traits.hpp#L732) [(Examples)](../tests/tests_type_traits.cpp#L1530)
- `mtl::is_c_string` [(Documentation)](../mtl/type_traits.hpp#L752) [(Examples)](../tests/tests_type_traits.cpp#L1614)
- `mtl::is_input_iterator` [(Documentation)](../mtl/type_traits.hpp#L771) [(Examples)](../tests/tests_type_traits.cpp#L1644)
- `mtl::is_output_iterator` [(Documentation)](../mtl/type_traits.hpp#L773) [(Examples)](../tests/tests_type_traits.cpp#L1644)
- `mtl::is_iterator` [(Documentation)](../mtl/type_traits.hpp#L775) [(Examples)](../tests/tests_type_traits.cpp#L1644)

---------------------------------------------------

## utility.hpp

- `MTL_ASSERT_MSG` [(Documentation)](../mtl/utility.hpp#L20) [(Examples)](../tests/tests_utility.cpp#L20)
- [**CLASS**] `mtl::no_copy` [(Documentation)](../mtl/utility.hpp#L40) [(Examples)](../tests/tests_utility.cpp#L75)
- [**CLASS**] `mtl::no_move` [(Documentation)](../mtl/utility.hpp#L57) [(Examples)](../tests/tests_utility.cpp#L99)

---------------------------------------------------

## xoroshiro128plus.hpp

- [**CLASS**] `mtl::xoroshiro128plus_engine` [(Documentation)](../mtl/xoroshiro128plus.hpp#L27) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L30)
  - `mtl::xoroshiro128plus_engine::xoroshiro128plus_engine` [(Documentation)](../mtl/xoroshiro128plus.hpp#L27) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L32)
  - `mtl::xoroshiro128plus_engine::operator=` [(Documentation)](../mtl/xoroshiro128plus.hpp#L185) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L34)
  - `mtl::xoroshiro128plus_engine::seed` [(Documentation)](../mtl/xoroshiro128plus.hpp#L219) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L36)
  - `mtl::xoroshiro128plus_engine::min` [(Documentation)](../mtl/xoroshiro128plus.hpp#L260) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L38)
  - `mtl::xoroshiro128plus_engine::max` [(Documentation)](../mtl/xoroshiro128plus.hpp#L269) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L40)
  - `mtl::xoroshiro128plus_engine::operator()` [(Documentation)](../mtl/xoroshiro128plus.hpp#L278) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L42)
  - `mtl::xoroshiro128plus_engine::generate` [(Documentation)](../mtl/xoroshiro128plus.hpp#L296) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L44)
  - `mtl::xoroshiro128plus_engine::discard` [(Documentation)](../mtl/xoroshiro128plus.hpp#L313) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L46)
  - `mtl::xoroshiro128plus_engine::operator<<` [(Documentation)](../mtl/xoroshiro128plus.hpp#L327) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L48)
  - `mtl::xoroshiro128plus_engine::operator>>` [(Documentation)](../mtl/xoroshiro128plus.hpp#L344) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L50)
  - `mtl::xoroshiro128plus_engine::operator==` [(Documentation)](../mtl/xoroshiro128plus.hpp#L363) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L52)
  - `mtl::xoroshiro128plus_engine::operator!=` [(Documentation)](../mtl/xoroshiro128plus.hpp#L376) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L54)
- [**CLASS**] `mtl::xoroshiro128plus` [(Documentation)](../mtl/xoroshiro128plus.hpp#L391) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L56)

---------------------------------------------------

## xorshift128plus.hpp

- [**CLASS**] `mtl::xorshift128plus_engine` [(Documentation)](../mtl/xorshift128plus.hpp#L27) [(Examples)](../tests/tests_xorshift128plus.cpp#L32)
  - `mtl::xorshift128plus_engine::xorshift128plus_engine` [(Documentation)](../mtl/xorshift128plus.hpp#L27) [(Examples)](../tests/tests_xorshift128plus.cpp#L34)
  - `mtl::xorshift128plus_engine::operator=` [(Documentation)](../mtl/xorshift128plus.hpp#L188) [(Examples)](../tests/tests_xorshift128plus.cpp#L36)
  - `mtl::xorshift128plus_engine::seed` [(Documentation)](../mtl/xorshift128plus.hpp#L222) [(Examples)](../tests/tests_xorshift128plus.cpp#L38)
  - `mtl::xorshift128plus_engine::min` [(Documentation)](../mtl/xorshift128plus.hpp#L263) [(Examples)](../tests/tests_xorshift128plus.cpp#L40)
  - `mtl::xorshift128plus_engine::max` [(Documentation)](../mtl/xorshift128plus.hpp#L272) [(Examples)](../tests/tests_xorshift128plus.cpp#L42)
  - `mtl::xorshift128plus_engine::operator()` [(Documentation)](../mtl/xorshift128plus.hpp#L281) [(Examples)](../tests/tests_xorshift128plus.cpp#L44)
  - `mtl::xorshift128plus_engine::generate` [(Documentation)](../mtl/xorshift128plus.hpp#L301) [(Examples)](../tests/tests_xorshift128plus.cpp#L46)
  - `mtl::xorshift128plus_engine::discard` [(Documentation)](../mtl/xorshift128plus.hpp#L318) [(Examples)](../tests/tests_xorshift128plus.cpp#L48)
  - `mtl::xorshift128plus_engine::operator<<` [(Documentation)](../mtl/xorshift128plus.hpp#L332) [(Examples)](../tests/tests_xorshift128plus.cpp#L50)
  - `mtl::xorshift128plus_engine::operator>>` [(Documentation)](../mtl/xorshift128plus.hpp#L349) [(Examples)](../tests/tests_xorshift128plus.cpp#L52)
  - `mtl::xorshift128plus_engine::operator==` [(Documentation)](../mtl/xorshift128plus.hpp#L368) [(Examples)](../tests/tests_xorshift128plus.cpp#L54)
  - `mtl::xorshift128plus_engine::operator!=` [(Documentation)](../mtl/xorshift128plus.hpp#L381) [(Examples)](../tests/tests_xorshift128plus.cpp#L56)
- [**CLASS**] `mtl::xorshift128plus` [(Documentation)](../mtl/xorshift128plus.hpp#L395) [(Examples)](../tests/tests_xorshift128plus.cpp#L58)

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
