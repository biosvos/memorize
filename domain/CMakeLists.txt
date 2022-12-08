add_library(time card_time.cpp)

add_library(card card.cpp)
target_link_libraries(card PRIVATE time)
