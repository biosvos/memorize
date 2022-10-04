//
// Created by biosvos on 10/4/22.
//

#include "update_card.h"

#include <utility>

UpdateCardUsecase::UpdateCardUsecase(std::shared_ptr<UpdateCard::IResponder> responder,
                                     std::shared_ptr<ICardRepository> repository) :
        responder_(std::move(responder)),
        repository_(std::move(repository)) {}

void UpdateCardUsecase::Request(const UpdateCardRequest &req) {
    auto card = repository_->Get(req.word);
    if (!card) {
        responder_->Response(UpdateCardResponse{.word = req.word, .result = UpdateCardResponse::Result::kNotFound});
        return;
    }

    auto err = repository_->Update(Card(req.word, req.meanings, req.next_time, req.nr_success));
    if (err) {
        responder_->Response(UpdateCardResponse{.word = req.word, .result = UpdateCardResponse::Result::kUnknown});
        return;
    }

    responder_->Response(UpdateCardResponse{.word = req.word, .result = UpdateCardResponse::Result::kOk});
}
