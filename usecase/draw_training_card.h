//
// Created by biosvos on 10/27/22.
//

#ifndef MEMORIZE_DRAW_TRAINING_CARD_H
#define MEMORIZE_DRAW_TRAINING_CARD_H

#include <memory>
#include "usecase.h"
#include "card_repository.h"

struct DrawTrainingCardRequest {

};

struct DrawTrainingCardResponse {
    std::optional<Card> card;
};

using DrawTrainingCardUsecase = Usecase<DrawTrainingCardRequest, DrawTrainingCardResponse>;

class DrawTrainingCard : public DrawTrainingCardUsecase::IRequester {
public:
    DrawTrainingCard(std::shared_ptr<DrawTrainingCardUsecase::IResponder> responder,
                     std::shared_ptr<ICardRepository> card_repository);

    void Request(const DrawTrainingCardRequest &req) override;

private:
    std::shared_ptr<DrawTrainingCardUsecase::IResponder> responder_;
    std::shared_ptr<ICardRepository> card_repository_;
};

#endif //MEMORIZE_DRAW_TRAINING_CARD_H
