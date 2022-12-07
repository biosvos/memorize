//
// Created by biosvos on 12/5/22.
//

#include "ftx.h"

#include <utility>
#include <ftxui/dom/elements.hpp>

Ftx::Ftx(std::shared_ptr<IUsecase> usecase) : usecase_(std::move(usecase)) {}

void Ftx::Run() {
    auto document = ftxui::hbox({
                                        ftxui::text("left-column"),
                                        ftxui::separator(),
                                        ftxui::vbox({
                                                            center(ftxui::text("top")) | ftxui::flex,
                                                            ftxui::separator(),
                                                            center(ftxui::text("bottom")),
                                                    }) | ftxui::flex,
                                        ftxui::separator(),
                                        ftxui::text("right-column"),
                                }) |
            ftxui::border;
    auto screen = ftxui::Screen::Create(ftxui::Dimension::Full(), ftxui::Dimension::Fit(document));
    Render(screen, document);
    screen.Print();
}
