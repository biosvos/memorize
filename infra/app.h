//
// Created by biosvos on 9/30/22.
//

#ifndef MEMORIZE_APP_H
#define MEMORIZE_APP_H

#include "../usecase/add_card.h"
#include "../adapter/card_controller.h"

class IFactory;

class App : public std::enable_shared_from_this<App>, public AddCard::IResponder {
public:
    void SetController(const std::shared_ptr<IFactory> &factory);

    void Run();

private:
    std::error_code Response(const AddCardResponse &rsp) override;

private:
    std::shared_ptr<CardController> controller_;
};

class IFactory {
public:
    virtual ~IFactory() = default;

    virtual std::shared_ptr<CardController> CreateController(std::shared_ptr<App> app) = 0;
};


#endif //MEMORIZE_APP_H
