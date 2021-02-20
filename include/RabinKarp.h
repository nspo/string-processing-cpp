#ifndef STRING_PROCESSING_CPP_RABINKARP_H
#define STRING_PROCESSING_CPP_RABINKARP_H

#include <cstdint>
#include <vector>
#include <optional>

namespace rk {

    namespace detail {
        /// @brief hash of first len characters in key
        [[nodiscard]]
        uint64_t hash(std::string_view key, const size_t len, const uint64_t radix, const uint64_t q) {
            uint64_t result = 0;
            for (size_t j=0; j<len; ++j) {
                result = (result * radix + key[j]) % q;
            }
            return result;
        }
    }

    /// @param return_after_num_matches Only match up to this number of matches, then return result. Must not be 0.
    [[nodiscard]]
    std::vector<size_t> find_probabilistic_all_matches(std::string_view pat, std::string_view text,
                                                       size_t return_after_num_matches = std::numeric_limits<size_t>::max()) {
        if (pat.size() > text.size()) return {};

        const uint64_t radix = 256;
        const uint64_t q = 1152921504606846869; ///< 2^60-107, a long prime
        uint64_t rm = 1; // radix^(pat.size()-1) % q, to be precomputed
        for (size_t i=1; i < pat.size(); ++i) {
            rm = (radix * rm) % q;
        }

        // create helper for hash calls
        auto hash = [](std::string_view key, const size_t len) { return detail::hash(key, len, radix, q); };

        uint64_t pat_hash = hash(pat, pat.size());
        uint64_t text_hash = hash(text, pat.size());

        std::vector<size_t> result;
        if (pat_hash == text_hash) {
            result.push_back(0);
        }
        for (size_t i=pat.size(); i < text.size(); ++i) {
            if (result.size() >= return_after_num_matches) return result;

            text_hash = (text_hash + q - rm*text[i-pat.size()] % q) % q;
            text_hash = (text_hash*radix + text[i]) % q;
            if (text_hash == pat_hash) {
                result.push_back(i+1-pat.size());
            }
        }
        return result;
    }

    [[nodiscard]]
    std::optional<size_t> find_probabilistic_single_match(std::string_view pat, std::string_view text) {
        auto result = find_probabilistic_all_matches(pat, text, 1);

        if (result.empty()) return {};
        else return {result[0]};
    }


} // rk

#endif //STRING_PROCESSING_CPP_RABINKARP_H
