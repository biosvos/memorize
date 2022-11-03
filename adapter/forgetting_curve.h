//
// Created by biosvos on 11/1/22.
//

#ifndef MEMORIZE_FORGETTING_CURVE_H
#define MEMORIZE_FORGETTING_CURVE_H

#include "../usecase/rememberer.h"

class ForgettingCurve : public IRememberer {
public:
    uint64_t PredictSuccess(uint64_t nr_success, uint64_t current_time) override;

    uint64_t PredictFail(uint64_t nr_success, uint64_t current_time) override;

};


#endif //MEMORIZE_FORGETTING_CURVE_H
