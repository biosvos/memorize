//
// Created by biosvos on 10/11/22.
//

#ifndef MEMORIZE_GTK_UI_H
#define MEMORIZE_GTK_UI_H

#include "../adapter/card_controller.h"

class UiInteractor {
public:
    virtual ~UiInteractor() = default;

    virtual std::string GetWordInAdd() = 0;

    virtual std::vector<std::string> GetMeaningsInAdd() = 0;

    virtual void ClearInAdd() = 0;

    virtual void DisableInAdd() = 0;

    virtual void EnableInAdd() = 0;

    virtual void ClearInList() = 0;

    struct Card {
        std::string word;
        std::vector<std::string> meanings;
        uint64_t time;
        uint64_t success;
    };

    virtual void SetInList(const std::vector<Card> &cards) = 0;
};

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
    std::shared_ptr<UiInteractor> interactor_;
};


#endif //MEMORIZE_GTK_UI_H
