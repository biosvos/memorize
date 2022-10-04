//
// Created by biosvos on 9/30/22.
//

#include "web.h"

#include <utility>


Web::Web(std::shared_ptr<CardController> controller) : controller_(std::move(controller)) {

}

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
    }
    controller_->Create(word, {""}, 0);

    auto rsp = drogon::HttpResponse::newHttpResponse();
    rsp->setStatusCode(drogon::k200OK);
    rsp->setBody("hello");
    callback(rsp);
}

