
#include <gtest/gtest.h>
#include "BoyerMoore.h"

template<typename T>
void print_map(const T& v) {
    for (const auto& [a,b] : v) {
        std::cout<<a<<":"<<b<<" ";
    }
    std::cout<<"\n";
}

TEST(bm, single) { // NOLINT
    std::string s = "hello";
    auto table = bm::create_bm_table(std::string_view(s));
    EXPECT_EQ(table.size(), 4);
    EXPECT_EQ(table['h'], 0);
    EXPECT_EQ(table['e'], 1);
    EXPECT_EQ(table['l'], 3);
    EXPECT_EQ(table['o'], 4);
    EXPECT_EQ(*bm::find_single_match("ABABAC", "ABABACB"), 0);
    EXPECT_EQ(*bm::find_single_match("ABABAC", "AABABACB"), 1);
    EXPECT_EQ(bm::find_single_match("ABABAC", "AABABABB").has_value(), false);
    EXPECT_EQ(*bm::find_single_match("AAAAA", "AAAABAAAAAC"), 5);
}

TEST(bm, all) { // NOLINT
    EXPECT_EQ(bm::find_all_matches("A", "BBB"), std::vector<size_t>{});
    EXPECT_EQ(bm::find_all_matches("A", "AAAAC"), (std::vector<size_t>{0,1,2,3}));
}