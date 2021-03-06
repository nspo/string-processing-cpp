#include <gtest/gtest.h>
#include "KnuthMorrisPratt.h"

//template<typename T>
//void print_vector(const std::vector<T>& v) {
//    for (const auto& elem : v) {
//        std::cout<<elem<<" ";
//    }
//    std::cout<<"\n";
//}

TEST(kmp, single) { // NOLINT
    EXPECT_EQ(*kmp::find_single_match("ABABAC", "ABABACB"), 0);
    EXPECT_EQ(*kmp::find_single_match("ABABAC", "AABABACB"), 1);
    EXPECT_EQ(kmp::find_single_match("ABABAC", "AABABABB").has_value(), false);
    EXPECT_EQ(*kmp::find_single_match("AAAAA", "AAAABAAAAAC"), 5);
}

TEST(kmp, all) { // NOLINT
    EXPECT_EQ(kmp::find_all_matches("A", "BBB"), std::vector<size_t>{});
    EXPECT_EQ(kmp::find_all_matches("A", "AAAAC"), (std::vector<size_t>{0,1,2,3}));
}