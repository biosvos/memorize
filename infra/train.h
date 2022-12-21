//
// Created by biosvos on 12/20/22.
//

#ifndef MEMORIZE_TRAIN_H
#define MEMORIZE_TRAIN_H

#include <gtkmm.h>

#include "../usecase/usecase.h"

class Train1 : public Gtk::Frame {
public:
    Train1();

    void SetCard(const IUsecase::Card &card);

    void SetClicked(const std::function<void()> &fn);

private:
    Gtk::Box box_;
    Gtk::Label word_;
    Gtk::Button show_;
};

class Train2 : public Gtk::Frame {
public:
    Train2();

    void SetCard(const IUsecase::Card &card);

    void SetClicked(const std::function<void()> &right_fn, const std::function<void()> &wrong_fn);

private:
    Gtk::Box box_;
    Gtk::Label word_;
    Gtk::Label meanings_;
    Gtk::Box button_box_;
    Gtk::Button right_;
    Gtk::Button wrong_;
};

class TrainFrame : public Gtk::Frame {
public:
    explicit TrainFrame(std::shared_ptr<IUsecase> usecase);

private:
    void SetCard(const IUsecase::Card &card);

    std::shared_ptr<IUsecase> usecase_;

    Train1 train_1_;
    Train2 train_2_;

    std::optional<IUsecase::Card> card_;
};

#endif //MEMORIZE_TRAIN_H
