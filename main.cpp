#include <utility>

#include "adapter/memory_repository.h"
#include "infra/web.h"
#include "infra/drogon_presenter.h"

class Factory : public IWebFactory {
public:
    explicit Factory(std::shared_ptr<ICardRepository> repository) : repository_(std::move(repository)) {}

public:
    std::shared_ptr<CardController>
    CreateController(std::function<void(const drogon::HttpResponsePtr &)> &callback) override {
        auto presenter = std::make_shared<DrogonPresenter>(callback);
        auto add_card = std::make_shared<AddCardUsecase>(presenter, repository_);
        auto update_card = std::make_shared<UpdateCardUsecase>(presenter, repository_);
        auto list_cards = std::make_shared<ListCardsUsecase>(presenter, repository_);
        return std::make_shared<CardController>(add_card, update_card, list_cards);
    }

private:
    std::shared_ptr<ICardRepository> repository_;
};

int main() {
    auto repository = std::make_shared<MemoryRepository>();
    auto factory = std::make_shared<Factory>(repository);
    auto app = std::make_shared<Web>(factory);
    drogon::app().registerController(app);
    drogon::app().addListener("127.0.0.1", 8888).run();
    return 0;
}