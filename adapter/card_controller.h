//
// Created by biosvos on 9/29/22.
//

#ifndef MEMORIZE_CARD_CONTROLLER_H
#define MEMORIZE_CARD_CONTROLLER_H

#include <system_error>

#include "../usecase/add_card.h"
#include "../usecase/update_card.h"

class CardController {
public:
    explicit CardController(std::shared_ptr<AddCard::IRequester> requester,
                            std::shared_ptr<UpdateCard::IRequester> update_requester);

    void Create(const std::string &word, const std::vector<std::string> &meanings, uint64_t create_time);

    void Update(const std::string &word, const std::vector<std::string> &meanings, uint64_t next_time, uint64_t success);

private:
    std::shared_ptr<AddCard::IRequester> add_requester_;
    std::shared_ptr<UpdateCard::IRequester> update_requester_;
};


#endif //MEMORIZE_CARD_CONTROLLER_H
