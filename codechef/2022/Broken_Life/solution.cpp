#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <vector>
using namespace std;

constexpr char chof(const int x) { return static_cast<char>(x); }

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

map<char, vector<int>> indices_of_present_chars(const string &xs) {
    map<char, vector<int>> result{
        {'a', {}}, {'b', {}}, {'c', {}}, {'d', {}}, {'e', {}}};

    for (int i = 0; i < sz(xs); ++i) {
        if (xs[i] == '?') continue;
        assert(result.count(xs[i]));
        result[xs[i]].push_back(i);
    }

    return result;
}

bool match(const string &S, const string &A) {
    const auto idx = indices_of_present_chars(S);

    for (int i = 0, p = 0; i < sz(A); ++i) {
        const auto &ii = idx.at(A[i]);
        const auto it = lower_bound(cbegin(ii), cend(ii), p);
        if (it == cend(ii)) return false;
        p = (*it) + 1;
    }

    return true;
}

constexpr char next_char(const char x) {
    const auto v = inof(x) - inof('a');
    return chof(inof('a') + ((v + 1) % 5));
}

optional<string> S_prime(string S, const string &A) {
    if (match(S, A)) return nullopt;
    const auto next_j = [&A](const int j) { return (j + 1) % sz(A); };

    for (int i = 0, j = 0; i < sz(S); ++i) {
        assert(0 <= j && j < sz(A));
        if (S[i] == '?') {
            S[i] = next_char(A[j]);
        } else if (S[i] == A[j]) {
            j = next_j(j);
        }
    }

    return S;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;
    while (t--) {
        int N, M;
        cin >> N >> M;

        string S;
        cin >> S;
        assert(sz(S) == N);

        string A;
        cin >> A;
        assert(sz(A) == M);

        const auto ans = S_prime(move(S), A);
        if (ans) {
            cout << *ans << '\n';
        } else {
            cout << "-1\n";
        }
    }

    return 0;
}
