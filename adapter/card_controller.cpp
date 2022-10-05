//
// Created by biosvos on 9/29/22.
//

#include "card_controller.h"

#include <utility>

CardController::CardController(std::shared_ptr<AddCard::IRequester> requester,
                               std::shared_ptr<UpdateCard::IRequester> update_requester,
                               std::shared_ptr<ListCards::IRequester> list_requester) :
        add_requester_(std::move(requester)),
        update_requester_(std::move(update_requester)),
        list_requester_(std::move(list_requester)) {}

void
CardController::Create(const std::string &word, const std::vector<std::string> &meanings, uint64_t create_time) {
    add_requester_->Request(AddCardRequest{word, meanings, create_time});
}

void CardController::Update(const std::string &word, const std::vector<std::string> &meanings, uint64_t next_time,
                            uint64_t success) {
    update_requester_->Request(UpdateCardRequest{word, meanings, next_time, success});
}

void CardController::List(uint64_t before) {
    if (before == 0) {
        list_requester_->Request(ListCardsRequest{});
    } else {
        list_requester_->Request(ListCardsRequest{.before = before});
    }
}

