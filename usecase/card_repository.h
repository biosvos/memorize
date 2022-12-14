//
// Created by biosvos on 9/29/22.
//

#ifndef MEMORIZE_CARD_REPOSITORY_H
#define MEMORIZE_CARD_REPOSITORY_H

#include <optional>

#include "../domain/card.h"

class ICardRepository {
public:
    virtual ~ICardRepository() = default;

    virtual void Add(const Domain::Card &card) = 0;

    virtual void Update(const Domain::Card &card) = 0;

    virtual std::optional<Domain::Card> Get(std::string_view word) = 0;

    virtual std::optional<Domain::Card> Draw() = 0;

    virtual std::vector<Domain::Card> List() = 0;
};


#endif //MEMORIZE_CARD_REPOSITORY_H
