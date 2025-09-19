#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

int lex_min_rotation(const std::string& s, const std::string& alphabet = "") {
    std::string doubled = s + s;  // Join the string with itself
    int n = s.size();

    // Map each character to its rank in the alphabet
    std::unordered_map<char, int> rank;
    if (alphabet.empty()) {
        std::string sorted_alpha = s;
        std::sort(sorted_alpha.begin(), sorted_alpha.end());
        sorted_alpha.erase(std::unique(sorted_alpha.begin(), sorted_alpha.end()), sorted_alpha.end());
        for (int i = 0; i < (int)sorted_alpha.size(); ++i) {
            rank[sorted_alpha[i]] = i;
        }
    } else {
        for (int i = 0; i < (int)alphabet.size(); ++i) {
            rank[alphabet[i]] = i;
        }
    }

    std::vector<int> f(2 * n, -1);
    int k = 0;  // Start index of minimal rotation

    for (int j = 1; j < 2 * n; ++j) {
        int i = f[j - k - 1];
        while (i != -1 && rank[doubled[j]] != rank[doubled[k + i + 1]]) {
            if (rank[doubled[j]] < rank[doubled[k + i + 1]]) {
                k = j - i - 1;
            }
            i = f[i];
        }
        if (i == -1 && rank[doubled[j]] != rank[doubled[k]]) {
            if (rank[doubled[j]] < rank[doubled[k]]) {
                k = j;
            }
            f[j - k] = -1;
        } else {
            f[j - k] = i + 1;
        }
    }
    return k;
}

int main() {
    std::string dna = "GATTACA";
    std::string alphabet = "ACGT";  // DNA alphabet order
    int index = lex_min_rotation(dna, alphabet);
    std::string minimal_rotation = dna.substr(index) + dna.substr(0, index);

    std::cout << "Lexicographically minimal rotation: " << minimal_rotation << std::endl;
    std::cout << "Rotation starting index: " << index << std::endl;

    return 0;
}
