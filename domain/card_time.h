//
// Created by biosvos on 12/8/22.
//

#ifndef MEMORIZE_CARD_TIME_H
#define MEMORIZE_CARD_TIME_H

#include <cstdint>

namespace Domain {
    struct CardTime {
        static CardTime FromSecond(uint64_t seconds);

        static CardTime FromNanosecond(uint64_t nanoseconds);

        static CardTime FromMinute(uint64_t minutes);

        static CardTime FromHour(uint64_t hours);

        static CardTime FromDay(uint64_t days);

        static CardTime FromWeek(uint64_t weeks);

        static CardTime FromNow();

        CardTime operator+(const CardTime &other) const;

        bool operator!=(const CardTime &other) const;

        bool operator<=(const CardTime &other) const;

        bool operator<(const CardTime &other) const;

        [[nodiscard]] uint64_t Seconds() const;

        [[nodiscard]] uint64_t Nanoseconds() const;

    private:
        explicit CardTime(uint64_t ns);

        uint64_t ns_;
    };
}

#endif //MEMORIZE_CARD_TIME_H
