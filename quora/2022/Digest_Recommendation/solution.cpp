#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T, size_t N>
ostream &operator<<(ostream &os, const array<T, N> &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

template <typename T, size_t N>
ostream &operator<<(ostream &os, const vector<array<T, N>> &xss) {
    for (const auto xs : xss) os << xs << '\n';
    return os;
}

void sort_rows(vvi &xss) {
    for (auto &xs : xss) {
        sort(begin(xs), end(xs));
    }
}

template <typename T, size_t N>
vector<array<T, N>> inc_each(vector<array<T, N>> src) {
    for (auto &xs : src) {
        for (auto &x : xs) {
            ++x;
        }
    }
    return src;
}

vvi gather_author_stories(const int m, const vi &story_authors) {
    vvi result(m);
    for (int s = 0; s < sz(story_authors); ++s) {
        const auto a = story_authors[s];
        result[a].push_back(s);
    }
    sort_rows(result);
    return result;
}

vector<array<int, 3>> recommend(const vi &story_authors, const vvi &u_fllw,
                                const vvi &s_fllw) {
    const auto n = sz(story_authors);
    const auto m = sz(u_fllw);
    const auto author_stories = gather_author_stories(m, story_authors);

    const auto alpha = [&](const int i, const int j) -> int {
        assert(0 <= i && i < m);
        assert(0 <= j && j < m);

        const auto ui_follows_story_s = [&](const int s) -> bool {
            return binary_search(cbegin(s_fllw[i]), cbegin(s_fllw[i]), s);
        };

        if (i == j) return 0;
        if (binary_search(cbegin(u_fllw[i]), cend(u_fllw[i]), j)) return 3;
        if (any_of(cbegin(author_stories[j]), cend(author_stories[j]),
                   ui_follows_story_s)) {
            return 2;
        }
        if (any_of(cbegin(s_fllw[j]), cend(s_fllw[j]), ui_follows_story_s)) {
            return 1;
        }
        return 0;
    };

    vector<array<int, 3>> result(m, array<int, 3>{});
    return result;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m;
    cin >> n >> m;

    vi story_authors(n, -1);
    for (auto &a : story_authors) {
        cin >> a;
        --a;
    }

    int p, q;
    cin >> p >> q;

    vvi u_fllw(m);
    for (int i = 1; i <= p; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        u_fllw[u].push_back(v);
    }
    sort_rows(u_fllw);

    vvi s_fllw(m);
    for (int i = 1; i <= q; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        s_fllw[u].push_back(v);
    }
    sort_rows(s_fllw);

    cout << inc_each(recommend(story_authors, u_fllw, s_fllw));
    return 0;
}
