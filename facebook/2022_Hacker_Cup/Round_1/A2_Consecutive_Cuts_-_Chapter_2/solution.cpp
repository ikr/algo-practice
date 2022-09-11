#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

deque<int> normalize(deque<int> xs) {
    if (all_of(cbegin(xs), cend(xs),
               [&](const auto a) { return a == xs[0]; })) {
        return xs;
    }

    while (xs.front() == xs.back()) {
        const auto x = xs.front();
        xs.pop_front();
        xs.push_back(x);
    }

    return xs;
}

vector<pii> run_length_encoding(const deque<int> &xs) {
    vector<pii> result{{xs[0], 1}};
    for (int i = 1; i < sz(xs); ++i) {
        if (result.back().first == xs[i]) {
            ++(result.back().second);
        } else {
            result.emplace_back(xs[i], 1);
        }
    }
    return result;
}

bool is_possible(const int K, deque<int> A, deque<int> B) {
    if (K == 0) return A == B;

    if (A.size() == 2) {
        if (A == B) {
            return K % 2 == 0;
        } else {
            return K % 2 == 1;
        }
    }

    if (A == B) return K != 1;

    const auto AA = run_length_encoding(normalize(move(A)));
    auto BB = run_length_encoding(normalize(move(B)));

    const auto a0 = AA[0];
    const auto i0 = distance(cbegin(BB), find(cbegin(BB), cend(BB), a0));
    rotate(begin(BB), begin(BB) + i0, end(BB));
    return AA == BB;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        int N, K;
        cin >> N >> K;

        deque<int> A(N);
        for (auto &a : A) cin >> a;

        deque<int> B(N);
        for (auto &b : B) cin >> b;

        cout << "Case #" << i << ": "
             << (is_possible(K, move(A), move(B)) ? "YES" : "NO") << '\n';
    }

    return 0;
}
