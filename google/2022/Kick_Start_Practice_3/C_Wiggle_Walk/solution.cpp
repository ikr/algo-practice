#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
enum class Dir { L, R };

int simulate_move_get_new_index(set<pii> &xs, const int i, const Dir dir) {
    assert(!xs.empty());
    const auto it = xs.lower_bound(pii{i, INT_MIN});

    if (dir == Dir::L) {
        assert(it != cbegin(xs));
        const auto jt = prev(it);

        const auto [a, b] = *jt;
        assert(a <= b);
        xs.erase(jt);

        if (a < b) xs.emplace(a, b - 1);
        return b;
    } else {
        const auto [a, b] = *it;
        assert(a <= b);
        xs.erase(it);

        if (a < b) xs.emplace(a + 1, b);
        return a;
    }
}

void erase_at(set<pii> &xs, const int i) {
    if (xs.empty()) return;

    const auto it = [&]() -> set<pii>::const_iterator {
        const auto jt = xs.lower_bound(pii{i, INT_MIN});
        if (jt == cend(xs)) return prev(jt);
        if (i == jt->first) return jt;
        return jt == cbegin(xs) ? jt : prev(jt);
    }();

    const auto [a, b] = *it;
    if (!(a <= i && i <= b)) return;
    xs.erase(it);

    if (a == b) {
        assert(i == a);
        return;
    }

    if (i == a) {
        xs.emplace(a + 1, b);
        return;
    }

    if (i == b) {
        xs.emplace(a, b - 1);
        return;
    }

    xs.emplace(a, i - 1);
    xs.emplace(i + 1, b);
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
    vert[co0] = set<pii>{};
    if (0 < ro0) vert[co0].emplace(0, ro0 - 1);
    if (ro0 < H - 1) vert[co0].emplace(ro0 + 1, H - 1);

    int ro = ro0, co = co0;
    for (const auto cmd : commands) {
        switch (cmd) {
        case 'N':
            ro = simulate_move_get_new_index(vert[co], ro, Dir::L);
            erase_at(horz[ro], co);
            break;

        case 'S':
            ro = simulate_move_get_new_index(vert[co], ro, Dir::R);
            erase_at(horz[ro], co);
            break;

        case 'W':
            co = simulate_move_get_new_index(horz[ro], co, Dir::L);
            erase_at(vert[co], ro);
            break;

        case 'E':
            co = simulate_move_get_new_index(horz[ro], co, Dir::R);
            erase_at(vert[co], ro);
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

        const auto [ro, co] =
            simulate_moves_get_destination({H, W}, {ro0, co0}, commands);

        cout << "Case #" << i << ": " << (ro + 1) << ' ' << (co + 1) << '\n';
    }

    return 0;
}
