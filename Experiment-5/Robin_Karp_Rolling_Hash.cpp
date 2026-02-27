#include<bits/stdc++.h>
using namespace std;


class solution {
public:
    const int p = 31;
    const int mod = 1e9 + 7;

    vector<int> find(string str, string pattern) {
        vector<int> result;
        int n = str.size();
        int m = pattern.size();

        if (m > n) return {-1};

        long long patternHash = 0;
        long long windowHash = 0;
        long long power = 1;

        // Compute p^(m-1)
        for (int i = 0; i < m - 1; i++)
            power = (power * p) % mod;

        // Initial hash
        for (int i = 0; i < m; i++) {
            patternHash = (patternHash * p + (pattern[i] - 'a' + 1)) % mod;
            windowHash = (windowHash * p + (str[i] - 'a' + 1)) % mod;
        }

        for (int i = 0; i <= n - m; i++) {
            if (windowHash == patternHash) {
                result.push_back(i);
            }

            if (i < n - m) {
                windowHash = (windowHash - (str[i] - 'a' + 1) * power % mod + mod) % mod;
                windowHash = (windowHash * p + (str[i + m] - 'a' + 1)) % mod;
            }
        }

        if (result.empty())
            result.push_back(-1);

        return result;
    }
};

int main() {
    string str = "abcde";
    string pattern = "cde";

    vector<int> result = solution().find(str, pattern);
    for(int index : result) {
        cout << index << endl;
    }
}
