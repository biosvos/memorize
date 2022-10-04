//
// Created by biosvos on 9/29/22.
//

#ifndef MEMORIZE_CARD_REPOSITORY_H
#define MEMORIZE_CARD_REPOSITORY_H

#include <optional>
#include <system_error>

#include "../domain/card.h"

class ICardRepository {
public:
    virtual ~ICardRepository() = default;

    virtual std::error_code Add(const Card &card) = 0;

    virtual std::error_code Update(const Card &card) = 0;

    virtual std::optional<Card> Get(std::string_view word) = 0;
};


#endif //MEMORIZE_CARD_REPOSITORY_H
