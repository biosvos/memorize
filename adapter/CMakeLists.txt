add_library(memory_repository memory_repository.cpp)
target_link_libraries(memory_repository PRIVATE card)
add_executable(memory_repository_test memory_repository_test.cpp)
target_link_libraries(memory_repository_test PRIVATE GTest::gtest GTest::gtest_main memory_repository)

add_library(forgetting_curve forgetting_curve.cpp)

#include(FetchContent)
#FetchContent_Declare(
#        objectbox
#        GIT_REPOSITORY https://github.com/objectbox/objectbox-c.git
#        GIT_TAG v0.18.0
#)
#FetchContent_MakeAvailable(objectbox)
#add_library(object_box_repository object_box_repository.cpp card_store.obx.cpp card_store.obx.hpp)
#target_link_libraries(object_box_repository PRIVATE card objectbox)