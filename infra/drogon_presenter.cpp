//
// Created by biosvos on 10/4/22.
//

#include "drogon_presenter.h"

DrogonPresenter::DrogonPresenter(std::function<void(const drogon::HttpResponsePtr &)> &callback) :
        callback_(callback) {}

void DrogonPresenter::Response(const AddCardResponse &rsp) {
    auto ret = drogon::HttpResponse::newHttpResponse();
    switch (rsp.result) {
        case AddCardError::kAddCardOk:
            ret->setStatusCode(drogon::k200OK);
            callback_(ret);
            break;
        case AddCardError::kAddCardConflicted:
            ret->setStatusCode(drogon::k409Conflict);
            callback_(ret);
            break;
        case AddCardError::kAddCardUnknown:
            ret->setStatusCode(drogon::k404NotFound);
            callback_(ret);
            break;
    }
}

