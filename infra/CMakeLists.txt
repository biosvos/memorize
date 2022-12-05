find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-4.0)
add_library(gtk_ui gtk_ui.cpp)
target_link_libraries(gtk_ui PRIVATE ${GTKMM_LIBRARIES})
target_include_directories(gtk_ui PRIVATE ${GTKMM_INCLUDE_DIRS})

find_package(unofficial-nana CONFIG REQUIRED)
add_library(nana_ui nana_ui.cpp)
target_link_libraries(nana_ui PRIVATE unofficial::nana::nana)

find_package(ftxui CONFIG REQUIRED)
add_library(ftx ftx.cpp)
target_link_libraries(ftx PRIVATE ftxui::dom ftxui::screen ftxui::component)