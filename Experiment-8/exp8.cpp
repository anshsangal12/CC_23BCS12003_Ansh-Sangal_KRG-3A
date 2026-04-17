#include <bits/stdc++.h>
using namespace std;

int maxSumAfterPartitioning(vector<int>& arr, int k) {
    int n = arr.size();
    vector<int> dp(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        int mx = 0;
        for (int j = 1; j <= k && i - j >= 0; j++) {
            mx = max(mx, arr[i - j]);
            dp[i] = max(dp[i], dp[i - j] + mx * j);
        }
    }
    return dp[n];
}

int main() {
    vector<int> arr1 = {1,15,7,9,2,5,10};
    int k1 = 3;
    cout << maxSumAfterPartitioning(arr1, k1) << endl;

    vector<int> arr2 = {1,4,1,5,7,3,6,1,9,9,3};
    int k2 = 4;
    cout << maxSumAfterPartitioning(arr2, k2) << endl;

    vector<int> arr3 = {1};
    int k3 = 1;
    cout << maxSumAfterPartitioning(arr3, k3) << endl;

    return 0;
}
