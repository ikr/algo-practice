#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int abc_occ_num(const string &xs) {
    int ans{};

    string::size_type i = 0;
    while ((i = xs.find("abc", i)) != xs.npos) {
        ++ans;
        i += 2;
    }

    return ans;
}

bool is_in_abc(const string &xs, const int i) {
    if (xs[i] == 'a') {
        if (i + 1 >= sz(xs) || xs[i + 1] != 'b') return false;
        if (i + 2 >= sz(xs) || xs[i + 2] != 'c') return false;
        return true;
    }

    if (xs[i] == 'b') {
        if (i - 1 < 0 || xs[i - 1] != 'a') return false;
        if (i + 1 >= sz(xs) || xs[i + 1] != 'c') return false;
        return true;
    }

    assert(xs[i] == 'c');
    if (i - 2 < 0 || xs[i - 2] != 'a') return false;
    if (i - 1 < 0 || xs[i - 1] != 'b') return false;
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, q;
    cin >> n >> q;

    string xs(n, ' ');
    cin >> xs;

    int curr = abc_occ_num(xs);

    for (int t = 0; t < q; ++t) {
        int i;
        cin >> i;
        --i;

        char x;
        cin >> x;

        if (xs[i] == x) {
            cout << curr << '\n';
            continue;
        }

        if (is_in_abc(xs, i)) {
            --curr;
            xs[i] = x;

            if (is_in_abc(xs, i)) ++curr;

            cout << curr << '\n';
            continue;
        }

        xs[i] = x;
        if (is_in_abc(xs, i)) ++curr;
        cout << curr << '\n';
    }

    return 0;
}
