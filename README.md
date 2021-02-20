# String processing - Tries, Ternary Search Tries, etc. in C++

## `include/`
- [`Trie`](https://en.wikipedia.org/wiki/Trie) symbol table
- [`TernarySearchTrie`](https://en.wikipedia.org/wiki/Ternary_search_tree) symbol table
- Implementation of [Knuth-Morris-Pratt](https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm) algorithm for efficient pattern matching 
- Implementation of [Boyer-Moore](https://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string-search_algorithm) algorithm for efficient pattern matching 

## Compilation and execution
- Download submodules (for unit tests): `git submodule update --init --recursive`
- Compile with `cmake`:
  ```bash
  mkdir build
  cd build/
  cmake ..
  make
  ```
- Go to top-level folder again: `cd ..`
- Run all tests: `find build/ -name "*_gtest" -exec {} \;`

## References
- Introduction to Algorithms by Cormen et al.
- Algorithms, [Part II](https://www.coursera.org/learn/algorithms-part2/home/welcome) by Princeton University (Robert Sedgewick, Kevin Wayne)