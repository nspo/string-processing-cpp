#ifndef STRING_PROCESSING_CPP_KNUTHMORRISPRATT_H
#define STRING_PROCESSING_CPP_KNUTHMORRISPRATT_H

#include <string_view>
#include <vector>

namespace kmp {

    std::vector<size_t> create_kmp_array(std::string_view sv) {
        std::vector<size_t> arr(sv.size(), 0);
        for (size_t i = 1; i < sv.size(); ++i) {
            size_t d = arr[i - 1];
            while (d > 0 && sv[d] != sv[i]) {
                d = arr[d - 1];
            }
            if (sv[d] == sv[i]) {
                arr[i] = d + 1;
            } else {
                arr[i] = 0;
            }
        }
        return arr;
    }

    /// @return index of first occurrence of pattern in text, or text size if not found
    size_t find_single_match(std::string_view pattern, std::string_view text) {
        const auto arr = create_kmp_array(pattern);
        size_t d = 0;
        for (size_t i = 0; i < text.size(); ++i) {
            while (d > 0 && pattern[d] != text[i]) {
                d = arr[d - 1];
            }
            if (pattern[d] == text[i]) {
                d += 1;
            }
            if (d == pattern.size()) {
                // match
                return i + 1 - d;
            }
        }
        return text.size();
    }

    /// @return indices of all matches of pattern in text
    std::vector<size_t> find_all_matches(std::string_view pattern, std::string_view text) {
        const auto arr = create_kmp_array(pattern);
        std::vector<size_t> matches;
        size_t d = 0;
        for (size_t i = 0; i < text.size(); ++i) {
            while (d > 0 && pattern[d] != text[i]) {
                d = arr[d - 1];
            }
            if (pattern[d] == text[i]) {
                d += 1;
            }
            if (d == pattern.size()) {
                // match
                matches.push_back(i + 1 - d);
                d = arr[d - 1];
            }
        }
        return matches;
    }

}

#endif //STRING_PROCESSING_CPP_KNUTHMORRISPRATT_H
