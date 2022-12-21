//
// Created by biosvos on 12/20/22.
//

#include <gtkmm.h>
#include <iostream>

#include "ui.h"
#include "train.h"
#include "add.h"
#include "list.h"

class MainWindow : public Gtk::Window {
public:
    MainWindow(std::shared_ptr<IUsecase> usecase) :
            usecase_(std::move(usecase)),
            train_(usecase),
            add_(usecase) {
        set_child(notebook_);

        notebook_.append_page(train_, "train");

//        notebook_.signal_realize().connect([&] {
//            std::cout << "work" << std::endl;
//            auto card = usecase_->DrawCard();
//            train_.SetCard(card.value());
//        });
        notebook_.signal_switch_page().connect([](Gtk::Widget *page, guint page_num) {
            std::cout << page_num << std::endl;
        });

        notebook_.append_page(add_, "add");
    }

private:
    Gtk::Notebook notebook_;

    TrainFrame train_;
    AddFrame add_;

    std::shared_ptr<IUsecase> usecase_;
};

Ui::Ui(std::shared_ptr<IUsecase> usecase) :
        usecase_(std::move(usecase)) {}

void Ui::Run() {
    auto app = Gtk::Application::create();
    app->make_window_and_run<MainWindow>(0, nullptr, usecase_);
}
