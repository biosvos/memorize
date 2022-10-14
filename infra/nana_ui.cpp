//
// Created by biosvos on 10/7/22.
//

#include <nana/gui.hpp>
#include <nana/gui/widgets/tabbar.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/button.hpp>
#include "nana_ui.h"

void NanaUi::Response(const AddCardResponse &rsp) {

}

void NanaUi::Response(const ListCardsResponse &rsp) {

}

void NanaUi::Response(const UpdateCardResponse &rsp) {

}

void NanaUi::Response(const PredictTrainingCasesResponse &rsp) {

}

void NanaUi::Run() {
    //Define a form.
    nana::form fm;

    //Define a label and display a text.
    nana::label lab{fm, "Hello, <bold blue size=16>Nana C++ Library</>"};
    lab.format(true);

    //Define a button and answer the click event.
    nana::button btn{fm, "Quit"};
    btn.events().click([&fm] {
        fm.close();
    });

    //Layout management
    fm.div("vert <><<><weight=80% text><>><><weight=24<><button><>><>");
    fm["text"] << lab;
    fm["button"] << btn;
    fm.collocate();

    //Show the form
    fm.show();

    //Start to event loop process, it blocks until the form is closed.
    nana::exec();
}

void NanaUi::SetController(const std::shared_ptr<IFactory<NanaUi>> &factory) {
    controller_ = factory->CreateController(shared_from_this());
}
