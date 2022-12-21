//
// Created by biosvos on 12/20/22.
//

#include <gtkmm.h>

#include <utility>

#include "train.h"

namespace {
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

TrainFrame::TrainFrame(std::shared_ptr<IUsecase> usecase) :
        usecase_(std::move(usecase)) {
    card_ = usecase_->DrawCard();
    if (card_) {
        set_child(train_1_);
        SetCard(*card_);
    } else {

    }

    train_1_.SetClicked([&] {
        set_child(train_2_);
    });

    train_2_.SetClicked([&] {
        usecase_->RightWithCard(*card_, Domain::CardTime::FromNow());
        card_ = usecase_->DrawCard();
        set_child(train_1_);
    }, [&] {
        usecase_->WrongWithCard(*card_, Domain::CardTime::FromNow());
        card_ = usecase_->DrawCard();
        set_child(train_1_);
    });
}

void TrainFrame::SetCard(const IUsecase::Card &card) {
    train_1_.SetCard(card);
    train_2_.SetCard(card);
}


Train1::Train1() :
        box_(Gtk::Orientation::VERTICAL),
        show_("Show") {
    set_child(box_);

    box_.set_margin(10);
    box_.append(word_);
    box_.append(show_);
}

void Train1::SetCard(const IUsecase::Card &card) {
    word_.set_text(card.word);
}

void Train1::SetClicked(const std::function<void()> &fn) {
    show_.signal_clicked().connect(fn);
}

Train2::Train2() :
        box_(Gtk::Orientation::VERTICAL),
        right_("Right"),
        wrong_("Wrong") {
    set_child(box_);

    box_.set_margin(10);
    box_.append(word_);
    box_.append(meanings_);
    box_.append(button_box_);

    button_box_.append(right_);
    button_box_.append(wrong_);
}

void Train2::SetCard(const IUsecase::Card &card) {
    word_.set_text(card.word);
    meanings_.set_text(Join(card.meanings));
}

void Train2::SetClicked(const std::function<void()> &right_fn, const std::function<void()> &wrong_fn) {
    right_.signal_clicked().connect(right_fn);

    wrong_.signal_clicked().connect(wrong_fn);
}
