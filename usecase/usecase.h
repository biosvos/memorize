//
// Created by biosvos on 9/19/22.
//

#ifndef MEMORIZE_USECASE_H
#define MEMORIZE_USECASE_H

enum class CardError {
    kCardUnknown = 1,
    kCardAlreadyExists,
    kCardNotFound,
};

struct CardErrorCategory : std::error_category {
    [[nodiscard]] const char *name() const noexcept override {
        return "Card";
    }

    [[nodiscard]] std::string message(int err) const override {
        switch (static_cast<CardError>(err)) {
            case CardError::kCardUnknown:
                return "unknown error";
            case CardError::kCardAlreadyExists:
                return "card already exists";
            case CardError::kCardNotFound:
                return "card not found";
            default:
                return "";
        }
    }
};

template<>
struct std::is_error_code_enum<CardError> : true_type {
};

static std::error_code make_error_code(CardError err) {
    static const CardErrorCategory image_error_category;
    return {static_cast<int>(err), image_error_category};
}

class IUsecase {
public:
    struct Card {
        std::string word;
        std::vector<std::string> meanings;
        uint64_t next_time;
        uint64_t nr_success;
    };

public:
    virtual ~IUsecase() = default;

public:
    virtual std::error_code AddCard(IUsecase::Card card) = 0;

    virtual std::error_code UpdateCard(IUsecase::Card card) = 0;

    virtual std::vector<IUsecase::Card> ListCards() = 0;

    virtual std::optional<IUsecase::Card> DrawCard(uint64_t current) = 0;

    virtual std::error_code RightWithCard(IUsecase::Card card, uint64_t current) = 0;

    virtual std::error_code WrongWithCard(IUsecase::Card card, uint64_t current) = 0;
};

#endif //MEMORIZE_USECASE_H
