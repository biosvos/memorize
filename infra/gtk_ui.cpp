//
// Created by biosvos on 10/11/22.
//

#include <gtkmm.h>
#include <iostream>
#include <utility>

#include "gtk_ui.h"

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
}

class AddWidget : public Gtk::Frame {
public:
    AddWidget() : button_("add") {
        Gtk::Grid grid;
        set_child(grid);
        Gtk::Label word_label("단어");
        grid.attach(word_label, 0, 0);
        grid.attach(word_entry_, 1, 0);

        Gtk::Label meanings_label("뜻");
        grid.attach(meanings_label, 0, 1);
        grid.attach(meanings_entry_, 1, 1);
        grid.attach(button_, 1, 2);
    }

    Gtk::Entry word_entry_;
    Gtk::Entry meanings_entry_;
    Gtk::Button button_;
};

class TrainWidget : public Gtk::Frame {
public:
    TrainWidget() {
        Gtk::Box box(Gtk::Orientation::VERTICAL);
        set_child(box);
        Gtk::Label word("A");
        Gtk::Label meaings("B");
        Gtk::Button button("button");
        box.append(word);
        box.append(meaings);
        box.append(button);
    }
};

class ListWidget : public Gtk::Frame {
public:
    ListWidget() : view_(4) {
        set_child(view_);
        view_.set_column_title(0, "word");
        view_.set_column_title(1, "meanings");
        view_.set_column_title(2, "next");
        view_.set_column_title(3, "success");
    }

    Gtk::ListViewText view_;
};


class MainWindow : public Gtk::Window, public UiInteractor {
public:
    std::string GetWordInAdd() override {
        auto str = std::string(add_.word_entry_.get_text());
        return ::Trim(str);
    }


    std::vector<std::string> GetMeaningsInAdd() override {
        auto str = add_.meanings_entry_.get_text();
        return Split(str, ",");
    }

    void ClearInAdd() override {
        add_.word_entry_.set_text("");
        add_.meanings_entry_.set_text("");
    }

    void DisableInAdd() override {
        add_.button_.set_sensitive(false);
        add_.word_entry_.set_sensitive(false);
        add_.meanings_entry_.set_sensitive(false);
    }

    void EnableInAdd() override {
        add_.word_entry_.set_sensitive(true);
        add_.meanings_entry_.set_sensitive(true);
        add_.button_.set_sensitive(true);
    }

    void ClearInList() override {
        list_.view_.clear_items();
    }

    void SetInList(const std::vector<Card> &cards) override {
        const char *const delim = ", ";
        for (const auto &item: cards) {
            auto row = list_.view_.append();
            list_.view_.set_text(row, 0, item.word);
            std::ostringstream meanings;
            copy(item.meanings.begin(), item.meanings.end(), std::ostream_iterator<std::string>(meanings, delim));
            list_.view_.set_text(row, 1, meanings.str());
            list_.view_.set_text(row, 2, "c");
            list_.view_.set_text(row, 3, "d");
        }
    }

    explicit MainWindow() {
        set_title("Basic application");
        set_default_size(200, 200);
        set_child(notebook_);

        notebook_.set_expand();
        notebook_.append_page(add_, "add");
        notebook_.append_page(train_, "train");
        notebook_.append_page(list_, "list");
        notebook_.show();

//        SetSignals(controller);
    }

//    void SetSignals(const std::shared_ptr<CardController> &controller) {
//        add_.button_.signal_clicked().connect([&]() {
//            DisableInAdd();
//            controller->Create(GetWordInAdd(), GetMeaningsInAdd(), 0);
//        });
//
//        notebook_.signal_switch_page().connect([&](auto widget, auto page) {
//            std::cout << page << std::endl;
//            if (page == 2) { // list
//                ClearInList();
//                controller->List(std::numeric_limits<time_t>::max());
//            }
//        });
//    }

    Gtk::Notebook notebook_;
    AddWidget add_;
    TrainWidget train_;
    ListWidget list_;
};


void GtkUi::Run() {
//    auto controller = factory_->CreateController(shared_from_this());
    auto app = Gtk::Application::create("org.gtkmm.examples.base");

    auto window = std::make_shared<MainWindow>();
//    interactor_ = window;

    app->signal_activate().connect([&]() {
        app->add_window(*window);
        window->show();
    });
    app->signal_shutdown().connect([&]() {});
    app->run();
}

GtkUi::GtkUi(std::shared_ptr<IUsecase> usecase) : usecase_(std::move(usecase)) {
}

//void GtkUi::Response(const AddCardResponse &rsp) {
//    switch (rsp.result) {
//        case AddCardError::kAddCardOk:
//            std::cout << "ok" << std::endl;
//            break;
//        case AddCardError::kAddCardConflicted:
//            std::cout << "already exists" << std::endl;
//            break;
//        case AddCardError::kAddCardUnknown:
//            std::cout << "unknown error" << std::endl;
//            break;
//    }
//    interactor_->ClearInAdd();
//    interactor_->EnableInAdd();
//}
//
//void GtkUi::Response(const ListCardsResponse &rsp) {
//    std::vector<UiInteractor::Card> cards;
//    for (const auto &item: rsp.cards) {
//        cards.push_back(UiInteractor::Card{item.word, item.meanings, item.next_time, item.nr_success});
//    }
//    interactor_->SetInList(cards);
//}
//
//void GtkUi::Response(const UpdateCardResponse &rsp) {
//
//}
//
//void GtkUi::Response(const PredictTrainingCasesResponse &rsp) {
//
//}
