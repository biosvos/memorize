//
// Created by biosvos on 9/19/22.
//

#ifndef MEMORIZE_CARD_H
#define MEMORIZE_CARD_H

#include <string>
#include <vector>
#include "card_time.h"

namespace Domain {
    class Card {
    public:
        Card();
        Card(std::string word, std::vector<std::string> meanings,
             CardTime next_time,
             uint64_t success_times_in_a_row);

    public:
        [[nodiscard]] const std::string &GetWord() const;

        [[nodiscard]] const std::vector<std::string> &GetMeanings() const;

        [[nodiscard]] CardTime GetNextTime() const;

        [[nodiscard]] uint64_t GetSuccessTimesInARow() const;

    private:
        std::string word_;
        std::vector<std::string> meanings_;
        CardTime next_time_;
        uint64_t success_times_in_a_row_ = 0;
    };
}

#endif //MEMORIZE_CARD_H
