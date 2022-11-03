//
// Created by biosvos on 9/30/22.
//

#ifndef MEMORIZE_MEMORY_REPOSITORY_H
#define MEMORIZE_MEMORY_REPOSITORY_H

#include <system_error>
#include <unordered_map>
#include "../usecase/card_repository.h"

class MemoryRepository : public ICardRepository {
public:
    std::error_code Add(const Domain::Card &card) override;

    std::optional<Domain::Card> Get(std::string_view word) override;

    std::error_code Update(const Domain::Card &card) override;

    std::vector<Domain::Card> List() override;

    std::vector<Domain::Card> ListBefore(uint64_t time) override;

    std::optional<Domain::Card> Draw() override;

private:
    std::unordered_map<std::string, Domain::Card> cards_;
};


#endif //MEMORIZE_MEMORY_REPOSITORY_H
