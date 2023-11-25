#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, L;
    cin >> N >> L;

    vector<int> xs(N);
    for (auto &x : xs) cin >> x;

    cout << count_if(cbegin(xs), cend(xs), [&](const auto x) { return x >= L; })
         << '\n';
    return 0;
}
