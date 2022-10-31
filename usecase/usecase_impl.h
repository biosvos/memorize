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

class UsecaseImpl : public IUsecase {
public:
    explicit UsecaseImpl(std::shared_ptr<ICardRepository> card_repository);

    std::error_code AddCard(IUsecase::Card card) override;

    std::error_code UpdateCard(IUsecase::Card card) override;

    std::vector<IUsecase::Card> ListCards() override;

    std::optional<IUsecase::Card> DrawCard(uint64_t current) override;

private:
    std::shared_ptr<ICardRepository> repository_;
};


#endif //MEMORIZE_USECASE_IMPL_H
