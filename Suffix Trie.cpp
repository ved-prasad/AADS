
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <numeric>
using namespace std;

class TrieNode {
public:
    unordered_map<char, unique_ptr<TrieNode>> children;
    vector<int> indexes;
};

class SuffixTrie {
private:
    unique_ptr<TrieNode> root;

    void insertSuffix(const string& suffix, int startIndex) {
        TrieNode* curr = root.get();

        for (char c : suffix) {
            if (curr->children.find(c) == curr->children.end()) {
                curr->children[c] = make_unique<TrieNode>();
            }

            curr = curr->children[c].get();

            curr->indexes.push_back(startIndex);
        }
    }

public:
    SuffixTrie(const string& text) {
        root = make_unique<TrieNode>();

        for (int i = 0; i < (int)text.length(); i++) {
            insertSuffix(text.substr(i), i);
        }
    }

    vector<int> search(const string& pattern) {
        // Empty pattern matches every boundary
        if (pattern.empty()) {
            vector<int> result(pattern.size() + 1);
            iota(result.begin(), result.end(), 0);
            return result;
        }

        TrieNode* curr = root.get();

        for (char c : pattern) {
            auto it = curr->children.find(c);

            if (it == curr->children.end()) {
                return {};
            }

            curr = it->second.get();
        }

        return curr->indexes;
    }
};

int main() {
    string text = "banana";

    SuffixTrie trie(text);

    string pattern = "ana";

    vector<int> matches = trie.search(pattern);

    cout << "Text: " << text << endl;
    cout << "Pattern: " << pattern << endl;

    if (matches.empty()) {
        cout << "Pattern not found." << endl;
    }
    else {
        cout << "Pattern found at indices: ";

        for (int idx : matches) {
            cout << idx << " ";
        }

        cout << endl;
    }

    return 0;
}
