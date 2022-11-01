//
// Created by biosvos on 10/11/22.
//

#ifndef MEMORIZE_GTK_UI_H
#define MEMORIZE_GTK_UI_H

#include <memory>
#include "../usecase/usecase.h"

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

    virtual void SetInList(const std::vector<UiInteractor::Card> &cards) = 0;
};

class GtkUi {
public:
    explicit GtkUi(std::shared_ptr<IUsecase> usecase);

    void Run();

//    void Response(const PredictTrainingCasesResponse &rsp) override;
//
//    void Response(const UpdateCardResponse &rsp) override;
//
//    void Response(const ListCardsResponse &rsp) override;
//
//    void Response(const AddCardResponse &rsp) override;

private:
    std::shared_ptr<IUsecase> usecase_;
//    std::shared_ptr<UiInteractor> interactor_;
};


#endif //MEMORIZE_GTK_UI_H
