//
// Created by biosvos on 10/11/22.
//

#include <gtkmm.h>
#include <iostream>
#include <utility>
#include <chrono>

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

    uint64_t CurrentTime() {
        auto now = std::chrono::system_clock::now().time_since_epoch();
        return std::chrono::duration_cast<std::chrono::seconds>(now).count();
    }

    std::string Join(std::vector<std::string> strings) {
        std::ostringstream meanings;
        copy(strings.begin(), strings.end(), std::ostream_iterator<std::string>(meanings, ","));
        return meanings.str();
    }
}

class AddWidget : public Gtk::Frame {
public:
    explicit AddWidget(std::shared_ptr<IUsecase> usecase) : usecase_(std::move(usecase)), button_("add") {
        SetLayout();
        SetSignal();
    }

private:
    void SetLayout() {
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

    void SetSignal() {
        button_.signal_clicked().connect(sigc::mem_fun(*this, &AddWidget::ClickAddButton));
    }

    void ClickAddButton() {
        DisableAddButton();
        usecase_->AddCard(IUsecase::Card{.word= GetWord(), .meanings = GetMeanings()});
        Clear();
        EnableAddButton();
    }

    void Clear() {
        word_entry_.set_text("");
        meanings_entry_.set_text("");
    }

    void DisableAddButton() {
        button_.set_sensitive(false);
        word_entry_.set_sensitive(false);
        meanings_entry_.set_sensitive(false);
    }

    void EnableAddButton() {
        word_entry_.set_sensitive(true);
        meanings_entry_.set_sensitive(true);
        button_.set_sensitive(true);
    }

    std::string GetWord() {
        auto str = std::string(word_entry_.get_text());
        return ::Trim(str);
    }

    std::vector<std::string> GetMeanings() {
        auto str = meanings_entry_.get_text();
        return Split(str, ",");
    }

    Gtk::Entry word_entry_;
    Gtk::Entry meanings_entry_;
    Gtk::Button button_;

    std::shared_ptr<IUsecase> usecase_;
};

class TrainWidget : public Gtk::Frame {
public:
    explicit TrainWidget(std::shared_ptr<IUsecase> usecase) :
            usecase_(std::move(usecase)),
            show_button_("show"),
            right_button_("right"),
            wrong_button_("wrong") {
        Gtk::Box box(Gtk::Orientation::VERTICAL);
        set_child(box);
        box.append(word_);
        box.append(meaings_);
        box.append(show_button_);
        box.append(right_button_);
        box.append(wrong_button_);

        show_button_.signal_clicked().connect(sigc::mem_fun(*this, &TrainWidget::ClickShowButton));
        right_button_.signal_clicked().connect(sigc::mem_fun(*this, &TrainWidget::ClickRightButton));
        wrong_button_.signal_clicked().connect(sigc::mem_fun(*this, &TrainWidget::ClickWrongButton));
    }

    void Clear() {
        meaings_.hide();
        right_button_.hide();
        wrong_button_.hide();

        word_.set_text("not found");
        meaings_.set_text("");
        word_.show();
        show_button_.hide();
    }

    void SetCard(const IUsecase::Card &current) {
        current_ = current;
        word_.set_text(current.word);
        meaings_.set_text(Join(current.meanings));

        show_button_.show();
    }

    void ClickShowButton() {
        show_button_.hide();

        meaings_.show();
        right_button_.show();
        wrong_button_.show();
    }

    void ClickRightButton() {
        usecase_->RightWithCard(current_, CurrentTime());
        Clear();
        auto card = usecase_->DrawCard(CurrentTime());
        if (!card) {
            return;
        }
        SetCard(card.value());
    }

    void ClickWrongButton() {
        usecase_->WrongWithCard(current_, CurrentTime());
        Clear();
        auto card = usecase_->DrawCard(CurrentTime());
        if (!card) {
            return;
        }
        SetCard(card.value());
    }

private:
    Gtk::Label word_;
    Gtk::Label meaings_;
    Gtk::Button show_button_;
    Gtk::Button right_button_;
    Gtk::Button wrong_button_;

    std::shared_ptr<IUsecase> usecase_;
    IUsecase::Card current_;
};

class ListWidget : public Gtk::Frame {
public:
    explicit ListWidget(std::shared_ptr<IUsecase> usecase) :
            usecase_(std::move(usecase)),
            view_(4) {
        SetLayout();
    }

    void Activate() {
        Clear();
        auto cards = usecase_->ListCards();
        SetItems(cards);
    }

private:
    void SetLayout() {
        set_child(view_);
        view_.set_column_title(0, "word");
        view_.set_column_title(1, "meanings");
        view_.set_column_title(2, "next");
        view_.set_column_title(3, "success");
    }

    void Clear() {
        view_.clear_items();
    }

    void SetItems(const std::vector<IUsecase::Card> &cards) {
        const char *const delim = ", ";
        for (const auto &item: cards) {
            auto row = view_.append();
            view_.set_text(row, 0, item.word);
            std::ostringstream meanings;
            copy(item.meanings.begin(), item.meanings.end(), std::ostream_iterator<std::string>(meanings, delim));
            view_.set_text(row, 1, meanings.str());
            view_.set_text(row, 2, std::to_string(item.next_time));
            view_.set_text(row, 3, std::to_string(item.nr_success));
        }
    }

    Gtk::ListViewText view_;

    std::shared_ptr<IUsecase> usecase_;
};


class MainWindow : public Gtk::Window {
public:
    explicit MainWindow(std::shared_ptr<IUsecase> usecase) :
            usecase_(std::move(usecase)),
            list_(usecase),
            train_(usecase),
            add_(usecase) {
        set_title("Basic application");
        set_default_size(200, 200);
        set_child(notebook_);

        notebook_.set_expand();
        notebook_.append_page(add_, "add");
        notebook_.append_page(train_, "train");
        notebook_.append_page(list_, "list");
        notebook_.show();

        SetSignals();
    }


    void SetSignals() {
        notebook_.signal_switch_page().connect([&](auto widget, auto page) {
            std::cout << page << std::endl;
            if (page == 1) {
                train_.Clear();
                auto card = usecase_->DrawCard(CurrentTime());
                if (!card) {
                    return;
                }
                train_.SetCard(card.value());
            }
            if (page == 2) { // list
                list_.Activate();
            }
        });
    }

    Gtk::Notebook notebook_;
    AddWidget add_;
    TrainWidget train_;
    ListWidget list_;

    std::shared_ptr<IUsecase> usecase_;
};


void GtkUi::Run() {
    auto app = Gtk::Application::create("org.gtkmm.examples.base");

    auto window = std::make_shared<MainWindow>(usecase_);

    app->signal_activate().connect([&]() {
        app->add_window(*window);
        window->show();
    });
    app->signal_shutdown().connect([&]() {});
    app->run();
}

GtkUi::GtkUi(std::shared_ptr<IUsecase> usecase) : usecase_(std::move(usecase)) {}
