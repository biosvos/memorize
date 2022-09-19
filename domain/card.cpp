//
// Created by biosvos on 9/19/22.
//

#include "card.h"

Card::Card(std::string_view word, const std::vector<std::string_view> &meanings) : word_(word) {
    for (const auto &item: meanings) {
        meanings_.emplace_back(item);
    }
}

const std::string &Card::GetWord() const {
    return word_;
}

const std::vector<std::string> &Card::GetMeanings() const {
    return meanings_;
}
