#include <bits/stdc++.h>
using namespace std;

vector<int> digits_reversed(int x) {
    vector<int> ans;
    while (x) {
        ans.push_back(x % 10);
        x /= 10;
    }
    return ans;
}

int sum_of_digits(const int x) {
    const auto ds = digits_reversed(x);
    return accumulate(cbegin(ds), cend(ds), 0);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int a, b;
    cin >> a >> b;

    int ans = max(sum_of_digits(a), sum_of_digits(b));
    cout << ans << '\n';
    return 0;
}
