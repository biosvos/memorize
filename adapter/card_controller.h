//
// Created by biosvos on 9/29/22.
//

#ifndef MEMORIZE_CARD_CONTROLLER_H
#define MEMORIZE_CARD_CONTROLLER_H

#include <system_error>

#include "../usecase/add_card.h"
#include "../usecase/update_card.h"
#include "../usecase/list_cards.h"
#include "../usecase/prediect_training_cases.h"

class CardController {
public:
    CardController(std::shared_ptr<AddCard::IRequester> requester,
                   std::shared_ptr<UpdateCard::IRequester> update_requester,
                   std::shared_ptr<ListCards::IRequester> list_requester,
                   std::shared_ptr<PredictTrainingCases::IRequester> predict_requester);

    void Create(const std::string &word, const std::vector<std::string> &meanings, uint64_t create_time);

    void
    Update(const std::string &word, const std::vector<std::string> &meanings, uint64_t next_time, uint64_t success);

    void List(uint64_t before);

    void Predict(uint64_t nr_success, uint64_t time);

private:
    std::shared_ptr<AddCard::IRequester> add_requester_;
    std::shared_ptr<UpdateCard::IRequester> update_requester_;
    std::shared_ptr<ListCards::IRequester> list_requester_;
    std::shared_ptr<PredictTrainingCases::IRequester> predict_requester_;
};

template<typename T>
class IFactory {
public:
    virtual ~IFactory() = default;

    virtual std::shared_ptr<CardController> CreateController(std::shared_ptr<T> ui) = 0;
};

#endif //MEMORIZE_CARD_CONTROLLER_H
