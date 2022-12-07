//
// Created by biosvos on 12/5/22.
//

#include "ftx.h"

#include <utility>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <sstream>

namespace {
    std::string &LeftTrim(std::string &s) {
        auto it = std::find_if(s.begin(), s.end(),
                               [](char c) {
                                   return !std::isspace<char>(c, std::locale::classic());
                               });
        s.erase(s.begin(), it);
        return s;
    }

    std::string &RightTrim(std::string &s) {
        auto it = std::find_if(s.rbegin(), s.rend(),
                               [](char c) {
                                   return !std::isspace<char>(c, std::locale::classic());
                               });
        s.erase(it.base(), s.end());
        return s;
    }

    std::string &Trim(std::string &s) {
        return LeftTrim(RightTrim(s));
    }

    std::vector<std::string> Split(std::string str, const std::string &delim) {
        size_t pos;
        std::vector<std::string> ret;
        std::string token;
        while ((pos = str.find(delim)) != std::string::npos) {
            token = str.substr(0, pos);
            ret.push_back(Trim(token));
            str.erase(0, pos + delim.length());
        }
        ret.push_back(Trim(str));
        return ret;
    }

    uint64_t CurrentTime() {
        auto now = std::chrono::system_clock::now().time_since_epoch();
        return std::chrono::duration_cast<std::chrono::seconds>(now).count();
    }

    std::string Join(std::vector<std::string> strings) {
        auto len = strings.size();
        if (len == 0) {
            return "";
        }

        std::ostringstream oss;
        oss << strings[0];
        for (int i = 1; i < len; ++i) {
            oss << ", ";
            oss << strings[i];
        }
        return oss.str();
    }
}

Ftx::Ftx(std::shared_ptr<IUsecase> usecase) : usecase_(std::move(usecase)) {}

void Ftx::List() {
    auto cards = usecase_->ListCards();

    std::vector<std::vector<ftxui::Element>> datas;

    for (const auto &item: cards) {
        auto &n = datas.emplace_back();
        n.emplace_back(ftxui::text(item.word));
        n.emplace_back(ftxui::text(Join(item.meanings)));
        n.emplace_back(ftxui::text(std::to_string(item.next_time)));
        n.emplace_back(ftxui::text(std::to_string(item.nr_success)));
    }

    ftxui::Table table(datas);

    auto renderer = ftxui::Renderer([&] {
        return ftxui::vbox({
                                   table.Render()
                           });
    });
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    screen.Loop(renderer);
}

void Ftx::Train2(IUsecase::Card &card) {
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    std::function<void()> right_clicked = [&] {
        usecase_->RightWithCard(card, CurrentTime());
        screen.ExitLoopClosure()();
    };
    auto right_button = ftxui::Button("Right", right_clicked);
    std::function<void()> wrong_clicked = [&] {
        usecase_->WrongWithCard(card, CurrentTime());
        screen.ExitLoopClosure()();
    };
    auto wrong_button = ftxui::Button("Wrong", wrong_clicked);

    auto components = ftxui::Container::Horizontal({
                                                           right_button,
                                                           wrong_button
                                                   });

    components |= ftxui::CatchEvent([&](const ftxui::Event &event) {
        if (event == ftxui::Event::Return) {
            right_clicked();
            return true;
        }

        if (event.is_character()) {
            if (event.character() == "1") {
                right_clicked();
                return true;
            }
            if (event.character() == "2") {
                wrong_clicked();
                return true;
            }
        }
        return false;
    });


    auto renderer = ftxui::Renderer(components, [&] {
        return ftxui::vbox({
                                   ftxui::text(card.word),
                                   ftxui::text(Join(card.meanings)),
                                   ftxui::hbox({
                                                       components->Render()
                                               })
                           });
    });

    screen.Loop(renderer);
}

void Ftx::Train1(IUsecase::Card &card) {
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    std::function<void()> show_clicked = [&] {
        Train2(card);
        screen.ExitLoopClosure()();
    };
    auto show_button = ftxui::Button("Show", show_clicked);

    auto components = ftxui::Container::Vertical({
                                                         show_button
                                                 });
    components |= ftxui::CatchEvent([&](const ftxui::Event &event) {
        if (event == ftxui::Event::Return) {
            show_clicked();
            return true;
        }
        return false;
    });

    auto renderer = ftxui::Renderer(components, [&] {
        return ftxui::vbox({
                                   ftxui::text(card.word),
                                   show_button->Render()
                           });
    });
    screen.Loop(renderer);
}

void Ftx::Add() {
    std::string word;
    std::string meanings;

    auto word_input = ftxui::Input(&word, "word");
    auto meanings_input = ftxui::Input(&meanings, "meanings");

    auto screen = ftxui::ScreenInteractive::Fullscreen();
    std::function<void()> add_clicked = [&] {
        usecase_->AddCard(IUsecase::Card{word, Split(meanings, ","), CurrentTime(), 0});
        word.clear();
        meanings.clear();
        word_input->TakeFocus();
    };
    auto add_button = ftxui::Button("Add", add_clicked);
    auto back_button = ftxui::Button("Back", screen.ExitLoopClosure());

    auto components = ftxui::Container::Vertical({
                                                         word_input,
                                                         meanings_input,
                                                         ftxui::Container::Horizontal(
                                                                 {
                                                                         add_button,
                                                                         back_button
                                                                 }
                                                         )
                                                 });

    components |= ftxui::CatchEvent([&](const ftxui::Event &event) {
        if (event == ftxui::Event::Escape) {
            screen.ExitLoopClosure()();
            return true;
        }
        if (event == ftxui::Event::Return) {
            if (word_input->Focused() and word.length() > 0) {
                meanings_input->TakeFocus();
                return true;
            } else if (meanings_input->Focused() and meanings.length() > 0) {
                add_clicked();
                return true;
            }
        }
        return false;
    });

    auto renderer = ftxui::Renderer(components, [&] {
        return ftxui::vbox({
                                   word_input->Render(),
                                   meanings_input->Render(),
                                   ftxui::hbox({
                                                       add_button->Render(),
                                                       back_button->Render()
                                               })
                           });
    });

    screen.Loop(renderer);
}

void Ftx::MainEntry() {
    auto buttons = ftxui::Container::Horizontal({
                                                        ftxui::Button("Train", [&] {
                                                            auto card = usecase_->DrawCard(CurrentTime());
                                                            while (card) {
                                                                Train1(card.value());
                                                            }
                                                        }),
                                                        ftxui::Button("Add", [&] { Add(); }),
                                                        ftxui::Button("List", [&] { List(); })
                                                });
    auto component = ftxui::Renderer(buttons, [&] {
        return ftxui::vbox(
                {
                        buttons->Render()
                }
        );
    });
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    screen.Loop(component);
}

void Ftx::Run() {
    MainEntry();
}
