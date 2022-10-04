//
// Created by biosvos on 9/30/22.
//

#include <utility>
#include "web.h"

Web::Web(std::shared_ptr<IWebFactory> factory) :
        factory_(std::move(factory)) {}


void Web::AddCard(const drogon::HttpRequestPtr &req,
                  std::function<void(const drogon::HttpResponsePtr &)> &&callback) const {
    Json::Value json;
    {
        auto ptr = req->getJsonObject();
        if (ptr == nullptr) {
            auto ret = drogon::HttpResponse::newHttpResponse();
            ret->setStatusCode(drogon::k400BadRequest);
            callback(ret);
            return;
        }
        json = *ptr;
    }
    if (json["word"].empty()) {
        auto ret = drogon::HttpResponse::newHttpResponse();
        ret->setStatusCode(drogon::k400BadRequest);
        callback(ret);
        return;
    }
    if (json["meanings"].empty()) {
        auto ret = drogon::HttpResponse::newHttpResponse();
        ret->setStatusCode(drogon::k400BadRequest);
        callback(ret);
        return;
    }
    if (json["time"].empty()) {
        auto ret = drogon::HttpResponse::newHttpResponse();
        ret->setStatusCode(drogon::k400BadRequest);
        callback(ret);
        return;
    }
    auto word = json["word"].asString();
    std::vector<std::string> meanings;
    for (int i = 0; i < json["meanings"].size(); ++i) {
        meanings.push_back(json["meanings"].get(i, "").asString());
    }
    auto time = json["time"].asUInt64();

    auto controller = factory_->CreateController(callback);
    controller->Create(word, meanings, time);
}


