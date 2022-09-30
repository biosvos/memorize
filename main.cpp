#include <iostream>

#include "infra/app.h"
#include "adapter/memory_repository.h"
#include "usecase/add_card.h"

class Factory : public IFactory {
public:
    std::shared_ptr<CardController> CreateController(std::shared_ptr<App> app) override {
        auto repository = std::make_shared<MemoryRepository>();
        auto add_card = std::make_shared<AddCardUsecase>(app, repository);

        return std::make_shared<CardController>(add_card);
    }
};

int main() {
    auto app = std::make_shared<App>();
    app->SetController(std::make_shared<Factory>());
    app->Run();
    return 0;
}
