cmake_minimum_required( VERSION 3.14)

project (csc746_project LANGUAGES C CXX)

set(CMAKE_BUILD_TYPE "Release")
 
add_executable (omp_count_words omp_count_words.cpp)
target_link_options(omp_count_words PRIVATE -fopenmp)
target_compile_features(omp_count_words PRIVATE c_std_11 c_restrict)
target_compile_options(omp_count_words PRIVATE -fopenmp -Wall -pedantic -march=native)
configure_file(job.in job-openmp)
