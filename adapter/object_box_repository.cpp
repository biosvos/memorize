//
// Created by biosvos on 11/11/22.
//

#ifndef OBX_CPP_FILE
#define OBX_CPP_FILE
#endif

#include "object_box_repository.h"
#include "card_store.obx.hpp"
#include "objectbox.hpp"
#include "objectbox-model.h"

void ObjectBoxRepository::Add(const Domain::Card &card) {
    obx::Store store(create_obx_model());
    obx::Box<CardStore> box(store);
    box.put(CardStore{.word = card.GetWord(), .meanings = card.GetMeanings(),
            .time = card.GetNextTime().Nanoseconds(), .success = card.GetSuccessTimesInARow()});
}

void ObjectBoxRepository::Update(const Domain::Card &card) {
    obx::Store store(create_obx_model());
    obx::Box<CardStore> box(store);
    auto query = box.query(CardStore_::word.equals(card.GetWord())).build();
    auto ret = query.findFirst();
    ret->meanings = card.GetMeanings();
    ret->time = card.GetNextTime().Nanoseconds();
    ret->success = card.GetSuccessTimesInARow();
    box.put(*ret);
}

std::optional<Domain::Card> ObjectBoxRepository::Get(std::string_view word) {
    obx::Store store(create_obx_model());
    obx::Box<CardStore> box(store);
    auto query = box.query(CardStore_::word.equals(std::string(word))).build();
    auto ret = query.findFirst();
    if (!ret) {
        return std::nullopt;
    }
    return Domain::Card(ret->word, ret->meanings, Domain::CardTime::FromNanosecond(ret->time), ret->success);
}

std::optional<Domain::Card> ObjectBoxRepository::Draw() {
    obx::Store store(create_obx_model());
    obx::Box<CardStore> box(store);
    auto query = box.query().order(CardStore_::time).build();
    auto ret = query.findFirst();
    if (!ret) {
        return std::nullopt;
    }
    return Domain::Card(ret->word, ret->meanings, Domain::CardTime::FromNanosecond(ret->time), ret->success);
}

std::vector<Domain::Card> ObjectBoxRepository::List() {
    obx::Store store(create_obx_model());
    obx::Box<CardStore> box(store);
    auto query = box.query().build();
    auto cards = query.find();
    std::vector<Domain::Card> ret;
    ret.reserve(cards.size());
    for (const auto &item: cards) {
        ret.emplace_back(item->word, item->meanings, Domain::CardTime::FromNanosecond(item->time), item->success);
    }
    return ret;
}
