//
// Created by biosvos on 10/5/22.
//

#ifndef MEMORIZE_LIST_CARDS_H
#define MEMORIZE_LIST_CARDS_H

#include <memory>
#include <optional>
#include <vector>
#include <string>
#include "usecase.h"
#include "card_repository.h"

struct ListCardsRequest {
    std::optional<uint64_t> before;
};

struct ListCardsResponse {
    struct Card {
        std::string word;
        std::vector<std::string> meanings;
        uint64_t next_time;
        uint64_t nr_success;
    };
    std::vector<Card> cards;
};

using ListCards = Usecase<ListCardsRequest, ListCardsResponse>;

class ListCardsUsecase : public ListCards::IRequester {
public:
    ListCardsUsecase(std::shared_ptr<ListCards::IResponder> responder, std::shared_ptr<ICardRepository> repository);

    void Request(const ListCardsRequest &req) override;

private:
    std::shared_ptr<ListCards::IResponder> responder_;
    std::shared_ptr<ICardRepository> repository_;
};

#endif //MEMORIZE_LIST_CARDS_H
