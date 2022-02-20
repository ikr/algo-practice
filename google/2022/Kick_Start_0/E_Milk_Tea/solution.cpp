#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <numeric>
#include <set>
#include <vector>
using namespace std;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<int> freqs_of_ones(const vector<string> &xss) {
    vector<int> result(sz(xss[0]), 0);
    for (const auto &xs : xss) {
        assert(sz(xs) == sz(result));

        for (int i = 0; i < sz(xs); ++i) {
            if (xs[i] == '1') ++result[i];
        }
    }
    return result;
}

string gather_proto_result(const int N, const vector<int> &fq1) {
    const auto P = sz(fq1);
    string proto_result(P, '0');

    for (int i = 0; i < P; ++i) {
        if (fq1[i] > N - fq1[i]) {
            proto_result[i] = '1';
        }
    }

    return proto_result;
}

int diffs_num(const string &xs, const string &ys) {
    assert(sz(xs) == sz(ys));
    int result{};

    for (int i = 0; i < sz(xs); ++i) {
        if (xs[i] != ys[i]) ++result;
    }

    return result;
}

int diffs_num(const vector<string> &xss, const string &ys) {
    int result{};
    for (const auto &xs : xss) {
        result += diffs_num(xs, ys);
    }
    return result;
}

void flip_at(string &xs, const int i) { xs[i] = xs[i] == '1' ? '0' : '1'; }

constexpr int mlog2(const unsigned int x) {
    return 8 * sizeof(unsigned int) - __builtin_clz(x) - 1;
}

vector<string> prepare_variations(const int M,
                                  const vector<int> &idx_by_flip_cost,
                                  const string &proto) {
    const auto lim = mlog2(M) + 2;
    assert(lim < 10);

    vector<string> result;

    for (int bits = 0; sz(result) <= M && bits < (1 << lim) - 1; ++bits) {
        string curr = proto;

        for (int i = 0; i < min(10, sz(idx_by_flip_cost)); ++i) {
            if ((1 << i) & bits) {
                flip_at(curr, idx_by_flip_cost[i]);
            }
        }

        result.push_back(curr);
    }

    return result;
}

int min_complaints(const vector<string> &preferences,
                   const set<string> &forbidden) {
    const auto N = sz(preferences);
    const auto P = sz(preferences[0]);
    const auto fq1 = freqs_of_ones(preferences);

    vector<int> idx_by_flip_cost(P);
    iota(begin(idx_by_flip_cost), end(idx_by_flip_cost), 0);

    const auto flip_cost = [&](const int i) -> int {
        return abs(N - 2 * fq1[i]);
    };

    sort(begin(idx_by_flip_cost), end(idx_by_flip_cost),
         [&](const int i, const int j) -> bool {
             return flip_cost(i) < flip_cost(j);
         });

    const auto proto = gather_proto_result(N, fq1);
    auto vs = prepare_variations(sz(forbidden), idx_by_flip_cost, proto);

    sort(begin(vs), end(vs), [&](const auto &lhs, const auto &rhs) {
        return diffs_num(preferences, lhs) < diffs_num(preferences, rhs);
    });

    for (const auto &v : vs) {
        if (!forbidden.count(v)) return diffs_num(preferences, v);
    }

    return numeric_limits<int>::max();
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N, M, P;
        cin >> N >> M >> P;

        vector<string> preferences(N);
        for (auto &p : preferences) {
            cin >> p;
            assert(sz(p) == P);
        }

        set<string> forbidden;
        for (int j = 1; j <= M; ++j) {
            string f;
            cin >> f;
            assert(sz(f) == P);
            forbidden.insert(f);
        }

        cout << "Case #" << i << ": " << min_complaints(preferences, forbidden)
             << '\n';
    }

    return 0;
}
