add_library(app app.cpp)
target_link_libraries(app card_controller)

find_package(Drogon REQUIRED)
add_library(web web.cpp)
target_link_libraries(web Drogon::Drogon)

add_library(drogon_presenter drogon_presenter.cpp)
target_link_libraries(drogon_presenter Drogon::Drogon)