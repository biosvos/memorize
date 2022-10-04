//
// Created by biosvos on 10/4/22.
//

#ifndef MEMORIZE_DROGON_PRESENTER_H
#define MEMORIZE_DROGON_PRESENTER_H

#include <functional>
#include <drogon/drogon.h>
#include "../usecase/add_card.h"

class DrogonPresenter : public AddCard::IResponder {
public:
    explicit DrogonPresenter(std::function<void(const drogon::HttpResponsePtr &)> &callback);

    void Response(const AddCardResponse &rsp) override;

private:
    std::function<void(const drogon::HttpResponsePtr &)> &callback_;
};


#endif //MEMORIZE_DROGON_PRESENTER_H
