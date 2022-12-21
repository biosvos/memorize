//
// Created by biosvos on 12/20/22.
//

#include "add.h"

#include <utility>

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

AddFrame::AddFrame(std::shared_ptr<IUsecase> usecase) :
        usecase_(std::move(usecase)),
        word_label_("word"),
        meanings_label_("meanings"),
        add_("Add") {
    set_child(grid_);
    grid_.set_margin(10);
    grid_.set_column_spacing(3);
    grid_.set_row_spacing(3);

    grid_.attach(word_label_, 0, 0);
    grid_.attach(word_entry_, 1, 0);
    grid_.attach(meanings_label_, 0, 1);
    grid_.attach(meanings_entry_, 1, 1);
    grid_.attach(add_, 0, 2, 2);

    add_.signal_clicked().connect([&] {
        auto word = word_entry_.get_text();
        auto meanings = Split(meanings_entry_.get_text(), ",");
        if (word.empty() || meanings.empty()) {
            auto window = dynamic_cast<Gtk::Window *>(get_ancestor(GTK_TYPE_WINDOW));
            dialog_ = std::make_unique<Gtk::MessageDialog>(*window, "fill all");
            dialog_->set_hide_on_close();
            dialog_->set_modal();
            dialog_->signal_response().connect([&](int) {
                dialog_->hide();
            });
            dialog_->show();
            return;
        }

        try {
            usecase_->AddCard(IUsecase::Card{word, meanings, Domain::CardTime::FromNow()});
        } catch (std::logic_error &e) {
            // TODO: 이미 존재한다면 일단 가져와서 해당 카드의 정보를 보여 주고, 업데이트 할지 물어봐야 한다.
            usecase_->UpdateCard(IUsecase::Card{word, meanings, Domain::CardTime::FromNow()});
        }
        word_entry_.set_text("");
        meanings_entry_.set_text("");
        word_entry_.grab_focus();
    });
}
