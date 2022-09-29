//
// Created by biosvos on 9/29/22.
//

#include <utility>
#include <iostream>

#include "../domain/card.h"
#include "add_card.h"
#include "card_error.h"

AddCardUsecase::AddCardUsecase(std::shared_ptr<AddCard::IResponder> responder) :
        responder_(std::move(responder)) {}

std::error_code AddCardUsecase::Request(const AddCardRequest &req) {
    auto card = repository_->Get(req.word);
    if (card) {
        return CardError::kAddCardConflicted;
    }

    auto err = repository_->Add(Card(req.word,
                                     req.meanings,
                                     req.create_time_in_epoch_time,
                                     0));
    if (err) {
        std::cerr << err << std::endl;
        return CardError::kAddCardUnknown;
    }

    err = responder_->Response(AddCardResponse{.word = req.word});
    if (err) {
        std::cerr << err << std::endl;
        return CardError::kAddCardUnknown;
    }
    return {};
}
