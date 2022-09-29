//
// Created by biosvos on 9/29/22.
//

#ifndef MEMORIZE_CARD_ERROR_H
#define MEMORIZE_CARD_ERROR_H


#include <system_error>

enum class CardError {
    kAddCardConflicted = 1,
    kAddCardUnknown = 2,
};

struct CardErrorCategory : std::error_category {
    [[nodiscard]] const char *name() const noexcept override {
        return "Card";
    }

    [[nodiscard]] std::string message(int err) const override {
        switch (static_cast<CardError>(err)) {
            case CardError::kAddCardConflicted:
                return "failed to add card, it already exists.";
            case CardError::kAddCardUnknown:
                return "failed to add card, unknown error.";
        }
    }
};

template<>
struct [[maybe_unused]] std::is_error_code_enum<CardError> : true_type {
};

[[maybe_unused]] std::error_code make_error_code(CardError err) {
    static const CardErrorCategory category;
    return {static_cast<int>(err), category};
}

#endif //MEMORIZE_CARD_ERROR_H
