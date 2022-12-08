//
// Created by biosvos on 12/8/22.
//

#include <chrono>
#include "card_time.h"

namespace Domain {
    CardTime::CardTime(uint64_t ns) : ns_(ns) {}

    CardTime CardTime::FromNow() {
        auto now = std::chrono::system_clock::now().time_since_epoch();
        return CardTime(std::chrono::duration_cast<std::chrono::nanoseconds>(now).count());
    }

    CardTime CardTime::FromNanosecond(uint64_t nanoseconds) {
        return CardTime(nanoseconds);
    }

    CardTime CardTime::FromSecond(uint64_t seconds) {
        return FromNanosecond(seconds * 1'000'000'000);
    }

    CardTime CardTime::FromMinute(uint64_t minutes) {
        return FromSecond(60 * minutes);
    }

    CardTime CardTime::FromHour(uint64_t hours) {
        return FromMinute(hours * 24);
    }

    CardTime CardTime::FromDay(uint64_t days) {
        return FromHour(days * 24);
    }

    CardTime CardTime::FromWeek(uint64_t weeks) {
        return FromDay(weeks * 7);
    }

    CardTime CardTime::operator+(const CardTime &other) const {
        return CardTime(ns_ + other.ns_);
    }

    uint64_t CardTime::Seconds() const {
        return ns_ / 1'000'000'000;
    }

    bool CardTime::operator!=(const CardTime &other) const {
        return ns_ != other.ns_;
    }

    bool CardTime::operator<=(const CardTime &other) const {
        return ns_ <= other.ns_;
    }

    uint64_t CardTime::Nanoseconds() const {
        return ns_;
    }

    bool CardTime::operator<(const CardTime &other) const {
        return ns_ < other.ns_;
    }
}
