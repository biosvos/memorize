cmake_minimum_required(VERSION 3.23)
project(memorize)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(domain)
add_subdirectory(usecase)
add_subdirectory(adapter)
add_subdirectory(infra)

add_executable(memorize main.cpp)
target_link_libraries(memorize
        app
        add_card memory_repository
        web)
