add_library(app app.cpp)
target_link_libraries(app card_controller)

find_package(Drogon REQUIRED)
add_library(web web.cpp)
target_link_libraries(web Drogon::Drogon)