//
// Created by biosvos on 9/29/22.
//

#include "card_controller.h"

#include <utility>

CardController::CardController(std::shared_ptr<AddCard::IRequester> requester) :
        add_requester_(std::move(requester)) {}

void
CardController::Create(const std::string &word, const std::vector<std::string> &meanings, uint64_t create_time) {
    add_requester_->Request(AddCardRequest{word, meanings, create_time});
}

