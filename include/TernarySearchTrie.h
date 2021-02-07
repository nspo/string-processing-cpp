#ifndef STRING_PROCESSING_CPP_TERNARYSEARCHTRIE_H
#define STRING_PROCESSING_CPP_TERNARYSEARCHTRIE_H

#include <optional>
#include <memory>

template<typename Value>
class TernarySearchTrie {
private:
    struct Node;
    using NodeUPtr = std::unique_ptr<Node>;
    struct Node {
        std::optional<Value> value;
        char c = '\0';
        NodeUPtr left, mid, right;
    };

    NodeUPtr root;

    NodeUPtr put(NodeUPtr x, const std::string& key, const int depth, const Value value) {
        const char c = key[depth];
        if (!x) {
            x = std::make_unique<Node>();
            x->c = c;
        }
        if (c < x->c) {
            x->left = put(std::move(x->left), key, depth, value);
        } else if (c > x->c) {
            x->right = put(std::move(x->right), key, depth, value);
        } else if (depth < key.size()-1) {
            x->mid = put(std::move(x->mid), key, depth+1, value);
        } else {
            x->value = value;
        }
        return x;
    }

    Node* get(Node* x, const std::string& key, const int depth) const {
        if (!x) return x;
        const char c = key[depth];
        if (c < x->c) {
            return get(x->left.get(), key, depth);
        } else if (c > x->c) {
            return get(x->right.get(), key, depth);
        } else if (depth < key.size()-1) {
            return get(x->mid.get(), key, depth+1);
        } else {
            return x;
        }
    }
public:
    void put(const std::string& key, const Value value) {
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

#endif //STRING_PROCESSING_CPP_TERNARYSEARCHTRIE_H
