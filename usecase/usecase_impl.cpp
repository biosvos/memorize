//
// Created by biosvos on 10/31/22.
//

#include <utility>
#include <iostream>

#include "usecase_impl.h"
#include "../domain/card.h"

UsecaseImpl::UsecaseImpl(std::shared_ptr<ICardRepository> card_repository, std::shared_ptr<IRememberer> rememberer) :
        repository_(std::move(card_repository)),
        rememberer_(std::move(rememberer)) {}

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

std::error_code UsecaseImpl::RightWithCard(IUsecase::Card card, uint64_t current) {
    auto get = repository_->Get(card.word);
    if (!get) {
        return CardError::kCardNotFound;
    }

    if (!IsEqual(get.value(), card)) {
        return CardError::kCardUnknown;
    }

    auto next = rememberer_->PredictSuccess(card.nr_success, current);

    auto err = repository_->Update(Domain::Card(card.word, card.meanings, next, card.nr_success + 1));
    if (err) {
        return CardError::kCardUnknown;
    }
    return {};
}

std::error_code UsecaseImpl::WrongWithCard(IUsecase::Card card, uint64_t current) {
    auto get = repository_->Get(card.word);
    if (!get) {
        return CardError::kCardNotFound;
    }

    if (!IsEqual(get.value(), card)) {
        return CardError::kCardUnknown;
    }

    auto next = rememberer_->PredictFail(card.nr_success, current);

    auto err = repository_->Update(Domain::Card(card.word, card.meanings, next, 0));
    if (err) {
        return CardError::kCardUnknown;
    }
    return {};
}

bool UsecaseImpl::IsEqual(const Domain::Card &real_card, const IUsecase::Card &requested_card) {
    if (real_card.GetWord() != requested_card.word) {
        return false;
    }

    if (real_card.GetMeanings().size() != requested_card.meanings.size()) {
        return false;
    }

    for (int i = 0; i < real_card.GetMeanings().size(); ++i) {
        if (real_card.GetMeanings()[i] != requested_card.meanings[i]) {
            return false;
        }
    }

    if (real_card.GetNextTimeInSec() != requested_card.next_time) {
        return false;
    }

    if (real_card.GetSuccessTimesInARow() != requested_card.nr_success) {
        return false;
    }

    return true;
}

