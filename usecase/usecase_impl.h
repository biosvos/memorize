//
// Created by biosvos on 10/31/22.
//

#ifndef MEMORIZE_USECASE_IMPL_H
#define MEMORIZE_USECASE_IMPL_H

#include <system_error>
#include <vector>
#include <optional>
#include <memory>

#include "usecase.h"
#include "card_repository.h"
#include "rememberer.h"

class UsecaseImpl : public IUsecase {
public:
    UsecaseImpl(std::shared_ptr<ICardRepository> card_repository, std::shared_ptr<IRememberer> rememberer);

    std::error_code AddCard(IUsecase::Card card) override;

    std::error_code UpdateCard(IUsecase::Card card) override;

    std::vector<IUsecase::Card> ListCards() override;

    std::optional<IUsecase::Card> DrawCard(uint64_t current) override;

    std::error_code RightWithCard(IUsecase::Card card, uint64_t current) override;

    std::error_code WrongWithCard(IUsecase::Card card, uint64_t current) override;

private:
    std::shared_ptr<ICardRepository> repository_;
    std::shared_ptr<IRememberer> rememberer_;

    static bool IsEqual(const Domain::Card &real_card, const Card &requested_card);
};


#endif //MEMORIZE_USECASE_IMPL_H
