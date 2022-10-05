//
// Created by biosvos on 9/30/22.
//

#include "memory_repository.h"

std::error_code MemoryRepository::Add(const Card &card) {
    if (cards_.count(card.GetWord()) > 0) {
        return std::make_error_code(std::errc::invalid_argument);
    }
    cards_[card.GetWord()] = card;
    return {};
}

std::optional<Card> MemoryRepository::Get(std::string_view word) {
    if (!cards_.count(std::string(word))) {
        return std::nullopt;
    }
    return cards_[std::string(word)];
}

std::error_code MemoryRepository::Update(const Card &card) {
    if (!cards_.count(card.GetWord())) {
        return std::make_error_code(std::errc::invalid_argument);
    }
    cards_[card.GetWord()] = card;
    return {};
}

std::vector<Card> MemoryRepository::List() {
    std::vector<Card> ret;
    for (const auto &[_, v]: cards_) {
        ret.push_back(v);
    }
    return ret;
}

std::vector<Card> MemoryRepository::ListBefore(uint64_t time) {
    std::vector<Card> ret;
    for (const auto &[_, v]: cards_) {
        if (v.GetNextTimeInSec() < time) {
            ret.push_back(v);
        }
    }
    return ret;
}
