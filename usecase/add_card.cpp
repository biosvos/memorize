//
// Created by biosvos on 9/29/22.
//

#include <utility>
#include <iostream>

#include "../domain/card.h"
#include "add_card.h"

AddCardUsecase::AddCardUsecase(std::shared_ptr<AddCard::IResponder> responder,
                               std::shared_ptr<ICardRepository> repository) :
        responder_(std::move(responder)),
        repository_(std::move(repository)) {}

void AddCardUsecase::Request(const AddCardRequest &req) {
    auto card = repository_->Get(req.word);
    if (card) {
        responder_->Response(AddCardResponse{.word = req.word});
        return;
    }

    auto err = repository_->Add(Card(req.word,
                                     req.meanings,
                                     req.create_time_in_epoch_time,
                                     0));
    if (err) {
        std::cerr << err << std::endl;
        responder_->Response(AddCardResponse{.word = req.word});
        return;
    }

    responder_->Response(AddCardResponse{.word = req.word});
}

