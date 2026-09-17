cmake_minimum_required(VERSION 3.21)

project(PokerSimulator VERSION 2.0.0 LANGUAGES CXX)

option(POKER_FETCH_SFML "Download SFML when it is not installed on the system" ON)
option(POKER_BUILD_TESTS "Build the automated test suite" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 2.5 COMPONENTS graphics window system CONFIG QUIET)

if(NOT TARGET sfml-graphics)
    if(NOT POKER_FETCH_SFML)
        message(FATAL_ERROR "SFML 2.5+ was not found. Install SFML or configure with -DPOKER_FETCH_SFML=ON.")
    endif()

    include(FetchContent)
    if(NOT DEFINED BUILD_SHARED_LIBS)
        set(BUILD_SHARED_LIBS ON CACHE BOOL "Build third-party libraries as shared libraries")
    endif()
    set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
    set(SFML_INSTALL_PKGCONFIG_FILES OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(sfml)
endif()

add_library(poker_core STATIC
    src/domain/Card.cpp
    src/domain/Deck.cpp
    src/domain/HandEvaluator.cpp
)

target_include_directories(poker_core PUBLIC include)

target_compile_features(poker_core PUBLIC cxx_std_17)

if(MSVC)
    target_compile_options(poker_core PRIVATE /W4 /permissive-)
else()
    target_compile_options(poker_core PRIVATE -Wall -Wextra -Wpedantic -Wconversion)
endif()

add_executable(poker_simulator
    src/main.cpp
    src/ui/GameApp.cpp
)

target_link_libraries(poker_simulator PRIVATE poker_core sfml-graphics sfml-window sfml-system)
set_target_properties(poker_simulator PROPERTIES
    BUILD_RPATH "$ORIGIN"
    INSTALL_RPATH "$ORIGIN"
)

add_custom_command(TARGET poker_simulator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:poker_simulator>/assets
)
add_custom_command(TARGET poker_simulator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-graphics>
        $<TARGET_FILE:sfml-window>
        $<TARGET_FILE:sfml-system>
        $<TARGET_FILE_DIR:poker_simulator>
)

if(UNIX AND NOT APPLE)
    add_custom_command(TARGET poker_simulator POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_SONAME_FILE:sfml-graphics>
            $<TARGET_SONAME_FILE:sfml-window>
            $<TARGET_SONAME_FILE:sfml-system>
            $<TARGET_FILE_DIR:poker_simulator>
    )
endif()

include(GNUInstallDirs)
install(TARGETS poker_simulator RUNTIME DESTINATION .)
install(DIRECTORY assets DESTINATION .)

if(POKER_BUILD_TESTS)
    include(CTest)
    if(BUILD_TESTING)
        add_executable(hand_evaluator_tests tests/HandEvaluatorTests.cpp)
        target_link_libraries(hand_evaluator_tests PRIVATE poker_core)
        add_test(NAME hand_evaluator_tests COMMAND hand_evaluator_tests)
    endif()
endif()
