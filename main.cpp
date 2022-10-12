#include <utility>

#include "adapter/memory_repository.h"
#include "adapter/forgetting_curve.h"
#include "infra/nana_ui.h"
#include "infra/gtk_ui.h"

class Factory : public IFactory {
public:
    explicit Factory(std::shared_ptr<ICardRepository> repository) : repository_(std::move(repository)) {}

    std::shared_ptr<CardController> CreateController(std::shared_ptr<NanaUi> ui) override {
        auto add_card = std::make_shared<AddCardUsecase>(ui, repository_);
        auto update_card = std::make_shared<UpdateCardUsecase>(ui, repository_);
        auto list_cards = std::make_shared<ListCardsUsecase>(ui, repository_);
        auto forgetting_curve = std::make_shared<ForgettingCurve>();
        auto predict = std::make_shared<PredictTrainingCasesUsecase>(ui, forgetting_curve);
        return std::make_shared<CardController>(add_card, update_card, list_cards, predict);
    }

private:
    std::shared_ptr<ICardRepository> repository_;
};

int main() {
    auto app = std::make_shared<GtkUi>();
    app->Run();
//    auto repository = std::make_shared<MemoryRepository>();
//    auto factory = std::make_shared<Factory>(repository);
//    auto app = std::make_shared<NanaUi>();
//    app->SetController(factory);
//    app->Run();
    return 0;
}