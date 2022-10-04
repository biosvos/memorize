//
// Created by biosvos on 9/29/22.
//

#ifndef MEMORIZE_CARD_CONTROLLER_H
#define MEMORIZE_CARD_CONTROLLER_H

#include <system_error>

#include "../usecase/add_card.h"

class CardController {
public:
    void Create(const std::string &word, const std::vector<std::string> &meanings, uint64_t create_time);

    explicit CardController(std::shared_ptr<AddCard::IRequester> requester);

private:
    std::shared_ptr<AddCard::IRequester> add_requester_;
};


#endif //MEMORIZE_CARD_CONTROLLER_H
