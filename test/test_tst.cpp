#include <gtest/gtest.h>
#include "TernarySearchTrie.h"

TEST(tst, basic) { // NOLINT
    TernarySearchTrie<int> tst;
    tst.put("she", 0);
    tst.put("sells", 1);
    tst.put("sea", 2);
    tst.put("shells", 3);
    tst.put("by", 4);
    tst.put("the", 5);
    tst.put("sea", 6);
    tst.put("shore", 7);

    EXPECT_EQ(*tst.get("she"), 0);
    EXPECT_EQ(*tst.get("sells"), 1);
    EXPECT_EQ(*tst.get("sea"), 6);
    EXPECT_EQ(*tst.get("shells"), 3);
    EXPECT_EQ(*tst.get("by"), 4);
    EXPECT_EQ(*tst.get("the"), 5);
    EXPECT_EQ(*tst.get("shore"), 7);
    EXPECT_FALSE(tst.get("seller"));
    EXPECT_FALSE(tst.get("sh"));
    EXPECT_FALSE(tst.contains("Benedict"));
    EXPECT_TRUE(tst.contains("shore"));
}
