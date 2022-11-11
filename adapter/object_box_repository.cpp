//
// Created by biosvos on 11/11/22.
//

#include "object_box_repository.h"
#include "card_store.obx.hpp"
#include "objectbox.hpp"
#include "objectbox-model.h"

std::error_code ObjectBoxRepository::Add(const Domain::Card &card) {
    obx::Store store(create_obx_model());
    obx::Box<CardStore> box(store);
    box.put(CardStore{.word = card.GetWord(), .meanings = card.GetMeanings()});
    return {};
}

std::error_code ObjectBoxRepository::Update(const Domain::Card &card) {
    obx::Store store(create_obx_model());
    obx::Box<CardStore> box(store);
    auto query = box.query(CardStore_::word.equals(card.GetWord())).build();
    auto ret = query.findFirst();
    ret->meanings = card.GetMeanings();
    ret->time = card.GetNextTimeInSec();
    ret->success = card.GetSuccessTimesInARow();
    box.put(*ret);
    return {};
}

std::optional<Domain::Card> ObjectBoxRepository::Get(std::string_view word) {
    obx::Store store(create_obx_model());
    obx::Box<CardStore> box(store);
    auto query = box.query(CardStore_::word.equals(std::string(word))).build();
    auto ret = query.findFirst();
    if (!ret) {
        return std::nullopt;
    }
    return Domain::Card(ret->word, ret->meanings, ret->time, ret->success);
}

std::optional<Domain::Card> ObjectBoxRepository::Draw() {
    obx::Store store(create_obx_model());
    obx::Box<CardStore> box(store);
    auto query = box.query().order(CardStore_::time).build();
    auto ret = query.findFirst();
    return Domain::Card(ret->word, ret->meanings, ret->time, ret->success);
}

std::vector<Domain::Card> ObjectBoxRepository::List() {
    obx::Store store(create_obx_model());
    obx::Box<CardStore> box(store);
    auto query = box.query().build();
    auto cards = query.find();
    std::vector<Domain::Card> ret;
    for (const auto &item: cards) {
        ret.emplace_back(item->word, item->meanings, item->time, item->success);
    }
    return ret;
}
