#find_package(ftxui CONFIG REQUIRED)
#add_library(ftx ftx.cpp)
#target_link_libraries(ftx PRIVATE ftxui::dom ftxui::screen ftxui::component)

add_library(ui ui.cpp train.cpp add.cpp list.cpp)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
target_link_libraries(ui PRIVATE ${GTKMM_LIBRARIES})
target_include_directories(ui PRIVATE ${GTKMM_INCLUDE_DIRS})