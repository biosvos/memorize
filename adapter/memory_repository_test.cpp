//
// Created by biosvos on 10/27/22.
//

#include <gtest/gtest.h>
#include "memory_repository.h"

TEST(memory_repository, draw) {
    MemoryRepository repo;
    repo.Add(Card("a", {"a"}, 1, 1));
    repo.Add(Card("b", {"b"}, 2, 2));

    auto card = repo.Draw();

    ASSERT_NE(card, std::nullopt);
    ASSERT_EQ(card->GetNextTimeInSec(), 1);
    ASSERT_EQ(card->GetWord(), "a");
}

TEST(memory_repository, draw_none) {
    MemoryRepository repo;

    auto card = repo.Draw();

    ASSERT_EQ(card, std::nullopt);
}