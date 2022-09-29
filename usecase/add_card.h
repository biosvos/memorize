//
// Created by biosvos on 9/29/22.
//

#ifndef MEMORIZE_ADD_CARD_H
#define MEMORIZE_ADD_CARD_H

#include <memory>
#include <vector>
#include "usecase.h"
#include "card_repository.h"

struct AddCardRequest {
    std::string word;
    std::vector<std::string> meanings;
    uint64_t create_time_in_epoch_time;
};

struct AddCardResponse {
    std::string word;
};

using AddCard = Usecase<AddCardRequest, AddCardResponse>;

class AddCardUsecase : public AddCard::IRequester {
public:
    explicit AddCardUsecase(std::shared_ptr<AddCard::IResponder> responder);

    std::error_code Request(const AddCardRequest &req) override;

private:
    std::shared_ptr<AddCard::IResponder> responder_;
    std::shared_ptr<CardRepository> repository_;
};

#endif //MEMORIZE_ADD_CARD_H
