cmake_minimum_required(VERSION 3.24)
project(memorize)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
enable_testing()

add_subdirectory(domain)
add_subdirectory(usecase)
add_subdirectory(adapter)
add_subdirectory(infra)

find_package(Argumentum CONFIG REQUIRED)
add_executable(memorize main.cpp)

# argumentum include 파일을 찾지 못해서 아래처럼 우회하는 방법을 적용한다.
target_include_directories(memorize PRIVATE ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include)
target_link_libraries(memorize PRIVATE
        Argumentum::argumentum
        object_box_repository
        usecase_impl
        forgetting_curve
        ui
        ftx
        )

add_executable(instant instant.cpp)
target_link_libraries(instant PRIVATE GTest::gtest GTest::gtest_main)
gtest_discover_tests(instant)
