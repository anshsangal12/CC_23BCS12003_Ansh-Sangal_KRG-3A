#include <bits/stdc++.h>
using namespace std;

vector<int> arr;
vector<int> tree;

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = arr[start];
    } else {
        int mid = (start + end) / 2;

        build(2*node, start, mid);
        build(2*node+1, mid+1, end);

        tree[node] = tree[2*node] + tree[2*node+1];
    }
}


int getSum(int node, int start, int end, int L, int R) {
    if (R < start || end < L)
        return 0;

    if (L <= start && end <= R)
        return tree[node];

    int mid = (start + end) / 2;

    return getSum(2*node, start, mid, L, R) +
           getSum(2*node+1, mid+1, end, L, R);
}


void updateValue(int node, int start, int end, int idx, int val) {
    if (start == end) {
        arr[idx] = val;
        tree[node] = val;
    } else {
        int mid = (start + end) / 2;

        if (idx <= mid)
            updateValue(2*node, start, mid, idx, val);
        else
            updateValue(2*node+1, mid+1, end, idx, val);

        tree[node] = tree[2*node] + tree[2*node+1];
    }
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    arr.resize(n);
    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    tree.resize(4 * n);

    build(1, 0, n-1);

    int choice;
    while (true) {
        cout << "\n1. Range Sum Query\n2. Update Value\n3. Exit\n";
        cin >> choice;

        if (choice == 1) {
            int l, r;
            cout << "Enter L and R: ";
            cin >> l >> r;
            cout << "Sum = " << getSum(1, 0, n-1, l, r) << endl;
        }
        else if (choice == 2) {
            int idx, val;
            cout << "Enter index and new value: ";
            cin >> idx >> val;
            updateValue(1, 0, n-1, idx, val);
        }
        else {
            break;
        }
    }

    return 0;
}
