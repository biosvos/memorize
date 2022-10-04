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

enum class AddCardError {
    kAddCardOk,
    kAddCardConflicted,
    kAddCardUnknown,
};

struct AddCardResponse {
    std::string word;
    AddCardError result;
};

using AddCard = Usecase<AddCardRequest, AddCardResponse>;

class AddCardUsecase : public AddCard::IRequester {
public:
    AddCardUsecase(std::shared_ptr<AddCard::IResponder> responder, std::shared_ptr<ICardRepository> repository);

    void Request(const AddCardRequest &req) override;

private:
    std::shared_ptr<AddCard::IResponder> responder_;
    std::shared_ptr<ICardRepository> repository_;
};

#endif //MEMORIZE_ADD_CARD_H
