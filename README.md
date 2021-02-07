# String processing - Tries, Ternary Search Tries, etc. in C++

## `include/`
- [`Trie`](https://en.wikipedia.org/wiki/Trie) symbol table
- [`TernarySearchTrie`](https://en.wikipedia.org/wiki/Ternary_search_tree) symbol table

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