cmake_minimum_required(VERSION 3.10)
project(MovieBookingService)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCES "src/*.cpp" "!.src/main.cpp")

add_library(booking_service_lib STATIC ${SOURCES})

# --- Unit Tests with Catch2 ---
find_package(Catch2 REQUIRED)

add_executable(booking_service_tests tests/test_booking_service.cpp)
target_link_libraries(booking_service_tests PRIVATE booking_service_lib Catch2::Catch2WithMain)

add_test(NAME booking_service_tests COMMAND booking_service_tests)