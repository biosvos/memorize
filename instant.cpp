//
// Created by biosvos on 12/29/22.
//
#include <gtest/gtest.h>

uint64_t DiffTime(int a_time, int b_time) {
    auto [lower, upper] = std::minmax(a_time, b_time);
    return upper - lower;
}

std::string TimeToString(uint64_t seconds) {
    std::stringstream ss;

    bool flag = false;
    for (auto divisor: {3600, 60}) {
        if (flag || seconds >= divisor) {
            flag = true;
            ss << std::setfill('0') << std::setw(2) << seconds / divisor;
            seconds %= divisor;
            ss << ":";
        }
    }
    ss << std::setfill('0') << std::setw(2) << seconds;

    return ss.str();
}

TEST(instant, b) {
    uint64_t diff = DiffTime(100, 10);
    ASSERT_EQ(diff, 90);
}

TEST(instant, time_to_string) {
    auto str = TimeToString(0);
    ASSERT_EQ(str, "00");
    str = TimeToString(60);
    ASSERT_EQ(str, "01:00");
    str = TimeToString(3600);
    ASSERT_EQ(str, "01:00:00");
    str = TimeToString(122843);
    ASSERT_EQ(str, "34:07:23");
}