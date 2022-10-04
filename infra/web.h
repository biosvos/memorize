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
    METHOD_LIST_END

    void
    AddCard(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback) const;

private:
    std::shared_ptr<IWebFactory> factory_;
};

class IWebFactory {
public:
    virtual ~IWebFactory() = default;

    virtual std::shared_ptr<CardController>
    CreateController(std::function<void(const drogon::HttpResponsePtr &)> &callback) = 0;
};


#endif //MEMORIZE_WEB_H
