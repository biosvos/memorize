cmake_minimum_required(VERSION 3.23)
project(memorize)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

add_subdirectory(domain)
add_subdirectory(usecase)
add_subdirectory(adapter)
add_subdirectory(infra)

add_executable(memorize main.cpp)
target_link_libraries(memorize PRIVATE
        add_card memory_repository
        update_card
        list_cards
        prediect_training_cases
        nana_ui
        card_controller
        forgetting_curve
        gtk_ui)
