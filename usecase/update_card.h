//
// Created by biosvos on 10/4/22.
//

#ifndef MEMORIZE_UPDATE_CARD_H
#define MEMORIZE_UPDATE_CARD_H

#include <memory>
#include "usecase.h"
#include "card_repository.h"

struct UpdateCardRequest {
    std::string word;
    std::vector<std::string> meanings;
    uint64_t next_time;
    uint64_t nr_success;
};

struct UpdateCardResponse {
    enum class Result {
        kOk,
        kUnprocessableEntity,
        kNotFound,
        kUnknown,
    };
    std::string word;
    Result result;
};

using UpdateCard = Usecase<UpdateCardRequest, UpdateCardResponse>;

class UpdateCardUsecase : public UpdateCard::IRequester {
public:
    UpdateCardUsecase(std::shared_ptr<UpdateCard::IResponder> responder, std::shared_ptr<ICardRepository> repository);

    void Request(const UpdateCardRequest &req) override;

private:
    std::shared_ptr<UpdateCard::IResponder> responder_;
    std::shared_ptr<ICardRepository> repository_;
};


#endif //MEMORIZE_UPDATE_CARD_H
