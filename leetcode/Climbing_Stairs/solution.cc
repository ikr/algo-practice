#include <bits/stdc++.h>

using namespace std;

struct Solution {
    int climbStairs(const int n) const;
};

int Solution::climbStairs(const int n) const {
    if (n == 1)
        return 1;

    if (n == 2)
        return 2;

    int res_1 = 1;
    int res = 2;
    for (int x = 3; x != n; ++x) {
        const int new_res_1 = res;
        res = res + res_1;
        res_1 = new_res_1;
    }

    return res + res_1;
}

int climb_stairs_recur(const int n) {
    switch (n) {
    case 1:
        return 1;

    case 2:
        return 2;

    default:
        return climb_stairs_recur(n - 1) + climb_stairs_recur(n - 2);
    }
}

int main() {
    vector<int> xs{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 18, 44};

    for (const int x : xs) {
        cout << x << " - " << Solution().climbStairs(x) << " | "
             << climb_stairs_recur(x) << endl;
    }

    return 0;
}
