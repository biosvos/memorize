add_library(card_controller card_controller.cpp)

add_library(memory_repository memory_repository.cpp)
target_link_libraries(memory_repository card)

add_library(forgetting_curve forgetting_curve.cpp)

add_executable(forgetting_curve_test forgetting_curve_test.cpp)
target_link_libraries(forgetting_curve_test GTest::gtest GTest::gmock_main forgetting_curve)