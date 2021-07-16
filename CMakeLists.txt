cmake_minimum_required(VERSION 3.10)
project(nc2csv LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wfatal-errors")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

set(THREADS_PERFER_PTHREAD_FLAG ON)
find_package(pybind11 REQUIRED)
find_package(Threads REQUIRED)

set(NC2CSV_SOURCES
        src/main.cpp)

set(COMMON_SOURCES
        src/write.cpp
        src/args.cpp
        src/fastnc.cpp
        src/cftime.cpp
        src/conversionjob.cpp)

set(TESTS
        test/main.cpp src/conversionjob.cpp src/conversionjob.h)

set(HEADERS)

add_executable(nc2csv ${NC2CSV_SOURCES} ${COMMON_SOURCES})
add_executable(tests EXCLUDE_FROM_ALL ${TESTS} ${COMMON_SOURCES})
add_test(n2csvtest tests)

target_link_libraries(nc2csv pybind11::embed)
target_link_libraries(nc2csv netcdf_c++4)
target_link_libraries(nc2csv netcdf)
target_link_libraries(nc2csv Threads::Threads)

target_link_libraries(tests pybind11::embed)
target_link_libraries(tests netcdf_c++4)
target_link_libraries(tests netcdf)
