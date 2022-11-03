//
// Created by biosvos on 11/1/22.
//

#include "forgetting_curve.h"

namespace {
    const int kMinute = 60;
    const int kHour = 60 * kMinute;
    const int kDay = 24 * kHour;
    const int kWeek = 7 * kDay;
}

uint64_t ForgettingCurve::PredictSuccess(uint64_t nr_success, uint64_t current_time) {
    switch (nr_success) {
        case 0:
            // 10분 추가
            return current_time + 10 * kMinute;
        case 1:
            // 하루
            return current_time + kDay;
        case 2:
            // 일주일
            return current_time + kWeek;
        case 3:
            // 4 주
            return current_time + 4 * kWeek;
        default:
            // 1년
            return current_time + 365 * kDay;
    }
}

uint64_t ForgettingCurve::PredictFail(uint64_t nr_success, uint64_t current_time) {
    return current_time;
}
