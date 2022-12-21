//
// Created by biosvos on 12/20/22.
//

#ifndef MEMORIZE_ADD_H
#define MEMORIZE_ADD_H

#include <gtkmm.h>

#include "../usecase/usecase.h"

class AddFrame : public Gtk::Frame {
public:
    explicit AddFrame(std::shared_ptr<IUsecase> usecase);

private:
    std::shared_ptr<IUsecase> usecase_;

    Gtk::Grid grid_;
    Gtk::Label word_label_;
    Gtk::Entry word_entry_;
    Gtk::Label meanings_label_;
    Gtk::Entry meanings_entry_;
    Gtk::Button add_;

    std::unique_ptr<Gtk::MessageDialog> dialog_;
};


#endif //MEMORIZE_ADD_H
