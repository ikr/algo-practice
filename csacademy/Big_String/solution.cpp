#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vll = vector<ll>;
using vvll = vector<vll>;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}
template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}
template <typename T> constexpr double doof(const T x) {
    return static_cast<double>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

static constexpr int AZ = 26;
using Freqs = array<ll, AZ>;
using State = pair<Freqs, char>;

ostream &operator<<(ostream &os, const Freqs &xs) {
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    return os;
}

string apply_operation(const string &xs) {
    string repeated = xs.substr(0, sz(xs) - 1);
    reverse(begin(repeated), end(repeated));
    string ans = xs + repeated;
    return ans;
}

Freqs freqs(const string &xs) {
    Freqs ans{};
    for (const auto x : xs) ++ans[x - 'a'];
    return ans;
}

State initial_state(const string &xs) {
    auto head = freqs(xs);
    --head[xs.back() - 'a'];
    return {head, xs.back()};
}

Freqs mul_by_two(Freqs xs) {
    transform(cbegin(xs), cend(xs), begin(xs),
              [](const auto x) { return x * 2LL; });
    return xs;
}

State op_transition(const State &s0) {
    auto [head, pivot] = s0;
    return {mul_by_two(head), pivot};
}

Freqs meld(const State &state) {
    auto [head, tail] = state;
    ++head[tail - 'a'];
    return head;
}

Freqs freqs_after_k_ops(const string &xs, const int k) {
    auto state = initial_state(apply_operation(xs));

    for (int i = 2; i <= k; ++i) {
        state = op_transition(state);
    }

    return meld(state);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(9) << fixed;

    string xs;
    cin >> xs;
    int k;
    cin >> k;

    cout << freqs_after_k_ops(xs, k) << '\n';
    return 0;
}
