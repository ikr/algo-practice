#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int AZ = 26;

array<int, AZ> gather_freqs(const string &xs) {
    array<int, AZ> fs;
    fs.fill(0);
    for (const auto &c : xs) {
        const auto x = inof(c) - inof('a');
        ++fs[x];
    }
    return fs;
}

template <typename T, size_t N>
constexpr array<T, N> operator-(array<T, N> a, const array<T, N> &b) {
    transform(cbegin(a), cend(a), cbegin(b), begin(a), minus<int>{});
    return a;
}

string sorted(string xs) {
    sort(begin(xs), end(xs));
    return xs;
}

bool solve(string A, string B) {
    if (sz(A) == sz(B)) return sorted(A) == sorted(B);
    if (sz(A) > sz(B)) swap(A, B);

    const auto fa = gather_freqs(A);
    const auto fb = gather_freqs(B);

    const auto df = fb - fa;
    if (any_of(cbegin(df), cend(df), [](const int f) { return f < 0; })) {
        return false;
    }

    const auto odds =
        count_if(cbegin(df), cend(df), [](const int f) { return f % 2; });
    return odds <= 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;

    while (t--) {
        int N, M;
        cin >> N >> M;

        string A, B;
        cin >> A >> B;
        assert(sz(A) == N);
        assert(sz(B) == M);

        cout << (solve(A, B) ? "YES" : "NO") << '\n';
    }
    return 0;
}
