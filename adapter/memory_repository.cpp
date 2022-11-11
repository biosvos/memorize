//
// Created by biosvos on 9/30/22.
//

#include <algorithm>
#include "memory_repository.h"

std::error_code MemoryRepository::Add(const Domain::Card &card) {
    if (cards_.count(card.GetWord()) > 0) {
        return std::make_error_code(std::errc::invalid_argument);
    }
    cards_[card.GetWord()] = card;
    return {};
}

std::optional<Domain::Card> MemoryRepository::Get(std::string_view word) {
    if (!cards_.count(std::string(word))) {
        return std::nullopt;
    }
    return cards_[std::string(word)];
}

std::error_code MemoryRepository::Update(const Domain::Card &card) {
    if (!cards_.count(card.GetWord())) {
        return std::make_error_code(std::errc::invalid_argument);
    }
    cards_[card.GetWord()] = card;
    return {};
}

std::vector<Domain::Card> MemoryRepository::List() {
    std::vector<Domain::Card> ret;
    for (const auto &[_, v]: cards_) {
        ret.push_back(v);
    }
    return ret;
}

std::optional<Domain::Card> MemoryRepository::Draw() {
    auto it = std::min_element(cards_.begin(), cards_.end(),
                               [](const std::pair<std::string, Domain::Card> &a, const std::pair<std::string, Domain::Card> &b) {
                                   return a.second.GetNextTimeInSec() < b.second.GetNextTimeInSec();
                               });

    if (it == cards_.end()) {
        return std::nullopt;
    }
    return it->second;
}
