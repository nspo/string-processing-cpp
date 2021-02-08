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

    auto keys = trie.keys();
    EXPECT_EQ(keys, (std::vector<std::string> {"by", "sea", "sells", "she", "shells", "shore", "the"}));

    auto keys2 = trie.keysWithPrefix("sh");
    EXPECT_EQ(keys2, (std::vector<std::string> {"she", "shells", "shore"}));

    EXPECT_EQ(trie.longestPrefixOf("shellsort"), "shells");
}

TEST(trie, ip) { // NOLINT
    // separated by each 8 bits although bitwise would be better
    Trie<int, uint8_t , 256> trie;
    trie.put({192, 168, 1}, 9001);
    EXPECT_EQ(trie.longestPrefixOf({192, 168, 1, 210}), (std::basic_string<uint8_t>{192, 168, 1}));
}