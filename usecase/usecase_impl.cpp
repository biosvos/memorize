//
// Created by biosvos on 10/31/22.
//

#include <utility>
#include <iostream>

#include "usecase_impl.h"
#include "../domain/card.h"

UsecaseImpl::UsecaseImpl(std::shared_ptr<ICardRepository> card_repository) : repository_(
        std::move(card_repository)) {}

std::error_code UsecaseImpl::AddCard(IUsecase::Card card) {
    auto get = repository_->Get(card.word);
    if (get) {
        return CardError::kCardAlreadyExists;
    }

    auto err = repository_->Add(Domain::Card(card.word, card.meanings, card.next_time, 0));
    if (err) {
        std::cerr << __FILE__ << "(@" << __LINE__ << "): " << err << std::endl;
        return CardError::kCardUnknown;
    }
    return {};
}

std::error_code UsecaseImpl::UpdateCard(IUsecase::Card card) {
    auto get = repository_->Get(card.word);
    if (!get) {
        return CardError::kCardNotFound;
    }

    auto err = repository_->Update(Domain::Card(card.word, card.meanings, card.next_time, card.nr_success));
    if (err) {
        std::cerr << __FILE__ << "(@" << __LINE__ << "): " << err << std::endl;
        return CardError::kCardUnknown;
    }

    return {};
}

std::vector<IUsecase::Card> UsecaseImpl::ListCards() {
    std::vector<IUsecase::Card> ret;
    auto cards = repository_->List();

    for (const auto &item: cards) {
        ret.push_back(IUsecase::Card{
                item.GetWord(),
                item.GetMeanings(),
                item.GetNextTimeInSec(),
                item.GetSuccessTimesInARow()
        });
    }

    return ret;
}

std::optional<IUsecase::Card> UsecaseImpl::DrawCard(uint64_t current) {
    auto card = repository_->Draw();
    if (!card) {
        return std::nullopt;
    }
    if (card->GetNextTimeInSec() > current) {
        return std::nullopt;
    }
    return IUsecase::Card{
            .word = card->GetWord(),
            .meanings = card->GetMeanings(),
            .next_time = card->GetNextTimeInSec(),
            .nr_success = card->GetSuccessTimesInARow(),
    };
}

