//
// Created by biosvos on 9/30/22.
//

#include <utility>
#include "web.h"

Web::Web(std::shared_ptr<IWebFactory> factory) :
        factory_(std::move(factory)) {}

bool Web::IsExists(Json::Value &json, std::initializer_list<std::string> keys) {
    for (const auto &item: keys) {
        if (json[item].empty()) {
            return false;
        }
    }
    return true;
}

void Web::AddCard(const drogon::HttpRequestPtr &req,
                  std::function<void(const drogon::HttpResponsePtr &)> &&callback) const {
    Json::Value json;
    {
        auto ptr = req->getJsonObject();
        if (ptr == nullptr) {
            BadRequest(callback);
            return;
        }
        json = *ptr;
    }

    if (!IsExists(json, {"word", "meanings", "time"})) {
        BadRequest(callback);
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

void Web::UpdateCard(const drogon::HttpRequestPtr &req,
                     std::function<void(const drogon::HttpResponsePtr &)> &&callback) const {
    Json::Value json;
    {
        auto ptr = req->getJsonObject();
        if (ptr == nullptr) {
            BadRequest(callback);
            return;
        }
        json = *ptr;
    }

    if (!IsExists(json, {"word", "meanings", "next_time", "success"})) {
        BadRequest(callback);
    }

    auto word = json["word"].asString();
    std::vector<std::string> meanings;
    for (int i = 0; i < json["meanings"].size(); ++i) {
        meanings.push_back(json["meanings"].get(i, "").asString());
    }
    auto time = json["next_time"].asUInt64();
    auto success = json["success"].asUInt64();

    auto controller = factory_->CreateController(callback);
    controller->Update(word, meanings, time, success);
}

void Web::BadRequest(const std::function<void(const drogon::HttpResponsePtr &)> &callback) {
    auto ret = drogon::HttpResponse::newHttpResponse();
    ret->setStatusCode(drogon::k400BadRequest);
    callback(ret);
}

void Web::ListCards(const drogon::HttpRequestPtr &req,
                    std::function<void(const drogon::HttpResponsePtr &)> &&callback) const {
    auto controller = factory_->CreateController(callback);
    auto before = req->getOptionalParameter<uint64_t>("before");
    if (before) {
        controller->List(before.value());
    } else {
        controller->List(0);
    }
}


