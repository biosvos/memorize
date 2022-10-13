//
// Created by biosvos on 10/7/22.
//

#ifndef MEMORIZE_NANA_UI_H
#define MEMORIZE_NANA_UI_H


#include <memory>

#include "../usecase/add_card.h"
#include "../usecase/list_cards.h"
#include "../usecase/update_card.h"
#include "../usecase/prediect_training_cases.h"
#include "../adapter/card_controller.h"

class NanaUi : public std::enable_shared_from_this<NanaUi>, public AddCard::IResponder, public ListCards::IResponder,
               public UpdateCard::IResponder, public PredictTrainingCases::IResponder {
public:
    void SetController(const std::shared_ptr<IFactory<NanaUi>> &factory);

    void Run();

    void Response(const PredictTrainingCasesResponse &rsp) override;

    void Response(const UpdateCardResponse &rsp) override;

    void Response(const ListCardsResponse &rsp) override;

    void Response(const AddCardResponse &rsp) override;

private:
    std::shared_ptr<CardController> controller_;
};


#endif //MEMORIZE_NANA_UI_H
