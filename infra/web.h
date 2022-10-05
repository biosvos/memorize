//
// Created by biosvos on 9/30/22.
//

#ifndef MEMORIZE_WEB_H
#define MEMORIZE_WEB_H

#include <drogon/HttpController.h>
#include "../adapter/card_controller.h"

class IWebFactory;

class Web : public drogon::HttpController<Web, false> {
public:
    explicit Web(std::shared_ptr<IWebFactory> factory);

public:
    METHOD_LIST_BEGIN
        METHOD_ADD(Web::AddCard, "/add", drogon::Post);
        METHOD_ADD(Web::UpdateCard, "/update", drogon::Put);
        METHOD_ADD(Web::ListCards, "/list", drogon::Get);
    METHOD_LIST_END

    void
    AddCard(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback) const;

    void
    UpdateCard(const drogon::HttpRequestPtr &req,
               std::function<void(const drogon::HttpResponsePtr &)> &&callback) const;

    void
    ListCards(const drogon::HttpRequestPtr &req,
              std::function<void(const drogon::HttpResponsePtr &)> &&callback) const;

private:
    static void BadRequest(const std::function<void(const drogon::HttpResponsePtr &)> &callback);

    static bool IsExists(Json::Value &json, std::initializer_list<std::string> keys);

    std::shared_ptr<IWebFactory> factory_;

};

class IWebFactory {
public:
    virtual ~IWebFactory() = default;

    virtual std::shared_ptr<CardController>
    CreateController(std::function<void(const drogon::HttpResponsePtr &)> &callback) = 0;
};


#endif //MEMORIZE_WEB_H
