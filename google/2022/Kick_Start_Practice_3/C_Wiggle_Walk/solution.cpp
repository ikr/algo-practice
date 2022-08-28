#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
enum class Dir { L, R };

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const set<T> &xs) {
    os << '{';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << '}';
    return os;
}

ostream &operator<<(ostream &os, const Dir x) {
    os << (x == Dir::L ? 'L' : 'R');
    return os;
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

int simulate_move_get_new_index(set<pii> &xs, const int i, const Dir dir) {
    assert(!xs.empty());
    cerr << "xs:" << xs << " i:" << i << " dir:" << dir << endl;
    const auto it = xs.lower_bound(pii{i, INT_MIN});

    if (dir == Dir::L) {
        assert(it != cbegin(xs));
        const auto jt = prev(it);

        const auto [a, b] = *jt;
        assert(a <= b);
        xs.erase(jt);

        if (a < b) xs.emplace(a, b - 1);
        cerr << "xs:" << xs << " returning " << b << endl;
        return b;
    } else {
        const auto [a, b] = *it;
        assert(a <= b);
        xs.erase(it);

        if (a < b) xs.emplace(a + 1, b);
        cerr << "xs:" << xs << " returning " << a << endl;
        return a;
    }
}

pii simulate_moves_get_destination(const pii dim, const pii src,
                                   const string &commands) {
    const auto [H, W] = dim;
    const auto [ro0, co0] = src;

    vector<set<pii>> horz(H, set{pii{0, W - 1}});
    horz[ro0] = set<pii>{};
    if (0 < co0) horz[ro0].emplace(0, co0 - 1);
    if (co0 < W - 1) horz[ro0].emplace(co0 + 1, W - 1);

    vector<set<pii>> vert(W, set{pii{0, H - 1}});
    if (0 < ro0) vert[co0].emplace(0, ro0 - 1);
    if (ro0 < H - 1) horz[co0].emplace(ro0 + 1, H - 1);

    int ro = ro0, co = co0;
    for (const auto cmd : commands) {
        switch (cmd) {
        case 'N':
            ro = simulate_move_get_new_index(vert[co], ro, Dir::L);
            break;

        case 'S':
            ro = simulate_move_get_new_index(vert[co], ro, Dir::R);
            break;

        case 'W':
            co = simulate_move_get_new_index(horz[ro], co, Dir::L);
            break;

        case 'E':
            co = simulate_move_get_new_index(horz[ro], co, Dir::R);
            break;

        default:
            assert(false && "Unknown command");
        }
    }
    return {ro, co};
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N, H, W;
        cin >> N >> H >> W;

        int ro0, co0;
        cin >> ro0 >> co0;
        --ro0;
        --co0;

        string commands;
        cin >> commands;
        assert(sz(commands) == N);

        const auto [ro, co] =
            simulate_moves_get_destination({H, W}, {ro0, co0}, commands);

        cout << "Case #" << i << ": " << (ro + 1) << ' ' << (co + 1) << '\n';
    }

    return 0;
}
