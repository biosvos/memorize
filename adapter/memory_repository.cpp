//
// Created by biosvos on 9/30/22.
//

#include "memory_repository.h"

std::error_code MemoryRepository::Add(const Card &card) {
    cards_[card.GetWord()] = card;
    return {};
}

std::optional<Card> MemoryRepository::Get(std::string_view word) {
    if (!cards_.count(std::string(word))) {
        return std::nullopt;
    }
    return cards_[std::string(word)];
}
