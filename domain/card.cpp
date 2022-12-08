//
// Created by biosvos on 9/19/22.
//

#include "card.h"

#include <utility>
#include <stdexcept>

namespace Domain {
    Card::Card() : next_time_(CardTime::FromNanosecond(0)) {}

    Card::Card(std::string word, std::vector<std::string> meanings, CardTime next_time,
               uint64_t success_times_in_a_row) : word_(std::move(word)), meanings_(std::move(meanings)),
                                                  next_time_(next_time),
                                                  success_times_in_a_row_(success_times_in_a_row) {
        if (word_.length() == 0) {
            throw std::invalid_argument("wrong word");
        }

        if (meanings_.empty()) {
            throw std::invalid_argument("wrong meanings");
        }

        for (const auto &item: meanings_) {
            if (item.length() == 0) {
                throw std::invalid_argument("wrong meanings factor");
            }
        }
    }

    const std::string &Card::GetWord() const {
        return word_;
    }

    const std::vector<std::string> &Card::GetMeanings() const {
        return meanings_;
    }

    CardTime Card::GetNextTime() const {
        return next_time_;
    }

    uint64_t Card::GetSuccessTimesInARow() const {
        return success_times_in_a_row_;
    }
}