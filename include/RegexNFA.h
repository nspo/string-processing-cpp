#ifndef STRING_PROCESSING_CPP_REGEXNFA_H
#define STRING_PROCESSING_CPP_REGEXNFA_H

#include <Digraph.h>

#include <string_view>
#include <utility>

// Nondeterministic Finite Automaton to match Regular Expressions
// Assumes:
// - expressions are enclosed with parentheses
// - no escaping of characters
// - . matches every single character
// - * matches 0 or more occurrences of the preceding term (which can be enclosed by parentheses)
// - text does not contain metasymbols
class NFA {
public:
    explicit NFA(std::string _re) : re{std::move(_re)}
    {
        // build epsilon transition digraph
        graph = std::make_unique<digraph::AdjacencyListDigraph>(re.size() + 1);
        std::stack<int> ops; // stack for location of opening parentheses and ors
        for (int i=0; i < re.size(); ++i) {
            int lpIdx = i; // location of left parenthesis, or current if not parenthesized
            if (re[i] == '(' || re[i] == '|') {
                ops.push(i);
            } else if (re[i] == ')') {
                int orIdx = ops.top(); ops.pop();
                if (re[orIdx] == '|') {
                    lpIdx = ops.top(); ops.pop();
                    graph->addEdge(lpIdx, orIdx+1);
                    graph->addEdge(orIdx, i);
                } else {
                    // actually was not a | but (
                    lpIdx = orIdx;
                }
            }

            if (i+1 < re.size() && re[i+1] == '*') {
                // add transitions for closure
                graph->addEdge(lpIdx, i+1);
                graph->addEdge(i+1, lpIdx);
            }

            if (re[i] == '(' || re[i] == ')' || re[i] == '*') {
                // add transition for all metasymbols
                graph->addEdge(i, i+1);
            }
        }
    }

    // does the regular expression match text fully?
    [[nodiscard]]
    bool recognizes(std::string_view text) const {
        // find states reachable via epsilon transitions from start
        digraph::DirectedDFS dfs(*graph, {0});
        std::vector<int> pc; // currently plausible states
        for (int v=0; v<graph->V(); ++v) {
            if (dfs.marked(v)) {
                pc.push_back(v);
            }
        }

        // walk through text
        for (const char c : text) {
            std::vector<int> matches; // all states plausible after using current text character
            for (const int v : pc) {
                if (v == re.size()) continue;
                if (re[v] == c | re[v] == '.') {
                    // character match
                    matches.push_back(v+1);
                }
            }

            // identify plausible states reachable via epsilon transition after character matching
            dfs = digraph::DirectedDFS(*graph, matches);
            pc.clear();
            for (int v=0; v < graph->V(); ++v) {
                if (dfs.marked(v)) {
                    pc.push_back(v);
                }
            }
        }

        // check whether success state was reached after using all text characters
        for (const int v : pc) { // NOLINT
            if (v == re.size()) {
                return true;
            }
        }
        return false;
    }
private:
    std::string re;
    std::unique_ptr<digraph::Digraph> graph;
};

#endif //STRING_PROCESSING_CPP_REGEXNFA_H
