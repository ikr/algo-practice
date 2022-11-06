#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

char next_base(const char x) {
    switch (x) {
    case 'A':
        return 'C';
    case 'C':
        return 'G';
    case 'G':
        return 'T';
    case 'T':
        return 'A';
    default:
        assert(false && "next_base");
        return '-';
    }
}

char prev_base(const char x) {
    switch (x) {
    case 'A':
        return 'T';
    case 'C':
        return 'A';
    case 'G':
        return 'C';
    case 'T':
        return 'G';
    default:
        assert(false && "next_base");
        return '-';
    }
}

vector<string> adjacent(const string &xs) {
    vector<string> result;
    for (int i = 0; i < sz(xs); ++i) {
        auto ys = xs;

        ys[i] = next_base(xs[i]);
        result.push_back(ys);

        ys[i] = prev_base(xs[i]);
        result.push_back(ys);
    }
    return result;
}

pair<int, string> ops_to_any(const string &src, const set<string> &dst) {
    assert(!dst.empty());
    unordered_map<string, int> D;
    D[src] = 0;

    queue<string> q;
    q.push(src);

    while (!q.empty()) {
        const auto u = q.front();
        q.pop();

        for (const auto &v : adjacent(u)) {
            if (D.count(v)) continue;

            if (dst.count(v)) {
                return {D.at(u) + 1, v};
            }

            D[v] = D.at(u) + 1;
            q.push(v);
        }
    }

    return {1e9, ""};
}

int min_ops(const vector<string> &dst) {
    const auto L = sz(dst[0]);
    set<string> xs(cbegin(dst), cend(dst));

    string src(L, 'A');

    if (xs.count(src)) {
        xs.erase(src);
    }

    int result{};

    while (!xs.empty()) {
        const auto [ops, x] = ops_to_any(src, xs);
        result += ops;

        src = x;
        xs.erase(x);
    }

    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N, L;
    cin >> N >> L;

    vector<string> dst(N);
    for (auto &xs : dst) cin >> xs;

    cout << min_ops(dst) << '\n';
    return 0;
}
