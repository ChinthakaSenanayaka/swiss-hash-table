cmake_minimum_required(VERSION 3.24)

project(basic_ht_project)

# Abseil requires C++14
set(CMAKE_CXX_STANDARD 14)

# # Local source files here
set(TestInsert TestInsert.cc TestDataUtil.cc TestLogUtil.cc TestPerfCalcUtil.cc)
set(TestSearch TestSearch.cc TestDataUtil.cc TestLogUtil.cc TestPerfCalcUtil.cc)
set(TestDelete TestDelete.cc TestDataUtil.cc TestLogUtil.cc TestPerfCalcUtil.cc)

add_executable(TestInsert ${TestInsert})
add_executable(TestSearch ${TestSearch})
add_executable(TestDelete ${TestDelete})