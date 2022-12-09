cmake_minimum_required(VERSION 3.24)
project(memorize)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
enable_testing()

add_subdirectory(domain)
add_subdirectory(usecase)
add_subdirectory(adapter)
add_subdirectory(infra)

add_executable(memorize main.cpp)
target_link_libraries(memorize PRIVATE
        object_box_repository
        usecase_impl
        forgetting_curve
        ftx
        )
