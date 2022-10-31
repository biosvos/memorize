//
// Created by biosvos on 10/27/22.
//

#include "draw_training_card.h"

#include <utility>

DrawTrainingCard::DrawTrainingCard(std::shared_ptr<DrawTrainingCardUsecase::IResponder> responder,
                                   std::shared_ptr<ICardRepository> card_repository) :
        responder_(std::move(responder)),
        card_repository_(std::move(card_repository)) {

}

void DrawTrainingCard::Request(const DrawTrainingCardRequest &req) {
    auto card = card_repository_->Draw();
    if (!card) {
        responder_->Response(DrawTrainingCardResponse{.card=std::nullopt});
        return;
    }
    if (card->GetNextTimeInSec() > req.time) {
        responder_->Response(DrawTrainingCardResponse{.card=std::nullopt});
        return;
    }
    responder_->Response(DrawTrainingCardResponse{.card=card});
}
