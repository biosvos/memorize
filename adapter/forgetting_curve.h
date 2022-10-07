//
// Created by biosvos on 10/7/22.
//

#ifndef MEMORIZE_FORGETTING_CURVE_H
#define MEMORIZE_FORGETTING_CURVE_H

#include "../usecase/prediect_training_cases.h"



class ForgettingCurve : public IRememberer {
public:
    Time PredictSuccess(uint64_t nr_success, uint64_t current_time) override;

    Time PredictFail(uint64_t nr_success, uint64_t current_time) override;

};


#endif //MEMORIZE_FORGETTING_CURVE_H
