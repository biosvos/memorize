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
            ret->setStatusCode(drogon::k201Created);
            break;
        case AddCardError::kAddCardConflicted:
            ret->setStatusCode(drogon::k409Conflict);
            break;
        case AddCardError::kAddCardUnknown:
            ret->setStatusCode(drogon::k500InternalServerError);
            break;
    }
    callback_(ret);
}

void DrogonPresenter::Response(const UpdateCardResponse &rsp) {
    auto ret = drogon::HttpResponse::newHttpResponse();
    switch (rsp.result) {
        case UpdateCardResponse::Result::kOk:
            ret->setStatusCode(drogon::k200OK);
            break;
        case UpdateCardResponse::Result::kUnprocessableEntity:
            ret->setStatusCode(drogon::k422UnprocessableEntity);
            break;
        case UpdateCardResponse::Result::kNotFound:
            ret->setStatusCode(drogon::k404NotFound);
            break;
        case UpdateCardResponse::Result::kUnknown:
            ret->setStatusCode(drogon::k500InternalServerError);
            break;
    }
    callback_(ret);
}

void DrogonPresenter::Response(const ListCardsResponse &rsp) {
    Json::Value json;

    json["cards"] = Json::Value(Json::arrayValue);
    for (const auto &item: rsp.cards) {
        Json::Value card_json;
        card_json["card"] = Json::Value();

        card_json["card"]["word"] = item.word;
        json["cards"].append(card_json);
//        std::cout << item.word << std::endl;
    }

    auto ret = drogon::HttpResponse::newHttpJsonResponse(json);
//    ret->setStatusCode(drogon::k204NoContent);
    callback_(ret);
}

