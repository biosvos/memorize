find_package(ftxui CONFIG REQUIRED)
add_library(ftx ftx.cpp)
target_link_libraries(ftx PRIVATE ftxui::dom ftxui::screen ftxui::component)