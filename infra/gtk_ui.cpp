//
// Created by biosvos on 10/11/22.
//

#include <gtkmm.h>
#include <iostream>
#include <utility>
#include "gtk_ui.h"

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
    ListWidget() {
        Gtk::ListViewText view(4);
        set_child(view);
        view.set_column_title(0, "word");
        view.set_column_title(1, "meanings");
        view.set_column_title(2, "next");
        view.set_column_title(3, "success");

        auto row = view.append();
        view.set_text(row, 0, "a");
        view.set_text(row, 1, "b");
        view.set_text(row, 2, "c");
        view.set_text(row, 3, "d");
    }
};

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


class MainWindow : public Gtk::Window, public UiInteractor {
public:
    std::string GetWord() override {
        auto str = std::string(add_.word_entry_.get_text());
        return ::Trim(str);
    }


    std::vector<std::string> GetMeanings() override {
        auto str = add_.meanings_entry_.get_text();
        return Split(str, ",");
    }

    void Clear() override {
        add_.word_entry_.set_text("");
        add_.meanings_entry_.set_text("");
    }

    void Disable() override {
        add_.button_.set_sensitive(false);
        add_.word_entry_.set_sensitive(false);
        add_.meanings_entry_.set_sensitive(false);
    }

    void Enable() override {
        add_.word_entry_.set_sensitive(true);
        add_.meanings_entry_.set_sensitive(true);
        add_.button_.set_sensitive(true);
    }

//    ~MainWindow() = default;

    explicit MainWindow(const std::shared_ptr<CardController> &controller) {
        set_title("Basic application");
        set_default_size(200, 200);
        set_child(notebook_);

        notebook_.set_expand();
        notebook_.append_page(add_, "add");
        notebook_.append_page(train_, "train");
        notebook_.append_page(list_, "list");
        notebook_.show();

        SetSignals(controller);
    }

    void SetSignals(const std::shared_ptr<CardController> &controller) {
        add_.button_.signal_clicked().connect([&]() {
            Disable();
            controller->Create(GetWord(), GetMeanings(), 0);
        });
    }

    Gtk::Notebook notebook_;
    AddWidget add_;
    TrainWidget train_;
    ListWidget list_;
};


void GtkUi::Run() {
    auto controller = factory_->CreateController(shared_from_this());
    auto app = Gtk::Application::create("org.gtkmm.examples.base");

    auto window = std::make_shared<MainWindow>(controller);
    interactor_ = window;

    app->signal_activate().connect([&]() {
        app->add_window(*window);
        window->show();
    });
    app->signal_shutdown().connect([&]() {});
    app->run();
}

GtkUi::GtkUi(std::shared_ptr<IFactory<GtkUi>> factory) : factory_(std::move(factory)) {
}

void GtkUi::Response(const AddCardResponse &rsp) {
    switch (rsp.result) {
        case AddCardError::kAddCardOk:
            std::cout << "ok" << std::endl;
            break;
        case AddCardError::kAddCardConflicted:
            std::cout << "already exists" << std::endl;
            break;
        case AddCardError::kAddCardUnknown:
            std::cout << "unknown error" << std::endl;
            break;
    }
    interactor_->Clear();
    interactor_->Enable();
}

void GtkUi::Response(const ListCardsResponse &rsp) {
}

void GtkUi::Response(const UpdateCardResponse &rsp) {

}

void GtkUi::Response(const PredictTrainingCasesResponse &rsp) {

}
