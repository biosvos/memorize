//
// Created by biosvos on 9/30/22.
//

#include <iostream>

#include "app.h"

void App::SetController(const std::shared_ptr<IFactory> &factory) {
    controller_ = factory->CreateController(shared_from_this());
}

void App::Response(const AddCardResponse &rsp) {
    std::cout << rsp.word << " ";
    switch (rsp.result) {
        case AddCardError::kAddCardOk:
            std::cout << "created";
            break;
        case AddCardError::kAddCardConflicted:
            std::cout << "conflicted";
            break;
        case AddCardError::kAddCardUnknown:
            std::cout << "unknown";
            break;
    }
    std::cout << std::endl;
}

void App::Run() {
    controller_->Create("word", {"가"}, 123);
}
