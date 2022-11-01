//
// Created by biosvos on 11/1/22.
//

#ifndef MEMORIZE_REMEMBERER_H
#define MEMORIZE_REMEMBERER_H

#include <cstdint>

class IRememberer {
public:
    virtual ~IRememberer() = default;

    virtual uint64_t PredictSuccess(uint64_t nr_success, uint64_t current_time) = 0;

    virtual uint64_t PredictFail(uint64_t nr_success, uint64_t current_time) = 0;
};

#endif //MEMORIZE_REMEMBERER_H
