# CMake script by Michael Trikergiotis
# 07/09/2020

# Copyright (c) Michael Trikergiotis. All Rights Reserved.
# Licensed under the MIT license. See LICENSE in the project root for license information.
# See ThirdPartyNotices.txt in the project root for third party licenses information.




# CMake 3.8 is the minimum requirement because that is when CMAKE_CXX_STANDARD and 
# CMAKE_CXX_STANDARD_REQUIRED was introduced
cmake_minimum_required(VERSION 3.8)

# set the name of the project
project(mtl)

# print CMake version and CMake generator
message("-- CMake version is ${CMAKE_VERSION}")
message("-- CMake generator is ${CMAKE_GENERATOR}")


# if the C++ standard version isn't defined, set it to C++ 17, if it is defined use that version
if(NOT DEFINED CMAKE_CXX_STANDARD)
    # set standard version to C++ 17
    set(CMAKE_CXX_STANDARD 17)
endif()

# require the C++ standard version to be provided
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# print the current C++ standard version used
message("-- C++ standard version is C++ ${CMAKE_CXX_STANDARD}")

# if the C++ standard version is not set to C++ 17 or later, print a message and invoke a
# fatal error
if(NOT (${CMAKE_CXX_STANDARD} GREATER_EQUAL 17))
    message(FATAL_ERROR "The mtl requires the C++ standard version to be C++ 17 or later.")
endif()



# if we are on Windows use flags appropriate for MSVC, clang-cl, clang or gcc
if(WIN32)
    
    # check if the compiler is Microsoft Visual C++
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        
        message("-- Compiler used is MSVC")

        # because CMake adds the flag /W3 and we want the flag /W4 instead
        # we have to replace it in the C++ flags variable using REGEX REPLACE
        string(REGEX REPLACE "/W3" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

        # for CMake versions above 3.15 for some configurations CMake may not add the /W3 flag
        # for us to replace so we have to add it to be sure
        if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.15.0")
            add_compile_options(/W4) 
        endif()

        # the /EHsc flag turns on standard C++ stack unwinding and C++ exception handling
        # the /WX flag turns warnings to errors
        # the analyze flag turns on MSVC static analyzer
        add_compile_options(/EHsc /WX /analyze)

    # check if the compiler is clang
    elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
        
        # variable to keep track if clang is enabled
        set(ENABLE_GNU_LIKE_CLANG OFF)

        # since CMake 3.15 we can correctly detect and work with both clang++ and clang-cl using 
        # CMAKE_CXX_COMPILER_FRONTEND_VARIANT for more info check
        # https://gitlab.kitware.com/cmake/cmake/-/issues/19724
        if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.15.0")
            if(${CMAKE_CXX_COMPILER_FRONTEND_VARIANT} STREQUAL "GNU")
                message("-- Detected clang++")
                set(ENABLE_GNU_LIKE_CLANG ON)
            endif()
        endif()
       
        # enable gnu like flags for clang++ on Windows
        if(ENABLE_GNU_LIKE_CLANG)
            message("-- Compiler used is clang++")
            
            # enable a lot of warnings and turn them to errors for clang
            add_compile_options(-Werror -Wall -Wextra)
        # enable cl like flags for clang-cl on Windows
        else()
            
            message("-- Compiler used is clang-cl")

            # because CMake adds the flag /W3 and we want the flag /W4 instead
            # we have to replace it in the C++ flags variable using REGEX REPLACE
            string(REGEX REPLACE "/W3" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

            # for CMake versions above 3.15 for some configurations CMake may not add the /W3
            # flag for us to replace so we have to add it to be sure
            if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.15.0")
                add_compile_options(/W4)
            endif()

            # the /EHsc flag turns on standard C++ stack unwinding and C++ exception handling
            # the /WX flag turns warnings to errors
            add_compile_options(/EHsc /WX)
        endif()
    # check if the compiler is g++
    elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
        message("-- Compiler used is g++")
        # enable a lot of warnings and turn them to errors for gcc
        add_compile_options(-Werror -Wall -Wextra)
    endif()

    # when building with MSBuild
    if("${CMAKE_GENERATOR}" MATCHES "^Visual Studio")
        message("-- Building with MSBuild")
        # set tests as the default project for the Visual Studio solution
        set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT tests) 
        # put the automatically generated projects to their own folder to keep things clean
        set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    endif()

# if the we are not in Windows then we must be in Linux or Unix so we use gcc and clang flags
else()

    # this option will enable clang-tidy
    option(ENABLE_CLANG_TIDY "Enable clang-tidy." OFF)
    if(ENABLE_CLANG_TIDY)
        # check if clang-tidy exists
        find_program(CLANG_TIDY_COMMAND NAMES clang-tidy)
        # if we couldn't find clang-tidy print an warning message and continue
        if(NOT CLANG_TIDY_COMMAND)
            message(WARNING "-- Could not find clang-tidy")
            set(CMAKE_CXX_CLANG_TIDY "" CACHE STRING "" FORCE)
        # if we found clang-tidy pass the correct flags and print a message that clang-tidy is enabled
        else()
            set(CLANG_TIDY_CHECKS "boost*,bugprone*,cert*,clang-analyzer*,concurrency*,cppcoreguidelines*,hicpp*,misc*,modernize*,performance*,portability*,readability-implicit-bool-conversion,-cert-dcl03-c,-cert-dcl16-c,-cert-err58-cpp,-cppcoreguidelines-avoid-m*,-cppcoreguidelines-m*,-cppcoreguidelines-pro-b*,-cppcoreguidelines-pro-type-r*,-hicpp-e*,-hicpp-n*,-hicpp-s*,-hicpp-uppercase-literal-suffix,-hicpp-use-auto,-hicpp-use-equals-delete,-misc-d*,-misc-non-p*,-misc-static-assert,-modernize-l*,-modernize-use-auto,-modernize-use-equals-delete,-modernize-use-trailing-return-type")
            set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND};-checks=${CLANG_TIDY_CHECKS};-warnings-as-errors=${CLANG_TIDY_CHECKS};-header-filter=.hpp;-quiet")
            message("-- Enabled clang-tidy")
        endif()
    endif()


    if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
        message("-- Compiler used is clang++")
    elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
        message("-- Compiler used is g++")
    endif()

    # if we are using clang then we may want to use libc++
    if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
        
        # this option will enable libc++
        option(ENABLE_LIBCXX "Enable libc++." OFF)

        #if ENABLE_LIBCXX option is turned on add the all flags needed to use libc++
        if(ENABLE_LIBCXX)
            message("-- Standard library used libc++")
            # we have to add the libc++ flag to the list of compiler flags
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
            # we have to also add the libc++ flags to the list of linker flags
            set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
        endif()
    endif()

    # enable a lot of warnings and turn them to errors for gcc and clang
    add_compile_options(-Werror -Wall -Wextra)
endif()




# add the mtl headers
include_directories(../../mtl)

# add all tests except mtl::console tests
add_executable(tests main.cpp tests_algorithm.cpp tests_conversion.cpp tests_container.cpp tests_filesystem.cpp tests_math.cpp tests_numeric.cpp tests_random.cpp tests_safety.cpp tests_stopwatch.cpp tests_string.cpp tests_type_traits.cpp tests_utility.cpp tests_xoroshiro128plus.cpp tests_xorshift128plus.cpp tests_xoshiro256plus.cpp)

# this option will enable mtl::console tests
option(ENABLE_CONSOLE_TESTS "Enable mtl::console tests." OFF)

# if the option is enabled add the file responsible for testing mtl::console
if(ENABLE_CONSOLE_TESTS)
    message("-- Enabled tests for mtl::console")
    target_sources(tests PRIVATE tests_console.cpp)
endif()
