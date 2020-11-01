# CMake build script by Michael Trikergiotis
# 07/09/2020

# CMake 3.8 is the minimum requirement because that is when CMAKE_CXX_STANDARD and 
# CMAKE_CXX_STANDARD_REQUIRED was introduced 
cmake_minimum_required(VERSION 3.8)

project(mtl)

message("-- CMake Vesion is ${CMAKE_VERSION}.")

#set the standard to C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# if we are on Windows use flags appropriate for MSVC, clang-cl, clang or gcc
if (WIN32)
    
    # check if the compiler is Microsoft Visual C++
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        
        message("-- Compiler used MSVC")

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

    #check if the compiler is clang
    elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
        
        # option to enable clang++
        set(ENABLE_GNU_LIKE_CLANG OFF)

        # since CMake 3.15 we can correctly detect and work with both clang++ and clang-cl using 
        # CMAKE_CXX_COMPILER_FRONTEND_VARIANT for more info check
        # https://gitlab.kitware.com/cmake/cmake/-/issues/19724
        if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.15.0")
            if (${CMAKE_CXX_COMPILER_FRONTEND_VARIANT} STREQUAL "GNU")
                message("-- Detected clang++")
                set(ENABLE_GNU_LIKE_CLANG ON)
            endif()
        endif()
       
       
        if(ENABLE_GNU_LIKE_CLANG)
            message("-- Compiler used clang++")   
            
            # enable a lot of warnings and turn them to errors for clang
            add_compile_options(-Werror -Wall -Wextra)            
        else()
            
            message("-- Compiler used clang-cl")

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
 
    endif()
    

    # set tests as the default project for the Visual Studio solution
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT tests) 
    # put the automatically generated projects to their own folder to keep things clean
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# if the we are not in Windows then we must be in Linux or Unix so we  use gcc and clang flags
else()

    if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
        message("-- Compiler used clang++")
    elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
        message("-- Compiler used g++")
    endif()

    # if we are using clang then we may want to use libc++
    if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
        
        # option to enable libc++
        option(ENABLE_LIBCXX "This option enables the libc++." OFF)

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

# add all the source files, except console tests, individually instead of globbing because the 
# makers of CMake recommend against it
# https://cmake.org/cmake/help/latest/command/file.html#filesystem
add_executable(tests main.cpp tests_algorithm.cpp tests_conversion.cpp tests_container.cpp tests_filesystem.cpp tests_math.cpp tests_numeric.cpp tests_random.cpp tests_safety.cpp tests_stopwatch.cpp tests_string.cpp tests_type_traits.cpp tests_utility.cpp tests_xoroshiro128plus.cpp tests_xorshift128plus.cpp tests_xoshiro256plus.cpp)


# option to enable console tests
option(ENABLE_CONSOLE_TESTS "This option enables the mtl::console tests" OFF)

# if the option is enabled add the file responsible for testing mtl::console
if(ENABLE_CONSOLE_TESTS)
    message("-- Enabled tests for mtl::console")
    target_sources(tests PRIVATE tests_console.cpp)
endif()
