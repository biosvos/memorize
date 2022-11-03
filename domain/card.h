//
// Created by biosvos on 9/19/22.
//

#ifndef MEMORIZE_CARD_H
#define MEMORIZE_CARD_H

#include <string>
#include <vector>

namespace Domain {
    class Card {
    public:
        Card(std::string word, std::vector<std::string> meanings,
             uint64_t next_time_in_sec,
             uint64_t success_times_in_a_row);

        Card() = default;

    public:
        [[nodiscard]] const std::string &GetWord() const;

        [[nodiscard]] const std::vector<std::string> &GetMeanings() const;

        [[nodiscard]] uint64_t GetNextTimeInSec() const;

        [[nodiscard]] uint64_t GetSuccessTimesInARow() const;

    private:
        std::string word_;
        std::vector<std::string> meanings_;
        uint64_t next_time_in_sec_ = 0;
        uint64_t success_times_in_a_row_ = 0;
    };
};

#endif //MEMORIZE_CARD_H
