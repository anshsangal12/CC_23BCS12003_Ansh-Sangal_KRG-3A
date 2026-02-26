class Solution {

    static int sumBitDiff(int[] arr) {
        int diff = 0;

        for (int i = 0; i < arr.length; i++) {
            for (int j = i; j < arr.length; j++) {
                int xor = arr[i] ^ arr[j];
                int count = countSetBits(xor);
                diff += 2 * count;
            }
        }

        return diff;
    }

    static int countSetBits(int n) {
        int count = 0;

        while (n != 0) {
            n = n & (n - 1);
            count++;
        }

        return count;
    }
}
