
#include <gtest/gtest.h>
#include "RabinKarp.h"

TEST(rk, single) { // NOLINT
    EXPECT_EQ(*rk::find_probabilistic_single_match("ABABAC", "ABABACB"), 0);
    EXPECT_EQ(*rk::find_probabilistic_single_match("ABABAC", "AABABACB"), 1);
    EXPECT_EQ(rk::find_probabilistic_single_match("ABABAC", "AABABABB").has_value(), false);
    EXPECT_EQ(*rk::find_probabilistic_single_match("AAAAA", "AAAABAAAAAC"), 5);
}

TEST(rk, all) { // NOLINT
    EXPECT_EQ(rk::find_probabilistic_all_matches("A", "BBB"), std::vector<size_t>{});
    EXPECT_EQ(rk::find_probabilistic_all_matches("A", "AAAAC"), (std::vector<size_t>{0,1,2,3}));
}