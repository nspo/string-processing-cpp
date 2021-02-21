#include <RegexNFA.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // simple grep implementation for standard input matching
    if (argc != 2) {
        std::cerr << "Usage: some_command | "<<argv[0]<<" REGEX\n";
        std::cerr << "The following metasymbols are allowed: ( ) * .\n";
        return 1;
    }
    std::string re = std::string("(.*") + argv[1] + ".*)";
    auto nfa = NFA(re);
    while (std::cin) {
        std::string line;
        std::cin >> line;
        if (nfa.recognizes(line)) {
            std::cout << line << "\n";
        }
    }
}