cmake_minimum_required(VERSION 3.24)

project(abseil_swiss_ht_project)

# Abseil requires C++14
set(CMAKE_CXX_STANDARD 14)

# Import Abseil's CMake targets
find_package(absl REQUIRED)

# # Local source files here
set(TestInsert TestInsert.cc TestDataUtil.cc TestLogUtil.cc TestPerfCalcUtil.cc)
set(TestSearch TestSearch.cc TestDataUtil.cc TestLogUtil.cc TestPerfCalcUtil.cc)
set(TestDelete TestDelete.cc TestDataUtil.cc TestLogUtil.cc TestPerfCalcUtil.cc)

add_executable(TestInsert ${TestInsert})
add_executable(TestSearch ${TestSearch})
add_executable(TestDelete ${TestDelete})

# Declare dependency on the absl::strings library
target_link_libraries(TestInsert absl::base absl::raw_hash_set absl::hash)
target_link_libraries(TestSearch absl::base absl::raw_hash_set absl::hash)
target_link_libraries(TestDelete absl::base absl::raw_hash_set absl::hash)