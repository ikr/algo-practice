#include <cassert>
#include <climits>
#include <iostream>
#include <map>
using namespace std;

template <typename K, typename V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << '{';
    for (auto i = m.cbegin(); i != m.cend(); ++i) {
        if (i != m.cbegin()) os << ' ';
        os << '(' << i->first << ' ' << i->second << ')';
    }
    os << '}';
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

bool can_zig_zag_impl(int l, map<int, int> fs) {
    const auto dec_at = [&](const int k, const int d) {
        assert(fs[k] >= d);
        fs[k] -= d;
        if (fs[k] == 0) fs.erase(k);
    };

    while (!fs.empty()) {
        // cerr << fs << " l:" << l << endl;
        if (sz(fs) == 1) {
            const auto rem = prev(cend(fs))->first;
            if (rem >= l || fs[rem] != 1) return false;
            break;
        }

        const int a = prev(cend(fs), 2)->first;
        const int b = prev(cend(fs))->first;
        if (a >= l) return false;
        const auto d = min(fs[a], fs[b]);
        dec_at(a, d);
        dec_at(b, d);
        l = b;
    }

    return true;
}

bool can_zig_zag(map<int, int> fs) {
    const auto l = crbegin(fs)->first;
    --fs[l];
    if (fs[l] == 0) fs.erase(l);
    return can_zig_zag_impl(l, fs);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    map<int, int> fs;

    for (int i = 1; i <= N; ++i) {
        int f;
        cin >> f;

        fs[i] = f;
    }

    cout << (can_zig_zag(move(fs)) ? "YES" : "NO") << '\n';
    return 0;
}
