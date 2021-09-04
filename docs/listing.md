# List of classes and functions

 | [algorithm.hpp](#algorithmhpp) | [console.hpp](#consolehpp) | [container.hpp](#containerhpp) | [conversion.hpp](#conversionhpp) | [filesystem.hpp](#filesystemhpp) | [math.hpp](#mathhpp) | [numeric.hpp](#numerichpp) | [random.hpp](#randomhpp) | [safety.hpp](#safetyhpp) | [stopwatch.hpp](#stopwatchhpp) | [string.hpp](#stringhpp) | [type_traits.hpp](#type_traitshpp) | [utility.hpp](#utilityhpp) | [xoroshiro128plus.hpp](#xoroshiro128plushpp) | [xorshift128plus.hpp](#xorshift128plushpp) | [xoshiro256plus.hpp](#xoshiro256plushpp) |

## Statistics

There are 16 headers.

There are 10 classes.

There are 52 class member functions.

There are 151 non-member functions.

## algorithm.hpp

- `mtl::not_unique_inclusive` [(Documentation)](../mtl/algorithm.hpp#L38) [(Examples)](../tests/tests_algorithm.cpp#L40)
- `mtl::not_unique_exclusive` [(Documentation)](../mtl/algorithm.hpp#L40) [(Examples)](../tests/tests_algorithm.cpp#L330)
- `mtl::not_unique` [(Documentation)](../mtl/algorithm.hpp#L42) [(Examples)](../tests/tests_algorithm.cpp#L617)
- `mtl::keep_duplicates_inclusive` [(Documentation)](../mtl/algorithm.hpp#L479) [(Examples)](../tests/tests_algorithm.cpp#L899)
- `mtl::keep_duplicates_exclusive` [(Documentation)](../mtl/algorithm.hpp#L631) [(Examples)](../tests/tests_algorithm.cpp#L1081)
- `mtl::keep_duplicates` [(Documentation)](../mtl/algorithm.hpp#L761) [(Examples)](../tests/tests_algorithm.cpp#L1255)
- `mtl::keep_duplicates_inclusive_sorted` [(Documentation)](../mtl/algorithm.hpp#L477) [(Examples)](../tests/tests_algorithm.cpp#L1434)
- `mtl::keep_duplicates_exclusive_sorted` [(Documentation)](../mtl/algorithm.hpp#L629) [(Examples)](../tests/tests_algorithm.cpp#L1643)
- `mtl::keep_duplicates_sorted` [(Documentation)](../mtl/algorithm.hpp#L759) [(Examples)](../tests/tests_algorithm.cpp#L1847)
- `mtl::keep_duplicates_inclusive_preserve` [(Documentation)](../mtl/algorithm.hpp#L481) [(Examples)](../tests/tests_algorithm.cpp#L2058)
- `mtl::keep_duplicates_exclusive_preserve` [(Documentation)](../mtl/algorithm.hpp#L633) [(Examples)](../tests/tests_algorithm.cpp#L2241)
- `mtl::keep_duplicates_preserve` [(Documentation)](../mtl/algorithm.hpp#L762) [(Examples)](../tests/tests_algorithm.cpp#L2433)
- `mtl::rem_duplicates_sorted` [(Documentation)](../mtl/algorithm.hpp#L267) [(Examples)](../tests/tests_algorithm.cpp#L2616)
- `mtl::rem_duplicates` [(Documentation)](../mtl/algorithm.hpp#L268) [(Examples)](../tests/tests_algorithm.cpp#L2805)
- `mtl::rem_duplicates_preserve` [(Documentation)](../mtl/algorithm.hpp#L269) [(Examples)](../tests/tests_algorithm.cpp#L2959)
- `mtl::contains` [(Documentation)](../mtl/algorithm.hpp#L875) [(Examples)](../tests/tests_algorithm.cpp#L3122)
- `mtl::contains_all` [(Documentation)](../mtl/algorithm.hpp#L928) [(Examples)](../tests/tests_algorithm.cpp#L3270)
- `mtl::contains_all_sorted` [(Documentation)](../mtl/algorithm.hpp#L929) [(Examples)](../tests/tests_algorithm.cpp#L3431)
- `mtl::for_each` [(Documentation)](../mtl/algorithm.hpp#L1011) [(Examples)](../tests/tests_algorithm.cpp#L3592)
- `mtl::for_adj_pairs` [(Documentation)](../mtl/algorithm.hpp#L1156) [(Examples)](../tests/tests_algorithm.cpp#L4087)
- `mtl::for_all_pairs` [(Documentation)](../mtl/algorithm.hpp#L1185) [(Examples)](../tests/tests_algorithm.cpp#L4175)
- `mtl::fill_range` [(Documentation)](../mtl/algorithm.hpp#L1221) [(Examples)](../tests/tests_algorithm.cpp#L4267)
- `mtl::range` [(Documentation)](../mtl/algorithm.hpp#L1264) [(Examples)](../tests/tests_algorithm.cpp#L4389)

---------------------------------------------------

## console.hpp

- `mtl::console::print` [(Documentation)](../mtl/console.hpp#L168) [(Examples)](../tests/tests_console.cpp#L74)
- `mtl::console::println` [(Documentation)](../mtl/console.hpp#L208) [(Examples)](../tests/tests_console.cpp#L74)
- `mtl::console::print_all` [(Documentation)](../mtl/console.hpp#L290) [(Examples)](../tests/tests_console.cpp#L341)
- `mtl::console::print_color` [(Documentation)](../mtl/console.hpp#L552) [(Examples)](../tests/tests_console.cpp#L674)
- `mtl::console::println_color` [(Documentation)](../mtl/console.hpp#L553) [(Examples)](../tests/tests_console.cpp#L973)
- `mtl::console::overtype` [(Documentation)](../mtl/console.hpp#L1236) [(Examples)](../tests/tests_console.cpp#L1216)
- `mtl::console::clear` [(Documentation)](../mtl/console.hpp#L1302) [(Examples)](../tests/tests_console.cpp#L1607)

---------------------------------------------------

## container.hpp

- `mtl::reserve` [(Documentation)](../mtl/container.hpp#L24) [(Examples)](../tests/tests_container.cpp#L25)
- `mtl::push_back` [(Documentation)](../mtl/container.hpp#L49) [(Examples)](../tests/tests_container.cpp#L124)
- `mtl::emplace_back` [(Documentation)](../mtl/container.hpp#L73) [(Examples)](../tests/tests_container.cpp#L260)
- `mtl::slice` [(Documentation)](../mtl/container.hpp#L103) [(Examples)](../tests/tests_container.cpp#L399)
- `mtl::slice_n` [(Documentation)](../mtl/container.hpp#L104) [(Examples)](../tests/tests_container.cpp#L1279)

---------------------------------------------------

## conversion.hpp

- `mtl::to_num` [(Documentation)](../mtl/conversion.hpp#L29) [(Examples)](../tests/tests_conversion.cpp#L65)
- `mtl::to_num_noex` [(Documentation)](../mtl/conversion.hpp#L30) [(Examples)](../tests/tests_conversion.cpp#L615)
- `mtl::numeric_cast` [(Documentation)](../mtl/conversion.hpp#L794) [(Examples)](../tests/tests_conversion.cpp#L3684)
- `mtl::numeric_cast_noex` [(Documentation)](../mtl/conversion.hpp#L796) [(Examples)](../tests/tests_conversion.cpp#L4302)
- `mtl::rounding_cast` [(Documentation)](../mtl/conversion.hpp#L877) [(Examples)](../tests/tests_conversion.cpp#L6961)
- `mtl::rounding_cast_noex` [(Documentation)](../mtl/conversion.hpp#L878) [(Examples)](../tests/tests_conversion.cpp#L7054)

---------------------------------------------------

## filesystem.hpp

- `mtl::filesystem::read_file` [(Documentation)](../mtl/filesystem.hpp#L38) [(Examples)](../tests/tests_filesystem.cpp#L129)
- `mtl::filesystem::read_all_lines` [(Documentation)](../mtl/filesystem.hpp#L114) [(Examples)](../tests/tests_filesystem.cpp#L379)
- `mtl::filesystem::write_file` [(Documentation)](../mtl/filesystem.hpp#L247) [(Examples)](../tests/tests_filesystem.cpp#L99)
- `mtl::filesystem::write_all_lines` [(Documentation)](../mtl/filesystem.hpp#L286) [(Examples)](../tests/tests_filesystem.cpp#L913)

---------------------------------------------------

## math.hpp

- `mtl::approx_equal_abs` [(Documentation)](../mtl/math.hpp#L25) [(Examples)](../tests/tests_math.cpp#L25)
- `mtl::approx_equal_rel` [(Documentation)](../mtl/math.hpp#L26) [(Examples)](../tests/tests_math.cpp#L98)
- `mtl::approx_equal_comb` [(Documentation)](../mtl/math.hpp#L27) [(Examples)](../tests/tests_math.cpp#L170)
- `mtl::percent_whole` [(Documentation)](../mtl/math.hpp#L95) [(Examples)](../tests/tests_math.cpp#L281)
- `mtl::percent_portion` [(Documentation)](../mtl/math.hpp#L96) [(Examples)](../tests/tests_math.cpp#L597)
- `mtl::percent` [(Documentation)](../mtl/math.hpp#L97) [(Examples)](../tests/tests_math.cpp#L791)

---------------------------------------------------

## numeric.hpp

- `mtl::iota` [(Documentation)](../mtl/numeric.hpp#L30) [(Examples)](../tests/tests_numeric.cpp#L23)
- `mtl::frequency` [(Documentation)](../mtl/numeric.hpp#L57) [(Examples)](../tests/tests_numeric.cpp#L533)
- `mtl::mean` [(Documentation)](../mtl/numeric.hpp#L132) [(Examples)](../tests/tests_numeric.cpp#L754)
- `mtl::median` [(Documentation)](../mtl/numeric.hpp#L162) [(Examples)](../tests/tests_numeric.cpp#L1103)

---------------------------------------------------

## random.hpp

- [**CLASS**] `mtl::rng` [(Documentation)](../mtl/random.hpp#L30) [(Examples)](../tests/tests_random.cpp#L26)
  - `mtl::rng::rng` [(Documentation)](../mtl/random.hpp#L30) [(Examples)](../tests/tests_random.cpp#L28)
  - `mtl::rng::set_min_max` [(Documentation)](../mtl/random.hpp#L113) [(Examples)](../tests/tests_random.cpp#L30)
  - `mtl::rng::min` [(Documentation)](../mtl/random.hpp#L128) [(Examples)](../tests/tests_random.cpp#L32)
  - `mtl::rng::max` [(Documentation)](../mtl/random.hpp#L137) [(Examples)](../tests/tests_random.cpp#L34)
  - `mtl::rng::next` [(Documentation)](../mtl/random.hpp#L146) [(Examples)](../tests/tests_random.cpp#L36)
  - `mtl::rng::seed` [(Documentation)](../mtl/random.hpp#L155) [(Examples)](../tests/tests_random.cpp#L38)
  - `mtl::rng::seed_random` [(Documentation)](../mtl/random.hpp#L188) [(Examples)](../tests/tests_random.cpp#L40)
- `mtl::random_choice` [(Documentation)](../mtl/random.hpp#L200) [(Examples)](../tests/tests_random.cpp#L645)
- `mtl::shuffle` [(Documentation)](../mtl/random.hpp#L253) [(Examples)](../tests/tests_random.cpp#L1116)

---------------------------------------------------

## safety.hpp

- `mtl::safe_copy` [(Documentation)](../mtl/safety.hpp#L28) [(Examples)](../tests/tests_safety.cpp#L29)
- `mtl::safe_copy_n` [(Documentation)](../mtl/safety.hpp#L29) [(Examples)](../tests/tests_safety.cpp#L694)

---------------------------------------------------

## stopwatch.hpp

- [**CLASS**] `mtl::chrono::stopwatch` [(Documentation)](../mtl/stopwatch.hpp#L28) [(Examples)](../tests/tests_stopwatch.cpp#L25)
  - `mtl::chrono::stopwatch::start` [(Documentation)](../mtl/stopwatch.hpp#L41) [(Examples)](../tests/tests_stopwatch.cpp#L27)
  - `mtl::chrono::stopwatch::stop` [(Documentation)](../mtl/stopwatch.hpp#L51) [(Examples)](../tests/tests_stopwatch.cpp#L29)
  - `mtl::chrono::stopwatch::reset` [(Documentation)](../mtl/stopwatch.hpp#L61) [(Examples)](../tests/tests_stopwatch.cpp#L31)
  - `mtl::chrono::stopwatch::restart` [(Documentation)](../mtl/stopwatch.hpp#L72) [(Examples)](../tests/tests_stopwatch.cpp#L33)
  - `mtl::chrono::stopwatch::elapsed_minutes` [(Documentation)](../mtl/stopwatch.hpp#L83) [(Examples)](../tests/tests_stopwatch.cpp#L35)
  - `mtl::chrono::stopwatch::elapsed_seconds` [(Documentation)](../mtl/stopwatch.hpp#L99) [(Examples)](../tests/tests_stopwatch.cpp#L37)
  - `mtl::chrono::stopwatch::elapsed_milli` [(Documentation)](../mtl/stopwatch.hpp#L112) [(Examples)](../tests/tests_stopwatch.cpp#L39)
  - `mtl::chrono::stopwatch::elapsed_micro` [(Documentation)](../mtl/stopwatch.hpp#L125) [(Examples)](../tests/tests_stopwatch.cpp#L41)
  - `mtl::chrono::stopwatch::elapsed_nano` [(Documentation)](../mtl/stopwatch.hpp#L138) [(Examples)](../tests/tests_stopwatch.cpp#L43)

---------------------------------------------------

## string.hpp

- `mtl::string::is_upper` [(Documentation)](../mtl/string.hpp#L41) [(Examples)](../tests/tests_string.cpp#L84)
- `mtl::string::is_lower` [(Documentation)](../mtl/string.hpp#L43) [(Examples)](../tests/tests_string.cpp#L227)
- `mtl::string::to_upper` [(Documentation)](../mtl/string.hpp#L110) [(Examples)](../tests/tests_string.cpp#L370)
- `mtl::string::to_lower` [(Documentation)](../mtl/string.hpp#L112) [(Examples)](../tests/tests_string.cpp#L417)
- `mtl::string::is_ascii` [(Documentation)](../mtl/string.hpp#L167) [(Examples)](../tests/tests_string.cpp#L462)
- `mtl::string::is_alphabetic` [(Documentation)](../mtl/string.hpp#L206) [(Examples)](../tests/tests_string.cpp#L589)
- `mtl::string::is_numeric` [(Documentation)](../mtl/string.hpp#L208) [(Examples)](../tests/tests_string.cpp#L743)
- `mtl::string::is_alphanum` [(Documentation)](../mtl/string.hpp#L209) [(Examples)](../tests/tests_string.cpp#L897)
- `mtl::string::contains` [(Documentation)](../mtl/string.hpp#L307) [(Examples)](../tests/tests_string.cpp#L1049)
- `mtl::string::strip_front` [(Documentation)](../mtl/string.hpp#L432) [(Examples)](../tests/tests_string.cpp#L1351)
- `mtl::string::strip_back` [(Documentation)](../mtl/string.hpp#L433) [(Examples)](../tests/tests_string.cpp#L1351)
- `mtl::string::strip` [(Documentation)](../mtl/string.hpp#L434) [(Examples)](../tests/tests_string.cpp#L1351)
- `mtl::string::pad_front` [(Documentation)](../mtl/string.hpp#L503) [(Examples)](../tests/tests_string.cpp#L1585)
- `mtl::string::pad_back` [(Documentation)](../mtl/string.hpp#L506) [(Examples)](../tests/tests_string.cpp#L1585)
- `mtl::string::pad` [(Documentation)](../mtl/string.hpp#L509) [(Examples)](../tests/tests_string.cpp#L1585)
- `mtl::string::to_string` [(Documentation)](../mtl/string.hpp#L672) [(Examples)](../tests/tests_string.cpp#L1803)
- `mtl::string::join_all` [(Documentation)](../mtl/string.hpp#L793) [(Examples)](../tests/tests_string.cpp#L1904)
- `mtl::string::join` [(Documentation)](../mtl/string.hpp#L969) [(Examples)](../tests/tests_string.cpp#L2127)
- `mtl::string::split` [(Documentation)](../mtl/string.hpp#L1110) [(Examples)](../tests/tests_string.cpp#L2220)
- `mtl::string::replace` [(Documentation)](../mtl/string.hpp#L1248) [(Examples)](../tests/tests_string.cpp#L3328)
- `mtl::string::replace_all` [(Documentation)](../mtl/string.hpp#L1560) [(Examples)](../tests/tests_string.cpp#L3986)

---------------------------------------------------

## type_traits.hpp

- `mtl::are_same` [(Documentation)](../mtl/type_traits.hpp#L40) [(Examples)](../tests/tests_type_traits.cpp#L48)
- `mtl::are_same_v` [(Documentation)](../mtl/type_traits.hpp#L41) [(Examples)](../tests/tests_type_traits.cpp#L79)
- `mtl::has_reserve` [(Documentation)](../mtl/type_traits.hpp#L67) [(Examples)](../tests/tests_type_traits.cpp#L112)
- `mtl::has_reserve_v` [(Documentation)](../mtl/type_traits.hpp#L68) [(Examples)](../tests/tests_type_traits.cpp#L136)
- `mtl::has_push_back` [(Documentation)](../mtl/type_traits.hpp#L92) [(Examples)](../tests/tests_type_traits.cpp#L160)
- `mtl::has_push_back_v` [(Documentation)](../mtl/type_traits.hpp#L93) [(Examples)](../tests/tests_type_traits.cpp#L181)
- `mtl::has_emplace_back` [(Documentation)](../mtl/type_traits.hpp#L115) [(Examples)](../tests/tests_type_traits.cpp#L203)
- `mtl::has_emplace_back_v` [(Documentation)](../mtl/type_traits.hpp#L116) [(Examples)](../tests/tests_type_traits.cpp#L224)
- `mtl::has_size` [(Documentation)](../mtl/type_traits.hpp#L170) [(Examples)](../tests/tests_type_traits.cpp#L249)
- `mtl::has_size_v` [(Documentation)](../mtl/type_traits.hpp#L171) [(Examples)](../tests/tests_type_traits.cpp#L271)
- `mtl::has_find` [(Documentation)](../mtl/type_traits.hpp#L193) [(Examples)](../tests/tests_type_traits.cpp#L294)
- `mtl::has_find_v` [(Documentation)](../mtl/type_traits.hpp#L194) [(Examples)](../tests/tests_type_traits.cpp#L322)
- `mtl::is_sint` [(Documentation)](../mtl/type_traits.hpp#L268) [(Examples)](../tests/tests_type_traits.cpp#L352)
- `mtl::is_sint_v` [(Documentation)](../mtl/type_traits.hpp#L269) [(Examples)](../tests/tests_type_traits.cpp#L380)
- `mtl::is_uint` [(Documentation)](../mtl/type_traits.hpp#L272) [(Examples)](../tests/tests_type_traits.cpp#L505)
- `mtl::is_uint_v` [(Documentation)](../mtl/type_traits.hpp#L273) [(Examples)](../tests/tests_type_traits.cpp#L533)
- `mtl::is_int` [(Documentation)](../mtl/type_traits.hpp#L276) [(Examples)](../tests/tests_type_traits.cpp#L658)
- `mtl::is_int_v` [(Documentation)](../mtl/type_traits.hpp#L277) [(Examples)](../tests/tests_type_traits.cpp#L685)
- `mtl::is_float` [(Documentation)](../mtl/type_traits.hpp#L280) [(Examples)](../tests/tests_type_traits.cpp#L809)
- `mtl::is_float_v` [(Documentation)](../mtl/type_traits.hpp#L281) [(Examples)](../tests/tests_type_traits.cpp#L823)
- `mtl::is_number` [(Documentation)](../mtl/type_traits.hpp#L284) [(Examples)](../tests/tests_type_traits.cpp#L878)
- `mtl::is_number_v` [(Documentation)](../mtl/type_traits.hpp#L285) [(Examples)](../tests/tests_type_traits.cpp#L907)
- `mtl::is_char` [(Documentation)](../mtl/type_traits.hpp#L288) [(Examples)](../tests/tests_type_traits.cpp#L1044)
- `mtl::is_char_v` [(Documentation)](../mtl/type_traits.hpp#L289) [(Examples)](../tests/tests_type_traits.cpp#L1058)
- `mtl::is_std_array` [(Documentation)](../mtl/type_traits.hpp#L385) [(Examples)](../tests/tests_type_traits.cpp#L1118)
- `mtl::is_std_array_v` [(Documentation)](../mtl/type_traits.hpp#L386) [(Examples)](../tests/tests_type_traits.cpp#L1131)
- `mtl::is_std_vector` [(Documentation)](../mtl/type_traits.hpp#L406) [(Examples)](../tests/tests_type_traits.cpp#L1145)
- `mtl::is_std_vector_v` [(Documentation)](../mtl/type_traits.hpp#L407) [(Examples)](../tests/tests_type_traits.cpp#L1158)
- `mtl::is_std_deque` [(Documentation)](../mtl/type_traits.hpp#L427) [(Examples)](../tests/tests_type_traits.cpp#L1172)
- `mtl::is_std_deque_v` [(Documentation)](../mtl/type_traits.hpp#L428) [(Examples)](../tests/tests_type_traits.cpp#L1185)
- `mtl::is_std_forward_list` [(Documentation)](../mtl/type_traits.hpp#L448) [(Examples)](../tests/tests_type_traits.cpp#L1199)
- `mtl::is_std_forward_list_v` [(Documentation)](../mtl/type_traits.hpp#L449) [(Examples)](../tests/tests_type_traits.cpp#L1213)
- `mtl::is_std_list` [(Documentation)](../mtl/type_traits.hpp#L469) [(Examples)](../tests/tests_type_traits.cpp#L1228)
- `mtl::is_std_list_v` [(Documentation)](../mtl/type_traits.hpp#L470) [(Examples)](../tests/tests_type_traits.cpp#L1241)
- `mtl::is_std_set` [(Documentation)](../mtl/type_traits.hpp#L490) [(Examples)](../tests/tests_type_traits.cpp#L1255)
- `mtl::is_std_set_v` [(Documentation)](../mtl/type_traits.hpp#L491) [(Examples)](../tests/tests_type_traits.cpp#L1269)
- `mtl::is_std_multiset` [(Documentation)](../mtl/type_traits.hpp#L511) [(Examples)](../tests/tests_type_traits.cpp#L1284)
- `mtl::is_std_multiset_v` [(Documentation)](../mtl/type_traits.hpp#L512) [(Examples)](../tests/tests_type_traits.cpp#L1298)
- `mtl::is_std_map` [(Documentation)](../mtl/type_traits.hpp#L532) [(Examples)](../tests/tests_type_traits.cpp#L1314)
- `mtl::is_std_map_v` [(Documentation)](../mtl/type_traits.hpp#L533) [(Examples)](../tests/tests_type_traits.cpp#L1328)
- `mtl::is_std_multimap` [(Documentation)](../mtl/type_traits.hpp#L553) [(Examples)](../tests/tests_type_traits.cpp#L1343)
- `mtl::is_std_multimap_v` [(Documentation)](../mtl/type_traits.hpp#L554) [(Examples)](../tests/tests_type_traits.cpp#L1357)
- `mtl::is_std_unordered_set` [(Documentation)](../mtl/type_traits.hpp#L574) [(Examples)](../tests/tests_type_traits.cpp#L1372)
- `mtl::is_std_unordered_set_v` [(Documentation)](../mtl/type_traits.hpp#L575) [(Examples)](../tests/tests_type_traits.cpp#L1386)
- `mtl::is_std_unordered_map` [(Documentation)](../mtl/type_traits.hpp#L595) [(Examples)](../tests/tests_type_traits.cpp#L1430)
- `mtl::is_std_unordered_map_v` [(Documentation)](../mtl/type_traits.hpp#L596) [(Examples)](../tests/tests_type_traits.cpp#L1444)
- `mtl::is_std_unordered_multiset` [(Documentation)](../mtl/type_traits.hpp#L616) [(Examples)](../tests/tests_type_traits.cpp#L1401)
- `mtl::is_std_unordered_multiset_v` [(Documentation)](../mtl/type_traits.hpp#L617) [(Examples)](../tests/tests_type_traits.cpp#L1415)
- `mtl::is_std_unordered_multimap` [(Documentation)](../mtl/type_traits.hpp#L637) [(Examples)](../tests/tests_type_traits.cpp#L1459)
- `mtl::is_std_unordered_multimap_v` [(Documentation)](../mtl/type_traits.hpp#L638) [(Examples)](../tests/tests_type_traits.cpp#L1473)
- `mtl::is_std_stack` [(Documentation)](../mtl/type_traits.hpp#L658) [(Examples)](../tests/tests_type_traits.cpp#L1488)
- `mtl::is_std_stack_v` [(Documentation)](../mtl/type_traits.hpp#L659) [(Examples)](../tests/tests_type_traits.cpp#L1502)
- `mtl::is_std_queue` [(Documentation)](../mtl/type_traits.hpp#L679) [(Examples)](../tests/tests_type_traits.cpp#L1517)
- `mtl::is_std_queue_v` [(Documentation)](../mtl/type_traits.hpp#L680) [(Examples)](../tests/tests_type_traits.cpp#L1531)
- `mtl::is_std_priority_queue` [(Documentation)](../mtl/type_traits.hpp#L700) [(Examples)](../tests/tests_type_traits.cpp#L1546)
- `mtl::is_std_priority_queue_v` [(Documentation)](../mtl/type_traits.hpp#L701) [(Examples)](../tests/tests_type_traits.cpp#L1560)
- `mtl::is_std_container` [(Documentation)](../mtl/type_traits.hpp#L721) [(Examples)](../tests/tests_type_traits.cpp#L1575)
- `mtl::is_std_container_v` [(Documentation)](../mtl/type_traits.hpp#L722) [(Examples)](../tests/tests_type_traits.cpp#L1589)
- `mtl::is_std_pair` [(Documentation)](../mtl/type_traits.hpp#L751) [(Examples)](../tests/tests_type_traits.cpp#L1608)
- `mtl::is_std_pair_v` [(Documentation)](../mtl/type_traits.hpp#L752) [(Examples)](../tests/tests_type_traits.cpp#L1635)
- `mtl::is_std_string` [(Documentation)](../mtl/type_traits.hpp#L775) [(Examples)](../tests/tests_type_traits.cpp#L1664)
- `mtl::is_std_string_v` [(Documentation)](../mtl/type_traits.hpp#L776) [(Examples)](../tests/tests_type_traits.cpp#L1681)
- `mtl::is_c_string` [(Documentation)](../mtl/type_traits.hpp#L796) [(Examples)](../tests/tests_type_traits.cpp#L1752)
- `mtl::is_c_string_v` [(Documentation)](../mtl/type_traits.hpp#L797) [(Examples)](../tests/tests_type_traits.cpp#L1769)
- `mtl::is_input_iterator` [(Documentation)](../mtl/type_traits.hpp#L816) [(Examples)](../tests/tests_type_traits.cpp#L1838)
- `mtl::is_input_iterator_v` [(Documentation)](../mtl/type_traits.hpp#L817) [(Examples)](../tests/tests_type_traits.cpp#L1864)
- `mtl::is_output_iterator` [(Documentation)](../mtl/type_traits.hpp#L820) [(Examples)](../tests/tests_type_traits.cpp#L1892)
- `mtl::is_output_iterator_v` [(Documentation)](../mtl/type_traits.hpp#L821) [(Examples)](../tests/tests_type_traits.cpp#L1918)
- `mtl::is_iterator` [(Documentation)](../mtl/type_traits.hpp#L824) [(Examples)](../tests/tests_type_traits.cpp#L1946)
- `mtl::is_iterator_v` [(Documentation)](../mtl/type_traits.hpp#L825) [(Examples)](../tests/tests_type_traits.cpp#L1972)

---------------------------------------------------

## utility.hpp

- `MTL_ASSERT_MSG` [(Documentation)](../mtl/utility.hpp#L23) [(Examples)](../tests/tests_utility.cpp#L19)
- [**CLASS**] `mtl::no_copy` [(Documentation)](../mtl/utility.hpp#L36) [(Examples)](../tests/tests_utility.cpp#L74)
- [**CLASS**] `mtl::no_move` [(Documentation)](../mtl/utility.hpp#L53) [(Examples)](../tests/tests_utility.cpp#L98)

---------------------------------------------------

## xoroshiro128plus.hpp

- [**CLASS**] `mtl::xoroshiro128plus_engine` [(Documentation)](../mtl/xoroshiro128plus.hpp#L30) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L29)
  - `mtl::xoroshiro128plus_engine::xoroshiro128plus_engine` [(Documentation)](../mtl/xoroshiro128plus.hpp#L30) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L31)
  - `mtl::xoroshiro128plus_engine::operator=` [(Documentation)](../mtl/xoroshiro128plus.hpp#L188) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L33)
  - `mtl::xoroshiro128plus_engine::seed` [(Documentation)](../mtl/xoroshiro128plus.hpp#L232) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L35)
  - `mtl::xoroshiro128plus_engine::min` [(Documentation)](../mtl/xoroshiro128plus.hpp#L273) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L37)
  - `mtl::xoroshiro128plus_engine::max` [(Documentation)](../mtl/xoroshiro128plus.hpp#L282) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L39)
  - `mtl::xoroshiro128plus_engine::operator()` [(Documentation)](../mtl/xoroshiro128plus.hpp#L291) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L41)
  - `mtl::xoroshiro128plus_engine::generate` [(Documentation)](../mtl/xoroshiro128plus.hpp#L309) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L43)
  - `mtl::xoroshiro128plus_engine::discard` [(Documentation)](../mtl/xoroshiro128plus.hpp#L326) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L45)
  - `mtl::xoroshiro128plus_engine::operator<<` [(Documentation)](../mtl/xoroshiro128plus.hpp#L340) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L47)
  - `mtl::xoroshiro128plus_engine::operator>>` [(Documentation)](../mtl/xoroshiro128plus.hpp#L357) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L49)
  - `mtl::xoroshiro128plus_engine::operator==` [(Documentation)](../mtl/xoroshiro128plus.hpp#L376) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L51)
  - `mtl::xoroshiro128plus_engine::operator!=` [(Documentation)](../mtl/xoroshiro128plus.hpp#L389) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L53)
- [**CLASS**] `mtl::xoroshiro128plus` [(Documentation)](../mtl/xoroshiro128plus.hpp#L404) [(Examples)](../tests/tests_xoroshiro128plus.cpp#L55)

---------------------------------------------------

## xorshift128plus.hpp

- [**CLASS**] `mtl::xorshift128plus_engine` [(Documentation)](../mtl/xorshift128plus.hpp#L30) [(Examples)](../tests/tests_xorshift128plus.cpp#L31)
  - `mtl::xorshift128plus_engine::xorshift128plus_engine` [(Documentation)](../mtl/xorshift128plus.hpp#L30) [(Examples)](../tests/tests_xorshift128plus.cpp#L33)
  - `mtl::xorshift128plus_engine::operator=` [(Documentation)](../mtl/xorshift128plus.hpp#L191) [(Examples)](../tests/tests_xorshift128plus.cpp#L35)
  - `mtl::xorshift128plus_engine::seed` [(Documentation)](../mtl/xorshift128plus.hpp#L235) [(Examples)](../tests/tests_xorshift128plus.cpp#L37)
  - `mtl::xorshift128plus_engine::min` [(Documentation)](../mtl/xorshift128plus.hpp#L276) [(Examples)](../tests/tests_xorshift128plus.cpp#L39)
  - `mtl::xorshift128plus_engine::max` [(Documentation)](../mtl/xorshift128plus.hpp#L285) [(Examples)](../tests/tests_xorshift128plus.cpp#L41)
  - `mtl::xorshift128plus_engine::operator()` [(Documentation)](../mtl/xorshift128plus.hpp#L294) [(Examples)](../tests/tests_xorshift128plus.cpp#L43)
  - `mtl::xorshift128plus_engine::generate` [(Documentation)](../mtl/xorshift128plus.hpp#L314) [(Examples)](../tests/tests_xorshift128plus.cpp#L45)
  - `mtl::xorshift128plus_engine::discard` [(Documentation)](../mtl/xorshift128plus.hpp#L331) [(Examples)](../tests/tests_xorshift128plus.cpp#L47)
  - `mtl::xorshift128plus_engine::operator<<` [(Documentation)](../mtl/xorshift128plus.hpp#L345) [(Examples)](../tests/tests_xorshift128plus.cpp#L49)
  - `mtl::xorshift128plus_engine::operator>>` [(Documentation)](../mtl/xorshift128plus.hpp#L362) [(Examples)](../tests/tests_xorshift128plus.cpp#L51)
  - `mtl::xorshift128plus_engine::operator==` [(Documentation)](../mtl/xorshift128plus.hpp#L381) [(Examples)](../tests/tests_xorshift128plus.cpp#L53)
  - `mtl::xorshift128plus_engine::operator!=` [(Documentation)](../mtl/xorshift128plus.hpp#L394) [(Examples)](../tests/tests_xorshift128plus.cpp#L55)
- [**CLASS**] `mtl::xorshift128plus` [(Documentation)](../mtl/xorshift128plus.hpp#L408) [(Examples)](../tests/tests_xorshift128plus.cpp#L57)

---------------------------------------------------

## xoshiro256plus.hpp

- [**CLASS**] `mtl::xoshiro256plus_engine` [(Documentation)](../mtl/xoshiro256plus.hpp#L30) [(Examples)](../tests/tests_xoshiro256plus.cpp#L31)
  - `mtl::xoshiro256plus_engine::xoshiro256plus_engine` [(Documentation)](../mtl/xoshiro256plus.hpp#L30) [(Examples)](../tests/tests_xoshiro256plus.cpp#L33)
  - `mtl::xoshiro256plus_engine::operator=` [(Documentation)](../mtl/xoshiro256plus.hpp#L227) [(Examples)](../tests/tests_xoshiro256plus.cpp#L35)
  - `mtl::xoshiro256plus_engine::seed` [(Documentation)](../mtl/xoshiro256plus.hpp#L271) [(Examples)](../tests/tests_xoshiro256plus.cpp#L37)
  - `mtl::xoshiro256plus_engine::min` [(Documentation)](../mtl/xoshiro256plus.hpp#L329) [(Examples)](../tests/tests_xoshiro256plus.cpp#L39)
  - `mtl::xoshiro256plus_engine::max` [(Documentation)](../mtl/xoshiro256plus.hpp#L338) [(Examples)](../tests/tests_xoshiro256plus.cpp#L41)
  - `mtl::xoshiro256plus_engine::operator()` [(Documentation)](../mtl/xoshiro256plus.hpp#L347) [(Examples)](../tests/tests_xoshiro256plus.cpp#L43)
  - `mtl::xoshiro256plus_engine::generate` [(Documentation)](../mtl/xoshiro256plus.hpp#L368) [(Examples)](../tests/tests_xoshiro256plus.cpp#L45)
  - `mtl::xoshiro256plus_engine::discard` [(Documentation)](../mtl/xoshiro256plus.hpp#L385) [(Examples)](../tests/tests_xoshiro256plus.cpp#L47)
  - `mtl::xoshiro256plus_engine::operator<<` [(Documentation)](../mtl/xoshiro256plus.hpp#L399) [(Examples)](../tests/tests_xoshiro256plus.cpp#L49)
  - `mtl::xoshiro256plus_engine::operator>>` [(Documentation)](../mtl/xoshiro256plus.hpp#L417) [(Examples)](../tests/tests_xoshiro256plus.cpp#L51)
  - `mtl::xoshiro256plus_engine::operator==` [(Documentation)](../mtl/xoshiro256plus.hpp#L438) [(Examples)](../tests/tests_xoshiro256plus.cpp#L53)
  - `mtl::xoshiro256plus_engine::operator!=` [(Documentation)](../mtl/xoshiro256plus.hpp#L451) [(Examples)](../tests/tests_xoshiro256plus.cpp#L55)
- [**CLASS**] `mtl::xoshiro256plus` [(Documentation)](../mtl/xoshiro256plus.hpp#L465) [(Examples)](../tests/tests_xoshiro256plus.cpp#L57)
