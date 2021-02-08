#ifndef STRING_PROCESSING_CPP_TRIE_H
#define STRING_PROCESSING_CPP_TRIE_H

#include <array>
#include <memory>
#include <optional>
#include <unordered_set>

// Trie symbol table
template<typename Value, typename CharType = char, int R = 256>
class Trie {
private:
    struct Node;
    using NodeUPtr = std::unique_ptr<Node>;
    struct Node {
        std::optional<Value> value;
        std::array<NodeUPtr, R> next;
    };

    NodeUPtr root;

    NodeUPtr put(NodeUPtr x, const std::basic_string<CharType>& key, const int depth, const Value value) {
        if (!x) x = std::make_unique<Node>();
        if (depth == key.size()) {
            x->value = value;
            return x;
        }
        const CharType c = key[depth];
        x->next[c] = put(std::move(x->next[c]), key, depth+1, value);
        return x;
    }

    Node* get(Node* x, const std::basic_string<CharType>& key, const int depth) const {
        if (!x) return x;
        if (depth == key.size()) return x;
        const CharType c = key[depth];
        return get(x->next[c].get(), key, depth+1);
    }

    void collect(Node* x, const std::basic_string<CharType>& prefix, std::vector<std::basic_string<CharType>>& result) const {
        if (!x) return;
        if (x->value) result.push_back(prefix);
        for (int c=0; c < R; ++c) {
            collect(x->next[c].get(), prefix + static_cast<CharType>(c), result);
        }
    }

    int search(Node* x, const std::basic_string<CharType>& key, const int depth, int length) const {
        if (!x) return length;
        if (x->value) length = depth;
        if (depth == key.size()) return length;
        const CharType c = key[depth];
        return search(x->next[c].get(), key,depth+1, length);
    }
public:
    void put(const std::basic_string<CharType>& key, const int value) {
        root = put(std::move(root), key, 0, value);
    }

    [[nodiscard]]
    std::optional<Value> get(const std::basic_string<CharType>& key) const {
        Node* x = get(root.get(), key, 0);
        if (!x) return {};
        return x->value;
    }

    [[nodiscard]]
    bool contains(const std::basic_string<CharType>& key) const {
        return get(key).has_value();
    }

    [[nodiscard]]
    std::vector<std::basic_string<CharType>> keys() const {
        std::vector<std::basic_string<CharType>> result;
        collect(root.get(), "", result);
        return result;
    }

    [[nodiscard]]
    std::vector<std::basic_string<CharType>> keysWithPrefix(const std::basic_string<CharType>& prefix) const {
        Node* x = get(root.get(), prefix, 0);
        if (!x) return {};
        std::vector<std::basic_string<CharType>> result;
        collect(x, prefix, result);
        return result;
    }

    [[nodiscard]]
    std::basic_string<CharType> longestPrefixOf(const std::basic_string<CharType>& key) const {
        const int length = search(root.get(), key,0, 0);
        return key.substr(0, length);
    }
};
#endif //STRING_PROCESSING_CPP_TRIE_H
