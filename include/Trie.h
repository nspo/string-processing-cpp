#ifndef STRING_PROCESSING_CPP_TRIE_H
#define STRING_PROCESSING_CPP_TRIE_H

#include <array>
#include <memory>
#include <optional>
#include <unordered_set>

// Trie symbol table
template<typename Value>
class Trie {
private:
    constexpr static int R = 256;

    struct Node;
    using NodeUPtr = std::unique_ptr<Node>;
    struct Node {
        std::optional<Value> value;
        std::array<NodeUPtr, R> next;
    };

    NodeUPtr root;

    NodeUPtr put(NodeUPtr x, const std::string& key, const int depth, const Value value) {
        if (!x) x = std::make_unique<Node>();
        if (depth == key.size()) {
            x->value = value;
            return x;
        }
        const char c = key[depth];
        x->next[c] = put(std::move(x->next[c]), key, depth+1, value);
        return x;
    }

    Node* get(Node* x, const std::string& key, const int depth) const {
        if (!x) return x;
        if (depth == key.size()) return x;
        const char c = key[depth];
        return get(x->next[c].get(), key, depth+1);
    }


public:
    void put(const std::string& key, const int value) {
        root = put(std::move(root), key, 0, value);
    }

    [[nodiscard]]
    std::optional<Value> get(const std::string& key) const {
        Node* x = get(root.get(), key, 0);
        if (!x) return {};
        return x->value;
    }

    [[nodiscard]]
    bool contains(const std::string& key) const {
        return get(key).has_value();
    }
};
#endif //STRING_PROCESSING_CPP_TRIE_H
