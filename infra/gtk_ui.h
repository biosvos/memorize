//
// Created by biosvos on 10/11/22.
//

#ifndef MEMORIZE_GTK_UI_H
#define MEMORIZE_GTK_UI_H

#include "../adapter/card_controller.h"

class GtkUi : public std::enable_shared_from_this<GtkUi>,
              public AddCard::IResponder, public ListCards::IResponder,
              public UpdateCard::IResponder, public PredictTrainingCases::IResponder {
public:
    explicit GtkUi(std::shared_ptr<IFactory<GtkUi>> factory);

    void Run();

    void Response(const PredictTrainingCasesResponse &rsp) override;

    void Response(const UpdateCardResponse &rsp) override;

    void Response(const ListCardsResponse &rsp) override;

    void Response(const AddCardResponse &rsp) override;

private:
    std::shared_ptr<IFactory<GtkUi>> factory_;
};


#endif //MEMORIZE_GTK_UI_H
