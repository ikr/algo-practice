#include <bits/stdc++.h>

using namespace std;

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    for (const auto x : xs) {
        os << x << ' ';
    }

    return os;
}

int main() {
    int n;
    cin >> n;
    vector<int> ays(n);
    int parlament_size{0};

    for (auto &a : ays) {
        cin >> a;
        parlament_size += a;
    }

    int coalition_size = ays[0];
    vector<int> ans{1};
    size_t i = 1;

    while (coalition_size <= parlament_size / 2 && i != ays.size()) {
        if (ays[i] * 2 <= ays[0]) {
            coalition_size += ays[i];
            ans.push_back(i + 1);
        }

        ++i;
    }

    if (coalition_size > parlament_size / 2) {
        cout << ans.size() << '\n';
        cout << ans << '\n';
    } else {
        cout << 0 << '\n';
    }
}
