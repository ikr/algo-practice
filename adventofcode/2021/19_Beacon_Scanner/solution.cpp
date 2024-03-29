#include <bits/stdc++.h>
using namespace std;

static constexpr int MATCH_THERSHOLD = 12;

using Tri = array<int, 3>;
using Duo = pair<int, int>;
enum class ZDir { PX, NX, PY, NY, PZ, NZ };
enum class Rot2d { D0, D90, D180, D270 };

struct Rot3d final {
    ZDir z;
    Rot2d xy;
};

struct Transf final {
    Tri o_src;
    Tri o_trg;
    Rot3d r;
};

using Graph = vector<vector<pair<int, Transf>>>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

constexpr tuple<int, int, int> as_tuple(const Tri &t) {
    return {t[0], t[1], t[2]};
}

Tri negate_t(Tri t) {
    transform(cbegin(t), cend(t), begin(t), [](const int a) { return -a; });
    return t;
}

Tri operator+(Tri t0, const Tri &t1) {
    transform(cbegin(t0), cend(t0), cbegin(t1), begin(t0),
              [](const int a, const int b) { return a + b; });
    return t0;
}

vector<Rot3d> all_possible_rotations() {
    vector<Rot3d> result;

    for (int i = inof(ZDir::PX); i <= inof(ZDir::NZ); ++i) {
        for (int j = inof(Rot2d::D0); j <= inof(Rot2d::D270); ++j) {
            result.push_back(
                Rot3d{static_cast<ZDir>(i), static_cast<Rot2d>(j)});
        }
    }

    assert(sz(result) == 24);
    return result;
}

Duo apply_rotation(const Rot2d &r, const Duo xy) {
    const auto [x, y] = xy;

    switch (r) {
    case Rot2d::D0:
        return xy;
    case Rot2d::D90:
        return {-y, x};
    case Rot2d::D180:
        return {-x, -y};
    case Rot2d::D270:
        return {y, -x};
    default:
        assert(false && "Impossible rotation");
        return {};
    }
}

Tri apply_rotation(const Rot3d t, const Tri &p) {
    const auto [x, y, z] = as_tuple(p);

    switch (t.z) {
    case ZDir::PX: //  z → x, x → y, y → z
    {
        const int x_ = z;
        const auto [y_, z_] = apply_rotation(t.xy, {x, y});
        return {x_, y_, z_};
    }
    case ZDir::NX: // z → -x, x → z, y → y
    {
        const int x_ = -z;
        const auto [z_, y_] = apply_rotation(t.xy, {x, y});
        return {x_, y_, z_};
    }
    case ZDir::PY: //  z → y, x → z, y → x
    {
        const int y_ = z;
        const auto [z_, x_] = apply_rotation(t.xy, {x, y});
        return {x_, y_, z_};
    }
    case ZDir::NY: // z → -y, x → x, y → z
    {
        const int y_ = -z;
        const auto [x_, z_] = apply_rotation(t.xy, {x, y});
        return {x_, y_, z_};
    }
    case ZDir::PZ: //  z → z, x → x, y → y
    {
        const int z_ = z;
        const auto [x_, y_] = apply_rotation(t.xy, {x, y});
        return {x_, y_, z_};
    }
    case ZDir::NZ: // z → -z, x → y, y → x
    {
        const int z_ = -z;
        const auto [y_, x_] = apply_rotation(t.xy, {x, y});
        return {x_, y_, z_};
    }
    default:
        assert(false && "Impossible orientation of z-axis");
        return {};
    }
}

static const auto RS = all_possible_rotations();

int intersection_size(vector<Tri> a, vector<Tri> b) {
    sort(begin(a), end(a));
    sort(begin(b), end(b));

    vector<Tri> x;
    set_intersection(cbegin(a), cend(a), cbegin(b), cend(b), back_inserter(x));
    return sz(x);
}

vector<Tri> center(const Tri &o, vector<Tri> a) {
    const auto o_ = negate_t(o);
    transform(cbegin(a), cend(a), begin(a),
              [&o_](const Tri &x) { return x + o_; });
    return a;
}

optional<Transf> overlap(const vector<Tri> &src, const vector<Tri> &trg) {
    for (const auto &o_src : src) {
        for (const auto &o_trg : trg) {
            const auto trg_ = center(o_trg, trg);
            const auto src_ = center(o_src, src);

            for (const auto &r : RS) {
                auto src__ = src_;

                transform(cbegin(src__), cend(src__), begin(src__),
                          [&r](const Tri &a) { return apply_rotation(r, a); });

                if (intersection_size(trg_, src__) >= MATCH_THERSHOLD) {
                    return Transf{o_src, o_trg, r};
                }
            }
        }
    }

    return nullopt;
}

Graph build_graph(const vector<vector<Tri>> &data) {
    const auto n = sz(data);
    Graph g(n, vector<pair<int, Transf>>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;

            const auto tr = overlap(data[i], data[j]);
            if (!tr) continue;
            g[i].emplace_back(j, *tr);
            cerr << i << " → " << j << endl;
        }
    }

    return g;
}

bool is_scanner_sep_line(const string &line) {
    return line.find("--- scanner ") == 0;
}

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

map<Duo, Transf> index_transf(const Graph &g) {
    map<Duo, Transf> result;

    for (int u = 0; u < sz(g); ++u) {
        for (const auto &[v, tr] : g[u]) {
            result[{u, v}] = tr;
        }
    }

    return result;
}

vector<Tri> join_into_common_space(const Graph &g,
                                   const vector<vector<Tri>> &spaces) {
    const auto idx = index_transf(g);
    vector<bool> visited(sz(g), false);
    function<vector<Tri>(int)> dfs;

    dfs = [&](const int u) -> vector<Tri> {
        visited[u] = true;
        vector<Tri> result(cbegin(spaces[u]), cend(spaces[u]));

        for (const auto &[v, _] : g[u]) {
            if (visited[v]) continue;
            auto sub = dfs(v);
            const auto tr = idx.at({v, u});

            transform(cbegin(result), cend(result), begin(result),
                      [&](const Tri &t) { return t + negate_t(tr.o_trg); });

            transform(cbegin(sub), cend(sub), begin(sub), [&](const Tri &t) {
                return apply_rotation(tr.r, t + negate_t(tr.o_src));
            });

            result.insert(cend(result), cbegin(sub), cend(sub));

            transform(cbegin(result), cend(result), begin(result),
                      [&](const Tri &t) { return t + tr.o_trg; });

            sort(begin(result), end(result));
            result.erase(unique(begin(result), end(result)), end(result));
        }

        return result;
    };

    return dfs(0);
}

int manhattan(const Tri &a, const Tri &b) {
    return abs(a[0] - b[0]) + abs(a[1] - b[1]) + abs(a[2] - b[2]);
}

int main() {
    vector<vector<Tri>> data;
    vector<Tri> curr;

    for (string line; getline(cin, line);) {
        if (line.empty()) continue;
        if (is_scanner_sep_line(line)) {
            if (curr.empty()) continue;
            data.push_back(curr);
            curr.clear();
            continue;
        }

        const auto xs = split(",", line);
        Tri t;
        transform(cbegin(xs), cend(xs), begin(t),
                  [](const auto &x) { return stoi(x); });
        curr.push_back(t);
    }

    assert(!curr.empty());
    data.push_back(curr);

    const auto g = build_graph(data);
    cout << "Total beacons: " << sz(join_into_common_space(g, data)) << '\n';

    const vector<vector<Tri>> zs(sz(g), vector<Tri>{{0, 0, 0}});
    const auto ts = join_into_common_space(g, zs);

    int ans{};

    for (int i = 0; i < sz(ts) - 1; ++i) {
        for (int j = i + 1; j < sz(ts); ++j) {
            ans = max(ans, manhattan(ts[i], ts[j]));
        }
    }

    cout << "Manhattan diameter of scanners: " << ans << '\n';
    return 0;
}
