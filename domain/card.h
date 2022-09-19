//
// Created by biosvos on 9/19/22.
//

#ifndef MEMORIZE_CARD_H
#define MEMORIZE_CARD_H

#include <string>
#include <vector>

class Card {
public:
    Card(std::string_view word, const std::vector<std::string_view> &meanings);

public:
    [[nodiscard]] const std::string &GetWord() const;

    [[nodiscard]] const std::vector<std::string> &GetMeanings() const;

private:
    std::string word_;
    std::vector<std::string> meanings_;
    uint64_t next_time_in_sec_;
    uint64_t success_times_in_a_row_;
};

#endif //MEMORIZE_CARD_H
