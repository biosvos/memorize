//
// Created by biosvos on 11/1/22.
//

#ifndef MEMORIZE_REMEMBERER_H
#define MEMORIZE_REMEMBERER_H

#include <cstdint>
#include "../domain/card.h"

class IRememberer {
public:
    virtual ~IRememberer() = default;

    virtual Domain::CardTime PredictSuccess(uint64_t nr_success, Domain::CardTime current_time) = 0;

    virtual Domain::CardTime PredictFail(uint64_t nr_success, Domain::CardTime current_time) = 0;
};

#endif //MEMORIZE_REMEMBERER_H
