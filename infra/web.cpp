//
// Created by biosvos on 9/30/22.
//

#include <utility>
#include "web.h"

Web::Web(std::shared_ptr<IWebFactory> factory) :
        factory_(std::move(factory)) {}


void Web::AddCard(const drogon::HttpRequestPtr &req,
                  std::function<void(const drogon::HttpResponsePtr &)> &&callback) const {
    auto json = req->getJsonObject();
    if (json == nullptr) {
        std::cout << "json null" << std::endl;
        callback(drogon::HttpResponse::newNotFoundResponse());
        return;
    }
    std::cout << json->get("word", "") << std::endl;
    auto word = json->get("word", "").asString();
    if (word.empty()) {
        callback(drogon::HttpResponse::newNotFoundResponse());
        return;
    }
    auto controller = factory_->CreateController(callback);
    controller->Create(word, {""}, 0);
}


