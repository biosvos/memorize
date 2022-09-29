//
// Created by biosvos on 9/29/22.
//

#ifndef MEMORIZE_CARD_CONTROLLER_H
#define MEMORIZE_CARD_CONTROLLER_H


#include <system_error>

class CardController {
public:
    virtual std::error_code Create() = 0;

    virtual std::error_code Update() = 0;

    virtual std::error_code Delete() = 0;

    virtual std::error_code List() = 0;

    virtual std::error_code Get() = 0;
};


#endif //MEMORIZE_CARD_CONTROLLER_H
