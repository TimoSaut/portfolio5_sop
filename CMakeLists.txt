cmake_minimum_required(VERSION 3.29)
project(untitled2 C)

set(CMAKE_C_STANDARD 11)

# Hauptprogramm
add_executable(untitled2
        src/main.c
        src/wc_functions.c
)

# Criterion für Unit Tests einbinden
find_package(PkgConfig REQUIRED)
pkg_check_modules(CRITERION REQUIRED criterion)

# Unit Tests hinzufügen
add_executable(test_wc
        tests/test_wc_functions.c
        tests/test_args.c
        tests/test_output.c
        tests/test_threads.c
        src/wc_functions.c
)

target_link_libraries(test_wc ${CRITERION_LIBRARIES} pthread)
include_directories(${CRITERION_INCLUDE_DIRS} src)

# CTest aktivieren
enable_testing()
add_test(NAME UnitTests COMMAND test_wc)
