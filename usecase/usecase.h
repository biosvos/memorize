//
// Created by biosvos on 9/19/22.
//

#ifndef MEMORIZE_USECASE_H
#define MEMORIZE_USECASE_H

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
    virtual void AddCard(IUsecase::Card card) = 0;

    virtual void UpdateCard(IUsecase::Card card) = 0;

    virtual std::vector<IUsecase::Card> ListCards() = 0;

    virtual std::optional<IUsecase::Card> DrawCard(uint64_t current) = 0;

    virtual void RightWithCard(IUsecase::Card card, uint64_t current) = 0;

    virtual void WrongWithCard(IUsecase::Card card, uint64_t current) = 0;
};

#endif //MEMORIZE_USECASE_H
