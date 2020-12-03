# List of classes and functions

 | [algorithm.hpp](#algorithmhpp) | [console.hpp](#consolehpp) | [container.hpp](#containerhpp) | [conversion.hpp](#conversionhpp) | [filesystem.hpp](#filesystemhpp) | [math.hpp](#mathhpp) | [numeric.hpp](#numerichpp) | [random.hpp](#randomhpp) | [safety.hpp](#safetyhpp) | [stopwatch.hpp](#stopwatchhpp) | [string.hpp](#stringhpp) | [type_traits.hpp](#type_traitshpp) | [utility.hpp](#utilityhpp) | [xoroshiro128plus.hpp](#xoroshiro128plushpp) | [xorshift128plus.hpp](#xorshift128plushpp) | [xoshiro256plus.hpp](#xoshiro256plushpp) |

## Statistics

There are 16 headers.

There are 10 classes.

There are 52 class member functions.

There are 116 non-member functions.

## algorithm.hpp

- `mtl::not_unique_inclusive` [(Documentation)](../mtl/algorithm.hpp#L33) [(Examples)](../tests/tests_algorithm.cpp#L38)
- `mtl::not_unique_exclusive` [(Documentation)](../mtl/algorithm.hpp#L35) [(Examples)](../tests/tests_algorithm.cpp#L38)
- `mtl::not_unique` [(Documentation)](../mtl/algorithm.hpp#L37) [(Examples)](../tests/tests_algorithm.cpp#L38)
- `mtl::keep_duplicates_inclusive` [(Documentation)](../mtl/algorithm.hpp#L455) [(Examples)](../tests/tests_algorithm.cpp#L325)
- `mtl::keep_duplicates_exclusive` [(Documentation)](../mtl/algorithm.hpp#L603) [(Examples)](../tests/tests_algorithm.cpp#L325)
- `mtl::keep_duplicates` [(Documentation)](../mtl/algorithm.hpp#L733) [(Examples)](../tests/tests_algorithm.cpp#L325)
- `mtl::keep_duplicates_inclusive_sorted` [(Documentation)](../mtl/algorithm.hpp#L453) [(Examples)](../tests/tests_algorithm.cpp#L521)
- `mtl::keep_duplicates_exclusive_sorted` [(Documentation)](../mtl/algorithm.hpp#L601) [(Examples)](../tests/tests_algorithm.cpp#L562)
- `mtl::keep_duplicates_sorted` [(Documentation)](../mtl/algorithm.hpp#L731) [(Examples)](../tests/tests_algorithm.cpp#L604)
- `mtl::keep_duplicates_inclusive_preserve` [(Documentation)](../mtl/algorithm.hpp#L457) [(Examples)](../tests/tests_algorithm.cpp#L754)
- `mtl::keep_duplicates_exclusive_preserve` [(Documentation)](../mtl/algorithm.hpp#L605) [(Examples)](../tests/tests_algorithm.cpp#L807)
- `mtl::keep_duplicates_preserve` [(Documentation)](../mtl/algorithm.hpp#L734) [(Examples)](../tests/tests_algorithm.cpp#L843)
- `mtl::rem_duplicates_sorted` [(Documentation)](../mtl/algorithm.hpp#L252) [(Examples)](../tests/tests_algorithm.cpp#L969)
- `mtl::rem_duplicates` [(Documentation)](../mtl/algorithm.hpp#L253) [(Examples)](../tests/tests_algorithm.cpp#L969)
- `mtl::rem_duplicates_preserve` [(Documentation)](../mtl/algorithm.hpp#L254) [(Examples)](../tests/tests_algorithm.cpp#L969)
- `mtl::contains` [(Documentation)](../mtl/algorithm.hpp#L846) [(Examples)](../tests/tests_algorithm.cpp#L1221)
- `mtl::contains_all` [(Documentation)](../mtl/algorithm.hpp#L899) [(Examples)](../tests/tests_algorithm.cpp#L1221)
- `mtl::contains_all_sorted` [(Documentation)](../mtl/algorithm.hpp#L900) [(Examples)](../tests/tests_algorithm.cpp#L1221)
- `mtl::fill_range` [(Documentation)](../mtl/algorithm.hpp#L981) [(Examples)](../tests/tests_algorithm.cpp#L1696)
- `mtl::for_each` [(Documentation)](../mtl/algorithm.hpp#L1023) [(Examples)](../tests/tests_algorithm.cpp#L1816)
- `mtl::for_adj_pairs` [(Documentation)](../mtl/algorithm.hpp#L1108) [(Examples)](../tests/tests_algorithm.cpp#L1879)
- `mtl::for_all_pairs` [(Documentation)](../mtl/algorithm.hpp#L1137) [(Examples)](../tests/tests_algorithm.cpp#L1879)
- `mtl::range` [(Documentation)](../mtl/algorithm.hpp#L1173) [(Examples)](../tests/tests_algorithm.cpp#L2058)

---------------------------------------------------

## console.hpp

- `mtl::console::print` [(Documentation)](../mtl/console.hpp#L154) [(Examples)](../tests/tests_console.cpp#L69)
- `mtl::console::println` [(Documentation)](../mtl/console.hpp#L183) [(Examples)](../tests/tests_console.cpp#L69)
- `mtl::console::print_all` [(Documentation)](../mtl/console.hpp#L217) [(Examples)](../tests/tests_console.cpp#L336)
- `mtl::console::print_color` [(Documentation)](../mtl/console.hpp#L469) [(Examples)](../tests/tests_console.cpp#L603)
- `mtl::console::println_color` [(Documentation)](../mtl/console.hpp#L470) [(Examples)](../tests/tests_console.cpp#L852)
- `mtl::console::overtype` [(Documentation)](../mtl/console.hpp#L1156) [(Examples)](../tests/tests_console.cpp#L1014)
- `mtl::console::clear` [(Documentation)](../mtl/console.hpp#L1214) [(Examples)](../tests/tests_console.cpp#L1394)

---------------------------------------------------

## container.hpp

- `mtl::reserve` [(Documentation)](../mtl/container.hpp#L19) [(Examples)](../tests/tests_container.cpp#L25)
- `mtl::push_back` [(Documentation)](../mtl/container.hpp#L44) [(Examples)](../tests/tests_container.cpp#L124)
- `mtl::emplace_back` [(Documentation)](../mtl/container.hpp#L68) [(Examples)](../tests/tests_container.cpp#L260)
- `mtl::slice` [(Documentation)](../mtl/container.hpp#L98) [(Examples)](../tests/tests_container.cpp#L399)
- `mtl::slice_n` [(Documentation)](../mtl/container.hpp#L99) [(Examples)](../tests/tests_container.cpp#L1279)

---------------------------------------------------

## conversion.hpp

- `mtl::to_num` [(Documentation)](../mtl/conversion.hpp#L23) [(Examples)](../tests/tests_conversion.cpp#L64)
- `mtl::to_num_noex` [(Documentation)](../mtl/conversion.hpp#L24) [(Examples)](../tests/tests_conversion.cpp#L479)
- `mtl::numeric_cast` [(Documentation)](../mtl/conversion.hpp#L706) [(Examples)](../tests/tests_conversion.cpp#L1509)
- `mtl::numeric_cast_noex` [(Documentation)](../mtl/conversion.hpp#L708) [(Examples)](../tests/tests_conversion.cpp#L2127)
- `mtl::rounding_cast` [(Documentation)](../mtl/conversion.hpp#L788) [(Examples)](../tests/tests_conversion.cpp#L4786)
- `mtl::rounding_cast_noex` [(Documentation)](../mtl/conversion.hpp#L789) [(Examples)](../tests/tests_conversion.cpp#L4879)

---------------------------------------------------

## filesystem.hpp

- `mtl::filesystem::read_file` [(Documentation)](../mtl/filesystem.hpp#L32) [(Examples)](../tests/tests_filesystem.cpp#L109)
- `mtl::filesystem::read_all_lines` [(Documentation)](../mtl/filesystem.hpp#L108) [(Examples)](../tests/tests_filesystem.cpp#L390)
- `mtl::filesystem::write_file` [(Documentation)](../mtl/filesystem.hpp#L230) [(Examples)](../tests/tests_filesystem.cpp#L71)
- `mtl::filesystem::write_all_lines` [(Documentation)](../mtl/filesystem.hpp#L269) [(Examples)](../tests/tests_filesystem.cpp#L781)

---------------------------------------------------

## math.hpp

- `mtl::approx_equal_abs` [(Documentation)](../mtl/math.hpp#L20) [(Examples)](../tests/tests_math.cpp#L24)
- `mtl::approx_equal_rel` [(Documentation)](../mtl/math.hpp#L21) [(Examples)](../tests/tests_math.cpp#L97)
- `mtl::approx_equal_comb` [(Documentation)](../mtl/math.hpp#L22) [(Examples)](../tests/tests_math.cpp#L169)
- `mtl::percent_whole` [(Documentation)](../mtl/math.hpp#L90) [(Examples)](../tests/tests_math.cpp#L280)
- `mtl::percent_portion` [(Documentation)](../mtl/math.hpp#L91) [(Examples)](../tests/tests_math.cpp#L596)
- `mtl::percent` [(Documentation)](../mtl/math.hpp#L92) [(Examples)](../tests/tests_math.cpp#L790)

---------------------------------------------------

## numeric.hpp

- `mtl::iota` [(Documentation)](../mtl/numeric.hpp#L25) [(Examples)](../tests/tests_numeric.cpp#L22)
- `mtl::frequency` [(Documentation)](../mtl/numeric.hpp#L52) [(Examples)](../tests/tests_numeric.cpp#L532)
- `mtl::mean` [(Documentation)](../mtl/numeric.hpp#L127) [(Examples)](../tests/tests_numeric.cpp#L753)
- `mtl::median` [(Documentation)](../mtl/numeric.hpp#L157) [(Examples)](../tests/tests_numeric.cpp#L1102)

---------------------------------------------------

## random.hpp

- [**CLASS**] `mtl::rng` [(Documentation)](../mtl/random.hpp#L25) [(Examples)](../tests/tests_random.cpp#L25)
  - `mtl::rng::rng` [(Documentation)](../mtl/random.hpp#L25) [(Examples)](../tests/tests_random.cpp#L27)
  - `mtl::rng::set_min_max` [(Documentation)](../mtl/random.hpp#L108) [(Examples)](../tests/tests_random.cpp#L29)
  - `mtl::rng::min` [(Documentation)](../mtl/random.hpp#L123) [(Examples)](../tests/tests_random.cpp#L31)
  - `mtl::rng::max` [(Documentation)](../mtl/random.hpp#L132) [(Examples)](../tests/tests_random.cpp#L33)
  - `mtl::rng::next` [(Documentation)](../mtl/random.hpp#L141) [(Examples)](../tests/tests_random.cpp#L35)
  - `mtl::rng::seed` [(Documentation)](../mtl/random.hpp#L150) [(Examples)](../tests/tests_random.cpp#L37)
  - `mtl::rng::seed_random` [(Documentation)](../mtl/random.hpp#L183) [(Examples)](../tests/tests_random.cpp#L39)
- `mtl::random_choice` [(Documentation)](../mtl/random.hpp#L195) [(Examples)](../tests/tests_random.cpp#L644)
- `mtl::shuffle` [(Documentation)](../mtl/random.hpp#L248) [(Examples)](../tests/tests_random.cpp#L1115)

---------------------------------------------------

## safety.hpp

- `mtl::safe_copy` [(Documentation)](../mtl/safety.hpp#L23) [(Examples)](../tests/tests_safety.cpp#L28)
- `mtl::safe_copy_n` [(Documentation)](../mtl/safety.hpp#L24) [(Examples)](../tests/tests_safety.cpp#L693)

---------------------------------------------------

## stopwatch.hpp

- [**CLASS**] `mtl::chrono::stopwatch` [(Documentation)](../mtl/stopwatch.hpp#L23) [(Examples)](../tests/tests_stopwatch.cpp#L24)
  - `mtl::chrono::stopwatch::start` [(Documentation)](../mtl/stopwatch.hpp#L36) [(Examples)](../tests/tests_stopwatch.cpp#L26)
  - `mtl::chrono::stopwatch::stop` [(Documentation)](../mtl/stopwatch.hpp#L46) [(Examples)](../tests/tests_stopwatch.cpp#L28)
  - `mtl::chrono::stopwatch::reset` [(Documentation)](../mtl/stopwatch.hpp#L56) [(Examples)](../tests/tests_stopwatch.cpp#L30)
  - `mtl::chrono::stopwatch::restart` [(Documentation)](../mtl/stopwatch.hpp#L67) [(Examples)](../tests/tests_stopwatch.cpp#L32)
  - `mtl::chrono::stopwatch::elapsed_minutes` [(Documentation)](../mtl/stopwatch.hpp#L77) [(Examples)](../tests/tests_stopwatch.cpp#L34)
  - `mtl::chrono::stopwatch::elapsed_seconds` [(Documentation)](../mtl/stopwatch.hpp#L93) [(Examples)](../tests/tests_stopwatch.cpp#L36)
  - `mtl::chrono::stopwatch::elapsed_milli` [(Documentation)](../mtl/stopwatch.hpp#L106) [(Examples)](../tests/tests_stopwatch.cpp#L38)
  - `mtl::chrono::stopwatch::elapsed_micro` [(Documentation)](../mtl/stopwatch.hpp#L119) [(Examples)](../tests/tests_stopwatch.cpp#L40)
  - `mtl::chrono::stopwatch::elapsed_nano` [(Documentation)](../mtl/stopwatch.hpp#L132) [(Examples)](../tests/tests_stopwatch.cpp#L42)

---------------------------------------------------

## string.hpp

- `mtl::string::is_upper` [(Documentation)](../mtl/string.hpp#L37) [(Examples)](../tests/tests_string.cpp#L83)
- `mtl::string::is_lower` [(Documentation)](../mtl/string.hpp#L39) [(Examples)](../tests/tests_string.cpp#L83)
- `mtl::string::to_upper` [(Documentation)](../mtl/string.hpp#L110) [(Examples)](../tests/tests_string.cpp#L151)
- `mtl::string::to_lower` [(Documentation)](../mtl/string.hpp#L112) [(Examples)](../tests/tests_string.cpp#L151)
- `mtl::string::is_ascii` [(Documentation)](../mtl/string.hpp#L165) [(Examples)](../tests/tests_string.cpp#L239)
- `mtl::string::is_alphabetic` [(Documentation)](../mtl/string.hpp#L217) [(Examples)](../tests/tests_string.cpp#L287)
- `mtl::string::is_numeric` [(Documentation)](../mtl/string.hpp#L219) [(Examples)](../tests/tests_string.cpp#L287)
- `mtl::string::is_alphanum` [(Documentation)](../mtl/string.hpp#L220) [(Examples)](../tests/tests_string.cpp#L287)
- `mtl::string::contains` [(Documentation)](../mtl/string.hpp#L324) [(Examples)](../tests/tests_string.cpp#L394)
- `mtl::string::strip_front` [(Documentation)](../mtl/string.hpp#L394) [(Examples)](../tests/tests_string.cpp#L470)
- `mtl::string::strip_back` [(Documentation)](../mtl/string.hpp#L395) [(Examples)](../tests/tests_string.cpp#L470)
- `mtl::string::strip` [(Documentation)](../mtl/string.hpp#L396) [(Examples)](../tests/tests_string.cpp#L470)
- `mtl::string::pad_front` [(Documentation)](../mtl/string.hpp#L466) [(Examples)](../tests/tests_string.cpp#L630)
- `mtl::string::pad_back` [(Documentation)](../mtl/string.hpp#L469) [(Examples)](../tests/tests_string.cpp#L630)
- `mtl::string::pad` [(Documentation)](../mtl/string.hpp#L472) [(Examples)](../tests/tests_string.cpp#L630)
- `mtl::string::to_string` [(Documentation)](../mtl/string.hpp#L630) [(Examples)](../tests/tests_string.cpp#L848)
- `mtl::string::join_all` [(Documentation)](../mtl/string.hpp#L747) [(Examples)](../tests/tests_string.cpp#L941)
- `mtl::string::join` [(Documentation)](../mtl/string.hpp#L924) [(Examples)](../tests/tests_string.cpp#L941)
- `mtl::string::split` [(Documentation)](../mtl/string.hpp#L1062) [(Examples)](../tests/tests_string.cpp#L1139)
- `mtl::string::replace` [(Documentation)](../mtl/string.hpp#L1191) [(Examples)](../tests/tests_string.cpp#L1683)
- `mtl::string::replace_all` [(Documentation)](../mtl/string.hpp#L1499) [(Examples)](../tests/tests_string.cpp#L2341)

---------------------------------------------------

## type_traits.hpp

- `mtl::are_same` [(Documentation)](../mtl/type_traits.hpp#L34) [(Examples)](../tests/tests_type_traits.cpp#L38)
- `mtl::has_reserve` [(Documentation)](../mtl/type_traits.hpp#L59) [(Examples)](../tests/tests_type_traits.cpp#L98)
- `mtl::has_push_back` [(Documentation)](../mtl/type_traits.hpp#L82) [(Examples)](../tests/tests_type_traits.cpp#L142)
- `mtl::has_emplace_back` [(Documentation)](../mtl/type_traits.hpp#L103) [(Examples)](../tests/tests_type_traits.cpp#L182)
- `mtl::has_size` [(Documentation)](../mtl/type_traits.hpp#L156) [(Examples)](../tests/tests_type_traits.cpp#L225)
- `mtl::has_find` [(Documentation)](../mtl/type_traits.hpp#L178) [(Examples)](../tests/tests_type_traits.cpp#L267)
- `mtl::is_sint` [(Documentation)](../mtl/type_traits.hpp#L252) [(Examples)](../tests/tests_type_traits.cpp#L322)
- `mtl::is_uint` [(Documentation)](../mtl/type_traits.hpp#L254) [(Examples)](../tests/tests_type_traits.cpp#L471)
- `mtl::is_int` [(Documentation)](../mtl/type_traits.hpp#L256) [(Examples)](../tests/tests_type_traits.cpp#L620)
- `mtl::is_float` [(Documentation)](../mtl/type_traits.hpp#L258) [(Examples)](../tests/tests_type_traits.cpp#L767)
- `mtl::is_number` [(Documentation)](../mtl/type_traits.hpp#L260) [(Examples)](../tests/tests_type_traits.cpp#L831)
- `mtl::is_char` [(Documentation)](../mtl/type_traits.hpp#L262) [(Examples)](../tests/tests_type_traits.cpp#L992)
- `mtl::is_std_array` [(Documentation)](../mtl/type_traits.hpp#L358) [(Examples)](../tests/tests_type_traits.cpp#L1061)
- `mtl::is_std_vector` [(Documentation)](../mtl/type_traits.hpp#L378) [(Examples)](../tests/tests_type_traits.cpp#L1083)
- `mtl::is_std_deque` [(Documentation)](../mtl/type_traits.hpp#L398) [(Examples)](../tests/tests_type_traits.cpp#L1105)
- `mtl::is_std_forward_list` [(Documentation)](../mtl/type_traits.hpp#L418) [(Examples)](../tests/tests_type_traits.cpp#L1127)
- `mtl::is_std_list` [(Documentation)](../mtl/type_traits.hpp#L438) [(Examples)](../tests/tests_type_traits.cpp#L1152)
- `mtl::is_std_set` [(Documentation)](../mtl/type_traits.hpp#L458) [(Examples)](../tests/tests_type_traits.cpp#L1174)
- `mtl::is_std_multiset` [(Documentation)](../mtl/type_traits.hpp#L478) [(Examples)](../tests/tests_type_traits.cpp#L1198)
- `mtl::is_std_map` [(Documentation)](../mtl/type_traits.hpp#L498) [(Examples)](../tests/tests_type_traits.cpp#L1224)
- `mtl::is_std_multimap` [(Documentation)](../mtl/type_traits.hpp#L518) [(Examples)](../tests/tests_type_traits.cpp#L1248)
- `mtl::is_std_unordered_set` [(Documentation)](../mtl/type_traits.hpp#L538) [(Examples)](../tests/tests_type_traits.cpp#L1273)
- `mtl::is_std_unordered_map` [(Documentation)](../mtl/type_traits.hpp#L558) [(Examples)](../tests/tests_type_traits.cpp#L1323)
- `mtl::is_std_unordered_multiset` [(Documentation)](../mtl/type_traits.hpp#L578) [(Examples)](../tests/tests_type_traits.cpp#L1298)
- `mtl::is_std_unordered_multimap` [(Documentation)](../mtl/type_traits.hpp#L598) [(Examples)](../tests/tests_type_traits.cpp#L1348)
- `mtl::is_std_stack` [(Documentation)](../mtl/type_traits.hpp#L618) [(Examples)](../tests/tests_type_traits.cpp#L1374)
- `mtl::is_std_queue` [(Documentation)](../mtl/type_traits.hpp#L638) [(Examples)](../tests/tests_type_traits.cpp#L1398)
- `mtl::is_std_priority_queue` [(Documentation)](../mtl/type_traits.hpp#L658) [(Examples)](../tests/tests_type_traits.cpp#L1422)
- `mtl::is_std_container` [(Documentation)](../mtl/type_traits.hpp#L678) [(Examples)](../tests/tests_type_traits.cpp#L1447)
- `mtl::is_std_pair` [(Documentation)](../mtl/type_traits.hpp#L707) [(Examples)](../tests/tests_type_traits.cpp#L1476)
- `mtl::is_std_string` [(Documentation)](../mtl/type_traits.hpp#L730) [(Examples)](../tests/tests_type_traits.cpp#L1528)
- `mtl::is_c_string` [(Documentation)](../mtl/type_traits.hpp#L750) [(Examples)](../tests/tests_type_traits.cpp#L1612)
- `mtl::is_input_iterator` [(Documentation)](../mtl/type_traits.hpp#L769) [(Examples)](../tests/tests_type_traits.cpp#L1642)
- `mtl::is_output_iterator` [(Documentation)](../mtl/type_traits.hpp#L771) [(Examples)](../tests/tests_type_traits.cpp#L1642)
- `mtl::is_iterator` [(Documentation)](../mtl/type_traits.hpp#L773) [(Examples)](../tests/tests_type_traits.cpp#L1642)

---------------------------------------------------

## utility.hpp

- `MTL_ASSERT_MSG` [(Documentation)](../mtl/utility.hpp#L18) [(Examples)](../tests/tests_utility.cpp#L18)
- [**CLASS**] `mtl::no_copy` [(Documentation)](../mtl/utility.hpp#L38) [(Examples)](../tests/tests_utility.cpp#L73)
- [**CLASS**] `mtl::no_move` [(Documentation)](../mtl/utility.hpp#L55) [(Examples)](../tests/tests_utility.cpp#L97)

---------------------------------------------------

## xoroshiro128plus.hpp

- [**CLASS**] `mtl::xoroshiro128plus_engine` [(Documentation)](../mtl/xoroshiro128plus.hpp#L25) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L28)
  - `mtl::xoroshiro128plus_engine::xoroshiro128plus_engine` [(Documentation)](../mtl/xoroshiro128plus.hpp#L25) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L30)
  - `mtl::xoroshiro128plus_engine::operator=` [(Documentation)](../mtl/xoroshiro128plus.hpp#L183) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L32)
  - `mtl::xoroshiro128plus_engine::seed` [(Documentation)](../mtl/xoroshiro128plus.hpp#L217) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L34)
  - `mtl::xoroshiro128plus_engine::min` [(Documentation)](../mtl/xoroshiro128plus.hpp#L258) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L36)
  - `mtl::xoroshiro128plus_engine::max` [(Documentation)](../mtl/xoroshiro128plus.hpp#L267) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L38)
  - `mtl::xoroshiro128plus_engine::operator()` [(Documentation)](../mtl/xoroshiro128plus.hpp#L276) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L40)
  - `mtl::xoroshiro128plus_engine::generate` [(Documentation)](../mtl/xoroshiro128plus.hpp#L297) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L42)
  - `mtl::xoroshiro128plus_engine::discard` [(Documentation)](../mtl/xoroshiro128plus.hpp#L314) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L44)
  - `mtl::xoroshiro128plus_engine::operator<<` [(Documentation)](../mtl/xoroshiro128plus.hpp#L328) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L46)
  - `mtl::xoroshiro128plus_engine::operator>>` [(Documentation)](../mtl/xoroshiro128plus.hpp#L345) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L48)
  - `mtl::xoroshiro128plus_engine::operator==` [(Documentation)](../mtl/xoroshiro128plus.hpp#L364) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L50)
  - `mtl::xoroshiro128plus_engine::operator!=` [(Documentation)](../mtl/xoroshiro128plus.hpp#L377) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L52)
- [**CLASS**] `mtl::xoroshiro128plus` [(Documentation)](../mtl/xoroshiro128plus.hpp#L392) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L54)

---------------------------------------------------

## xorshift128plus.hpp

- [**CLASS**] `mtl::xorshift128plus_engine` [(Documentation)](../mtl/xorshift128plus.hpp#L25) [(Examples)](../tests/tests_xorshift128plus.cpp#L30)
  - `mtl::xorshift128plus_engine::xorshift128plus_engine` [(Documentation)](../mtl/xorshift128plus.hpp#L25) [(Examples)](../tests/tests_xorshift128plus.cpp#L32)
  - `mtl::xorshift128plus_engine::operator=` [(Documentation)](../mtl/xorshift128plus.hpp#L186) [(Examples)](../tests/tests_xorshift128plus.cpp#L34)
  - `mtl::xorshift128plus_engine::seed` [(Documentation)](../mtl/xorshift128plus.hpp#L220) [(Examples)](../tests/tests_xorshift128plus.cpp#L36)
  - `mtl::xorshift128plus_engine::min` [(Documentation)](../mtl/xorshift128plus.hpp#L261) [(Examples)](../tests/tests_xorshift128plus.cpp#L38)
  - `mtl::xorshift128plus_engine::max` [(Documentation)](../mtl/xorshift128plus.hpp#L270) [(Examples)](../tests/tests_xorshift128plus.cpp#L40)
  - `mtl::xorshift128plus_engine::operator()` [(Documentation)](../mtl/xorshift128plus.hpp#L279) [(Examples)](../tests/tests_xorshift128plus.cpp#L42)
  - `mtl::xorshift128plus_engine::generate` [(Documentation)](../mtl/xorshift128plus.hpp#L302) [(Examples)](../tests/tests_xorshift128plus.cpp#L44)
  - `mtl::xorshift128plus_engine::discard` [(Documentation)](../mtl/xorshift128plus.hpp#L319) [(Examples)](../tests/tests_xorshift128plus.cpp#L46)
  - `mtl::xorshift128plus_engine::operator<<` [(Documentation)](../mtl/xorshift128plus.hpp#L333) [(Examples)](../tests/tests_xorshift128plus.cpp#L48)
  - `mtl::xorshift128plus_engine::operator>>` [(Documentation)](../mtl/xorshift128plus.hpp#L350) [(Examples)](../tests/tests_xorshift128plus.cpp#L50)
  - `mtl::xorshift128plus_engine::operator==` [(Documentation)](../mtl/xorshift128plus.hpp#L369) [(Examples)](../tests/tests_xorshift128plus.cpp#L52)
  - `mtl::xorshift128plus_engine::operator!=` [(Documentation)](../mtl/xorshift128plus.hpp#L382) [(Examples)](../tests/tests_xorshift128plus.cpp#L54)
- [**CLASS**] `mtl::xorshift128plus` [(Documentation)](../mtl/xorshift128plus.hpp#L396) [(Examples)](../tests/tests_xorshift128plus.cpp#L56)

---------------------------------------------------

## xoshiro256plus.hpp

- [**CLASS**] `mtl::xoshiro256plus_engine` [(Documentation)](../mtl/xoshiro256plus.hpp#L25) [(Examples)](../tests/tests_xoshiro256plus.cpp#L30)
  - `mtl::xoshiro256plus_engine::xoshiro256plus_engine` [(Documentation)](../mtl/xoshiro256plus.hpp#L25) [(Examples)](../tests/tests_xoshiro256plus.cpp#L32)
  - `mtl::xoshiro256plus_engine::operator=` [(Documentation)](../mtl/xoshiro256plus.hpp#L222) [(Examples)](../tests/tests_xoshiro256plus.cpp#L34)
  - `mtl::xoshiro256plus_engine::seed` [(Documentation)](../mtl/xoshiro256plus.hpp#L256) [(Examples)](../tests/tests_xoshiro256plus.cpp#L36)
  - `mtl::xoshiro256plus_engine::min` [(Documentation)](../mtl/xoshiro256plus.hpp#L314) [(Examples)](../tests/tests_xoshiro256plus.cpp#L38)
  - `mtl::xoshiro256plus_engine::max` [(Documentation)](../mtl/xoshiro256plus.hpp#L323) [(Examples)](../tests/tests_xoshiro256plus.cpp#L40)
  - `mtl::xoshiro256plus_engine::operator()` [(Documentation)](../mtl/xoshiro256plus.hpp#L332) [(Examples)](../tests/tests_xoshiro256plus.cpp#L42)
  - `mtl::xoshiro256plus_engine::generate` [(Documentation)](../mtl/xoshiro256plus.hpp#L356) [(Examples)](../tests/tests_xoshiro256plus.cpp#L44)
  - `mtl::xoshiro256plus_engine::discard` [(Documentation)](../mtl/xoshiro256plus.hpp#L373) [(Examples)](../tests/tests_xoshiro256plus.cpp#L46)
  - `mtl::xoshiro256plus_engine::operator<<` [(Documentation)](../mtl/xoshiro256plus.hpp#L387) [(Examples)](../tests/tests_xoshiro256plus.cpp#L48)
  - `mtl::xoshiro256plus_engine::operator>>` [(Documentation)](../mtl/xoshiro256plus.hpp#L405) [(Examples)](../tests/tests_xoshiro256plus.cpp#L50)
  - `mtl::xoshiro256plus_engine::operator==` [(Documentation)](../mtl/xoshiro256plus.hpp#L426) [(Examples)](../tests/tests_xoshiro256plus.cpp#L52)
  - `mtl::xoshiro256plus_engine::operator!=` [(Documentation)](../mtl/xoshiro256plus.hpp#L439) [(Examples)](../tests/tests_xoshiro256plus.cpp#L54)
- [**CLASS**] `mtl::xoshiro256plus` [(Documentation)](../mtl/xoshiro256plus.hpp#L453) [(Examples)](../tests/tests_xoshiro256plus.cpp#L56)
