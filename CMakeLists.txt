cmake_minimum_required( VERSION 3.14)

project (csc746_project LANGUAGES CXX)

set(CMAKE_BUILD_TYPE "Release")

find_package(LIKWID QUIET)
# use cmake --log-level=debug to see DEBUG messages
if ( LIKWID_FOUND ) 
   message ( STATUS "Likwid: found")
else()
   message( STATUS  "Likwid: NOT found")
endif()
 
add_executable (omp_count_words omp_count_words.cpp)
target_link_options(omp_count_words PRIVATE -fopenmp)
target_compile_features(omp_count_words PRIVATE c_std_11 c_restrict)
if ( LIKWID_FOUND )
   target_include_directories(omp_count_words PRIVATE ${LIKWID_INCLUDE_DIR})
   target_compile_definitions(omp_count_words PRIVATE -DLIKWID_PERFMON)
   target_link_libraries(omp_count_words PRIVATE ${LIKWID_LIBRARIES})
endif ()
target_compile_options(omp_count_words PRIVATE -fopenmp -Wall -pedantic -march=native)
