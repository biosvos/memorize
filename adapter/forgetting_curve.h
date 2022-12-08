//
// Created by biosvos on 11/1/22.
//

#ifndef MEMORIZE_FORGETTING_CURVE_H
#define MEMORIZE_FORGETTING_CURVE_H

#include "../usecase/rememberer.h"

class ForgettingCurve : public IRememberer {
public:
    Domain::CardTime PredictSuccess(uint64_t nr_success, Domain::CardTime current_time) override;

    Domain::CardTime PredictFail(uint64_t nr_success, Domain::CardTime current_time) override;

};


#endif //MEMORIZE_FORGETTING_CURVE_H
