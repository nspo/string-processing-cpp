set(BINARY string_processing_gtest)

add_executable(${BINARY}
                test_trie.cpp
                test_tst.cpp
                test_kmp.cpp
                test_bm.cpp
                test_rk.cpp
                test_nfa.cpp
)

add_executable(grep grep.cpp)

add_test(NAME ${BINARY} COMMAND ${BINARY})

target_link_libraries(${BINARY} PUBLIC gtest gtest_main pthread)
