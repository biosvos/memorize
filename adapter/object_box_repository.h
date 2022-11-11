//
// Created by biosvos on 11/11/22.
//

#ifndef MEMORIZE_OBJECT_BOX_REPOSITORY_H
#define MEMORIZE_OBJECT_BOX_REPOSITORY_H

#include "../usecase/card_repository.h"

class ObjectBoxRepository : public ICardRepository {
public:
    std::error_code Add(const Domain::Card &card) override;

    std::error_code Update(const Domain::Card &card) override;

    std::optional<Domain::Card> Get(std::string_view word) override;

    std::optional<Domain::Card> Draw() override;

    std::vector<Domain::Card> List() override;
};


#endif //MEMORIZE_OBJECT_BOX_REPOSITORY_H
