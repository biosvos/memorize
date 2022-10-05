//
// Created by biosvos on 10/5/22.
//

#include "list_cards.h"

#include <utility>

ListCardsUsecase::ListCardsUsecase(std::shared_ptr<ListCards::IResponder> responder,
                                   std::shared_ptr<ICardRepository> repository) :
        responder_(std::move(responder)),
        repository_(std::move(repository)) {}

void ListCardsUsecase::Request(const ListCardsRequest &req) {
    ListCardsResponse rsp;
    std::vector<Card> cards;
    if (req.before) {
        cards = repository_->ListBefore(req.before.value());
    } else {
        cards = repository_->List();
    }

    for (const auto &item: cards) {
        rsp.cards.push_back(ListCardsResponse::Card{
                item.GetWord(),
                item.GetMeanings(),
                item.GetNextTimeInSec(),
                item.GetSuccessTimesInARow()
        });
    }

    responder_->Response(rsp);
}
