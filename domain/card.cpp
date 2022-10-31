//
// Created by biosvos on 9/19/22.
//

#include "card.h"

#include <utility>

namespace Domain {

    Card::Card(std::string word, std::vector<std::string> meanings, uint64_t next_time_in_sec,
               uint64_t success_times_in_a_row) : word_(std::move(word)), meanings_(std::move(meanings)),
                                                  next_time_in_sec_(next_time_in_sec),
                                                  success_times_in_a_row_(success_times_in_a_row) {}

    const std::string &Card::GetWord() const {
        return word_;
    }

    const std::vector<std::string> &Card::GetMeanings() const {
        return meanings_;
    }

    uint64_t Card::GetNextTimeInSec() const {
        return next_time_in_sec_;
    }

    uint64_t Card::GetSuccessTimesInARow() const {
        return success_times_in_a_row_;
    }

}