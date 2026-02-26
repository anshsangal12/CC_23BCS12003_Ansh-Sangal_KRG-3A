// A positive integer is magical if it is divisible by either a or b.
// Given the three integers n, a, and b, return the nth magical number. Since the answer may be very large, return it modulo 109 + 7.

// Example 1:
// Input: n = 1, a = 2, b = 3
// Output: 2

// Example 2:
// Input: n = 4, a = 2, b = 3
// Output: 6



#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int nthMagicalNumber(int n, int a, int b) {
        long long lcm = (long long)a * b / __gcd(a, b);
        long long low = min(a, b), high = (long long)low * n;
        while (low < high) {
            long long mid = low + (high - low) / 2;
            if (mid / a + mid / b - mid / lcm < n) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return low % 1000000007;
    }
};  
