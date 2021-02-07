#include <gtest/gtest.h>
#include "Trie.h"

TEST(trie, basic) { // NOLINT
    Trie<int> trie;
    trie.put("she", 0);
    trie.put("sells", 1);
    trie.put("sea", 2);
    trie.put("shells", 3);
    trie.put("by", 4);
    trie.put("the", 5);
    trie.put("sea", 6);
    trie.put("shore", 7);

    EXPECT_EQ(*trie.get("she"), 0);
    EXPECT_EQ(*trie.get("sells"), 1);
    EXPECT_EQ(*trie.get("sea"), 6);
    EXPECT_EQ(*trie.get("shells"), 3);
    EXPECT_EQ(*trie.get("by"), 4);
    EXPECT_EQ(*trie.get("the"), 5);
    EXPECT_EQ(*trie.get("shore"), 7);
    EXPECT_FALSE(trie.get("seller"));
    EXPECT_FALSE(trie.get("sh"));
    EXPECT_FALSE(trie.contains("Benedict"));
    EXPECT_TRUE(trie.contains("shore"));
}
