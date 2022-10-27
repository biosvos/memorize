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
    std::error_code Add(const Card &card) override;

    std::optional<Card> Get(std::string_view word) override;

    std::error_code Update(const Card &card) override;

    std::vector<Card> List() override;

    std::vector<Card> ListBefore(uint64_t time) override;

    std::optional<Card> Draw(uint64_t time) override;

private:
    std::unordered_map<std::string, Card> cards_;
};


#endif //MEMORIZE_MEMORY_REPOSITORY_H
