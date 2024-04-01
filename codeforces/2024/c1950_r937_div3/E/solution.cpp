#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

unordered_map<char, int> frequencies(const string &xs) {
    unordered_map<char, int> result;
    for (const char x : xs) ++result[x];
    return result;
}

bool confirm_m_pattern(const string &xs, const int m) {
    const auto n = sz(xs);
    assert(n % m == 0);
    for (int i0 = m; i0 < n; i0 += m) {
        int diffs{};

        for (int i = 0; i < m; ++i) {
            diffs += xs[i] != xs[i0 + i];
        }

        if (diffs != 1) return false;
    }
    return true;
}

vector<int> divisors_ascending(const int n) {
    set<int> result;
    for (int i = 2; llof(i) * i <= llof(n); ++i) {
        if (n % i) continue;
        result.insert(i);
        result.insert(n / i);
    }
    return vector(cbegin(result), cend(result));
}

int shortest_pattern_length(string xs) {
    const auto n = sz(xs);
    if (n < 3) return 1;

    {
        const auto fq = frequencies(xs);
        if (sz(fq) == 1 ||
            (sz(fq) == 2 && any_of(cbegin(fq), cend(fq), [](const auto kv) {
                 return kv.second == 1;
             }))) {
            return 1;
        }
    }

    const auto try_matching = [&]() -> int {
        for (const auto m : divisors_ascending(n)) {
            if (confirm_m_pattern(xs, m)) return m;
        }
        return n;
    };

    const auto o1 = try_matching();
    reverse(begin(xs), end(xs));
    const auto o2 = try_matching();
    return min(o1, o2);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        string xs;
        cin >> xs;

        cout << shortest_pattern_length(std::move(xs)) << '\n';
    }

    return 0;
}
