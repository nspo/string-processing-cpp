#ifndef STRING_PROCESSING_CPP_BOYERMOORE_H
#define STRING_PROCESSING_CPP_BOYERMOORE_H

#include <string_view>
#include <vector>
#include <unordered_map>

namespace bm {

    /// @brief Determines rightmost occurrence of each character in the input
    std::unordered_map<char,int> create_bm_table(std::string_view sv) {
        std::unordered_map<char,int> right;
        for(size_t j=0; j<sv.size(); ++j) {
            right[sv[j]] = static_cast<int>(j);
        }
        return right;
    }

    /// @return index of first occurrence of pattern in text, or text size if not found
    template<typename CharType = char>
    size_t find_single_match(std::string_view pattern, std::string_view text) {
        auto right = create_bm_table(pattern);
        int skip = 0;
        for(int i=0; i <= static_cast<int>(text.size())-static_cast<int>(pattern.size()); i += skip) {
            skip = 0;
            // walk through pattern from right to left
            for (int j = static_cast<int>(pattern.size())-1; j >= 0; --j) {
                if (pattern[j] != text[i+j]) {
                    // char does not match
                    int rightmost = -1;
                    if (auto it=right.find(text[i+j]); it != right.end()) {
                        // current text char exists in pattern
                        rightmost = it->second;
                    }
                    skip = std::max(1, j-rightmost);
                    break;
                }
            }
            if (skip == 0) return static_cast<size_t>(i);
        }
        return text.size();
    }

    /// @return indices of all matches of pattern in text
    std::vector<size_t> find_all_matches(std::string_view pattern, std::string_view text) {
        std::vector<size_t> result;
        auto right = create_bm_table(pattern);
        int skip = 0;
        for(int i=0; i <= static_cast<int>(text.size())-static_cast<int>(pattern.size()); i += skip) {
            skip = 0;
            // walk through pattern from right to left
            for (int j = static_cast<int>(pattern.size())-1; j >= 0; --j) {
                if (pattern[j] != text[i+j]) {
                    // char does not match
                    int rightmost = -1;
                    if (auto it=right.find(text[i+j]); it != right.end()) {
                        // current text char exists in pattern
                        rightmost = it->second;
                    }
                    skip = std::max(1, j-rightmost);
                    break;
                }
            }
            if (skip == 0) {
                result.push_back(i);
                skip = 1;
            }
        }
        return result;
    }
}

#endif //STRING_PROCESSING_CPP_BOYERMOORE_H
