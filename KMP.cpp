#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> computeLPSArray(const string& pattern) {
    int m = pattern.length();

    vector<int> lps(m, 0);
    int len = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }

    return lps;
}

void KMPSearch(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();

    if (m == 0) {
        cout << "Pattern is empty." << endl;
        return;
    }

    vector<int> lps = computeLPSArray(pattern);

    int i = 0;
    int j = 0;
    bool found = false;

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            cout << "Pattern found at index " << (i - j) << endl;
            found = true;
            j = lps[j - 1];
        }
        else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                i++;
            }
        }
    }

    if (!found) {
        cout << "Pattern not found in the text." << endl;
    }
}

int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";

    cout << "Text: " << text << endl;
    cout << "Pattern: " << pattern << "\n\n";

    KMPSearch(text, pattern);

    return 0;
}