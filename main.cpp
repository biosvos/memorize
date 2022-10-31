#include "adapter/memory_repository.h"
#include "infra/gtk_ui.h"
#include "usecase/usecase_impl.h"

//class Factory : public IFactory<GtkUi> {
//public:
//    explicit Factory(std::shared_ptr<ICardRepository> repository) : repository_(std::move(repository)) {}
//
//    std::shared_ptr<CardController> CreateController(std::shared_ptr<GtkUi> ui) override {
//        auto add_card = std::make_shared<AddCardUsecase>(ui, repository_);
//        auto update_card = std::make_shared<UpdateCardUsecase>(ui, repository_);
//        auto list_cards = std::make_shared<ListCardsUsecase>(ui, repository_);
//        auto forgetting_curve = std::make_shared<ForgettingCurve>();
//        auto predict = std::make_shared<PredictTrainingCasesUsecase>(ui, forgetting_curve);
//        return std::make_shared<CardController>(add_card, update_card, list_cards, predict);
//    }
//
//private:
//    std::shared_ptr<ICardRepository> repository_;
//};

int main() {
    auto repository = std::make_shared<MemoryRepository>();
    auto usecase = std::make_shared<UsecaseImpl>(repository);
//    GtkUi(factory);
    auto app = std::make_shared<GtkUi>(usecase);
    app->Run();
//    app->Run();
//    auto app = std::make_shared<NanaUi>();
//    app->SetController(factory);
//    app->Run();
    return 0;
}