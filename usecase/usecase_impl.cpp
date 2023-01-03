//
// Created by biosvos on 10/31/22.
//

#include <utility>
#include <iostream>

#include "usecase_impl.h"

UsecaseImpl::UsecaseImpl(std::shared_ptr<ICardRepository> card_repository, std::shared_ptr<IRememberer> rememberer) :
        repository_(std::move(card_repository)),
        rememberer_(std::move(rememberer)) {}

void UsecaseImpl::AddCard(IUsecase::Card card) {
    auto get = repository_->Get(card.word);
    if (get) {
        throw std::logic_error("failed to add card, already exists");
    }

    auto domain_card = Domain::Card(card.word, card.meanings, card.next, 0);
    repository_->Add(domain_card);
}

void UsecaseImpl::UpdateCard(IUsecase::Card card) {
    auto get = repository_->Get(card.word);
    if (!get) {
        throw std::logic_error("not found card");
    }

    repository_->Update(Domain::Card(card.word, card.meanings, card.next, card.nr_success));
}

std::optional<IUsecase::Card> UsecaseImpl::DrawCard() {
    auto card = repository_->Draw();
    if (!card) {
        return std::nullopt;
    }
    return IUsecase::Card{
            .word = card->GetWord(),
            .meanings = card->GetMeanings(),
            .next = card->GetNextTime(),
            .nr_success = card->GetSuccessTimesInARow(),
    };
}

void UsecaseImpl::RightWithCard(IUsecase::Card card, Domain::CardTime current) {
    auto get = repository_->Get(card.word);
    if (!get) {
        throw std::logic_error("not found card");
    }

    if (!IsEqual(get.value(), card)) {
        throw std::logic_error("card is not same");
    }

    auto next = rememberer_->PredictSuccess(card.nr_success, current);

    repository_->Update(Domain::Card(card.word, card.meanings, next, card.nr_success + 1));
}

void UsecaseImpl::WrongWithCard(IUsecase::Card card, Domain::CardTime current) {
    auto get = repository_->Get(card.word);
    if (!get) {
        throw std::logic_error("not found card");
    }

    if (!IsEqual(get.value(), card)) {
        throw std::logic_error("card is not same");
    }

    auto next = rememberer_->PredictFail(card.nr_success, current);

    repository_->Update(Domain::Card(card.word, card.meanings, next, 0));
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

    if (real_card.GetNextTime() != requested_card.next) {
        return false;
    }

    if (real_card.GetSuccessTimesInARow() != requested_card.nr_success) {
        return false;
    }

    return true;
}

