#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    unordered_set<string> dictionary;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        dictionary.insert(s);
    }

    while (m--) {
        string query;
        cin >> query;

        bool found = false;

        for (int i = 0; i < query.length(); i++) {
            char original = query[i];

            for (char c : {'a', 'b', 'c'}) {
                if (c == original) continue;

                query[i] = c;

                if (dictionary.find(query) != dictionary.end()) {
                    found = true;
                    break;
                }
            }

            query[i] = original;  // restore

            if (found) break;
        }

        cout << (found ? "YES\n" : "NO\n");
    }

    return 0;
}
