//
// Created by biosvos on 10/7/22.
//

#include "forgetting_curve.h"

static const int kMinute = 60;
static const int kHour = 60 * kMinute;
static const int kDay = 24 * kHour;
static const int kWeek = 7 * kDay;

IRememberer::Time ForgettingCurve::PredictSuccess(uint64_t nr_success, uint64_t current_time) {
    uint64_t ret = current_time;
    switch (nr_success) {
        case 0:
            // 10분 추가
            ret += 10 * kMinute;
            break;
        case 1:
            // 하루
            ret += kDay;
            break;
        case 2:
            // 일주일
            ret += kWeek;
            break;
        case 3:
            // 4 주
            ret += 4 * kWeek;
            break;
        default:
            // 1년
            ret += 365 * kDay;
    }
    return Time{ret};
}

IRememberer::Time ForgettingCurve::PredictFail(uint64_t nr_success, uint64_t current_time) {
    return Time{current_time};
}
