//
// Created by biosvos on 10/7/22.
//

#ifndef MEMORIZE_PREDIECT_TRAINING_CASES_H
#define MEMORIZE_PREDIECT_TRAINING_CASES_H

#include <memory>
#include <string>

#include "usecase.h"
#include "../domain/card.h"

class IRememberer {
public:
    struct Time {
        uint64_t next_time;
    };

    virtual ~IRememberer() = default;

    virtual Time PredictSuccess(uint64_t nr_success, uint64_t current_time) = 0;

    virtual Time PredictFail(uint64_t nr_success, uint64_t current_time) = 0;
};

struct PredictTrainingCasesRequest {
    uint64_t nr_success;
    uint64_t current_time;
};

struct PredictTrainingCasesResponse {
    uint64_t success_time;
    uint64_t fail_time;
};

using PredictTrainingCases = Usecase<PredictTrainingCasesRequest, PredictTrainingCasesResponse>;

class PredictTrainingCasesUsecase : public PredictTrainingCases::IRequester {
public:
    explicit PredictTrainingCasesUsecase(std::shared_ptr<PredictTrainingCases::IResponder> responder,
                                         std::shared_ptr<IRememberer> rememberer);

    void Request(const PredictTrainingCasesRequest &req) override;

private:
    std::shared_ptr<PredictTrainingCases::IResponder> responder_;
    std::shared_ptr<IRememberer> rememberer_;
};

#endif //MEMORIZE_PREDIECT_TRAINING_CASES_H
