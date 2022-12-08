//
// Created by biosvos on 10/31/22.
//

#ifndef MEMORIZE_USECASE_IMPL_H
#define MEMORIZE_USECASE_IMPL_H

#include <vector>
#include <optional>
#include <memory>

#include "usecase.h"
#include "card_repository.h"
#include "rememberer.h"

class UsecaseImpl : public IUsecase {
public:
    UsecaseImpl(std::shared_ptr<ICardRepository> card_repository, std::shared_ptr<IRememberer> rememberer);

    void AddCard(IUsecase::Card card) override;

    void UpdateCard(IUsecase::Card card) override;

    std::vector<IUsecase::Card> ListCards() override;

    std::optional<IUsecase::Card> DrawCard() override;

    void RightWithCard(IUsecase::Card card, Domain::CardTime current) override;

    void WrongWithCard(IUsecase::Card card, Domain::CardTime current) override;

private:
    std::shared_ptr<ICardRepository> repository_;
    std::shared_ptr<IRememberer> rememberer_;

    static bool IsEqual(const Domain::Card &real_card, const Card &requested_card);
};


#endif //MEMORIZE_USECASE_IMPL_H
