//
// Created by biosvos on 11/1/22.
//

#include "forgetting_curve.h"

Domain::CardTime ForgettingCurve::PredictSuccess(uint64_t nr_success, Domain::CardTime current_time) {
    switch (nr_success) {
        case 0:
            // 10분 추가
            return current_time + Domain::CardTime::FromMinute(10);
        case 1:
            // 하루
            return current_time + Domain::CardTime::FromDay(1);
        case 2:
            // 일주일
            return current_time + Domain::CardTime::FromWeek(1);
        case 3:
            // 4 주
            return current_time + Domain::CardTime::FromWeek(4);
        default:
            // 1년
            return current_time + Domain::CardTime::FromDay(365);
    }
}

Domain::CardTime ForgettingCurve::PredictFail(uint64_t nr_success, Domain::CardTime current_time) {
    return current_time;
}
