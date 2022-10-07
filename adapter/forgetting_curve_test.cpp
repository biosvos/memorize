//
// Created by biosvos on 10/7/22.
//

#include <gtest/gtest.h>
#include "forgetting_curve.h"

TEST(ForgettingCurve, 0) {
    ForgettingCurve curve;

    auto ret = curve.PredictSuccess(0, 0);

    ASSERT_EQ(ret.next_time, 10 * 60);
}

TEST(ForgettingCurve, 1) {
    ForgettingCurve curve;

    auto ret = curve.PredictSuccess(1, 0);

    ASSERT_EQ(ret.next_time, 60 * 60 * 24);
}

TEST(ForgettingCurve, 2) {
    ForgettingCurve curve;

    auto ret = curve.PredictSuccess(2, 0);

    ASSERT_EQ(ret.next_time, 60 * 60 * 24 * 7);
}

TEST(ForgettingCurve, 3) {
    ForgettingCurve curve;

    auto ret = curve.PredictSuccess(3, 0);

    ASSERT_EQ(ret.next_time, 60 * 60 * 24 * 7 * 4);
}