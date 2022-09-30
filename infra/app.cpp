//
// Created by biosvos on 9/30/22.
//

#include <iostream>

#include "app.h"

void App::SetController(const std::shared_ptr<IFactory> &factory) {
    controller_ = factory->CreateController(shared_from_this());
}

std::error_code App::Response(const AddCardResponse &rsp) {
    std::cout << rsp.word << " created" << std::endl;
    return {};
}

void App::Run() {
    controller_->Create("word", {"가"}, 123);
}
