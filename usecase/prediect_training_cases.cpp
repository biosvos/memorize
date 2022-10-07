//
// Created by biosvos on 10/7/22.
//

#include "prediect_training_cases.h"

#include <utility>

PredictTrainingCasesUsecase::PredictTrainingCasesUsecase(std::shared_ptr<PredictTrainingCases::IResponder> responder,
                                                         std::shared_ptr<IRememberer> rememberer) :
        responder_(std::move(responder)),
        rememberer_(std::move(rememberer)) {

}

void PredictTrainingCasesUsecase::Request(const PredictTrainingCasesRequest &req) {
    auto success = rememberer_->PredictSuccess(req.nr_success, req.current_time);
    auto fail = rememberer_->PredictFail(req.nr_success, req.current_time);
    PredictTrainingCasesResponse rsp = {
            .success_time = success.next_time,
            .fail_time = success.next_time,
    };

    responder_->Response(rsp);
}
