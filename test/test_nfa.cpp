
#include <gtest/gtest.h>
#include "RegexNFA.h"

TEST(digraph, marked) { // NOLINT
    using namespace digraph;
    auto dg = AdjacencyListDigraph(5);
    dg.addEdge(0, 1);
    dg.addEdge(1, 2);
    dg.addEdge(2, 3);
    dg.addEdge(4, 0);
    auto reachability = DirectedDFS(dg, {0,1});
    EXPECT_TRUE(reachability.marked(0));
    EXPECT_TRUE(reachability.marked(1));
    EXPECT_TRUE(reachability.marked(2));
    EXPECT_TRUE(reachability.marked(3));
    EXPECT_TRUE(!reachability.marked(4));
    reachability = DirectedDFS(dg, {4});
    EXPECT_TRUE(reachability.marked(0));
    EXPECT_TRUE(reachability.marked(1));
    EXPECT_TRUE(reachability.marked(2));
    EXPECT_TRUE(reachability.marked(3));
    EXPECT_TRUE(reachability.marked(4));
}

TEST(nfa, basic) { // NOLINT
    auto nfa = NFA("(hello)");
    EXPECT_TRUE(nfa.recognizes("hello"));
    EXPECT_TRUE(!nfa.recognizes("hello!"));
    nfa = NFA("(hel*o)");
    EXPECT_TRUE(nfa.recognizes("heo"));
    EXPECT_TRUE(nfa.recognizes("helo"));
    EXPECT_TRUE(nfa.recognizes("hello"));
    EXPECT_TRUE(nfa.recognizes("helllo"));
    EXPECT_TRUE(nfa.recognizes("hellllo"));
    EXPECT_TRUE(!nfa.recognizes("hello!"));
    EXPECT_TRUE(!nfa.recognizes("hero"));
    nfa = NFA("(he(l|r)*o)");
    EXPECT_TRUE(nfa.recognizes("heo"));
    EXPECT_TRUE(nfa.recognizes("helo"));
    EXPECT_TRUE(nfa.recognizes("hero"));
    EXPECT_TRUE(nfa.recognizes("herlo"));
    EXPECT_TRUE(nfa.recognizes("helrlo"));
    EXPECT_TRUE(nfa.recognizes("helllrrlo"));
    EXPECT_TRUE(!nfa.recognizes("hello!"));
    EXPECT_TRUE(!nfa.recognizes("h"));
}

