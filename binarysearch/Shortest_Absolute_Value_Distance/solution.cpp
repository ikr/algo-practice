using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
template <typename T> constexpr int inof(const T x) { return static_cast<int>(x); }
template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }
constexpr int INF = 1e9;

using Coord = complex<int>;
constexpr int row(const Coord coord) { return coord.real(); }
constexpr int col(const Coord coord) { return coord.imag(); }

struct q_less final {
    bool operator()(const pair<int, Coord> &a,
                    const pair<int, Coord> &b) const {
        return pair{a.first, pair{row(a.second), col(a.second)}} <
               pair{b.first, pair{row(b.second), col(b.second)}};
    }
};

using Queue =
    priority_queue<pair<int, Coord>, vector<pair<int, Coord>>, q_less>;

// Dijkstra's algorithm
int solve(vvi &xss) {
    const int h = sz(xss);
    const int w = sz(xss[0]);

    vvi cost(h, vi(w, INF));
    cost[0][0] = 0;
    Queue q;
    q.emplace(0, Coord{0, 0});

    const auto in_bounds = [h, w](const Coord crd) {
        return row(crd) >= 0 && row(crd) < h && col(crd) >= 0 && col(crd) < w;
    };

    while (!q.empty()) {
        const auto u = q.top().second;
        q.pop();

        for (const auto delta : vector<Coord>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
            const auto v = u + delta;
            if (!in_bounds(v)) continue;

            const auto uv_cost = abs(xss[row(u)][col(u)] - xss[row(v)][col(v)]);
            const auto candidate = cost[row(u)][col(u)] + uv_cost;
            if (cost[row(v)][col(v)] > candidate) {
                cost[row(v)][col(v)] = candidate;
                q.emplace(-candidate, v);
            }
        }
    }

    return cost.back().back();
}
