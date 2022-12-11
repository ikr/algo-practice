#include <bits/stdc++.h>
#include <gmpxx.h>
using namespace std;

using ll = mpz_class;

struct Monkey final {
    queue<ll> q;
    function<ll(ll)> op;
    function<int(ll)> route;
};

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

function<ll(ll)> parse_op(const char op, const string arg) {
    if (op == '+') return [arg](const ll x) { return ll{arg} + x; };

    assert(op == '*');
    return [arg](const ll x) { return arg == "old" ? (x * x) : (ll{arg} * x); };
}

function<int(ll)> make_routing_function(const int divisor, const int a,
                                        const int b) {
    return [divisor, a, b](const ll x) {
        return (x % ll{divisor} == ll{0}) ? a : b;
    };
}

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

auto strings_to_ints(const vector<string> &xs) {
    vector<int> result(sz(xs));
    transform(cbegin(xs), cend(xs), begin(result),
              [](const auto &x) { return stoi(x); });
    return result;
}

queue<ll> q_of(const vector<int> &xs) {
    queue<ll> result;
    for (const auto x : xs) result.push(x);
    return result;
}

Monkey read_monkey() {
    string line;
    getline(cin, line); // Monkey X:

    getline(cin, line);
    const auto xs = strings_to_ints(
        split(", ", line.substr(sz(string{"  Starting items: "}))));

    getline(cin, line);
    const auto op = [&]() {
        const auto suf = line.substr(sz(string{"  Operation: new = old "}));
        return parse_op(suf[0], suf.substr(2));
    }();

    getline(cin, line);
    const auto divisor = stoi(line.substr(sz(string{"  Test: divisible by "})));

    getline(cin, line);
    const auto a =
        stoi(line.substr(sz(string{"    If true: throw to monkey "})));

    getline(cin, line);
    const auto b =
        stoi(line.substr(sz(string{"    If false: throw to monkey "})));
    const auto route = make_routing_function(divisor, a, b);

    return {q_of(xs), op, route};
}

auto simulate_counting_inspections(vector<Monkey> monkeys, const int rounds) {
    vector<int> result(sz(monkeys), 0);

    for (int round_num = 1; round_num <= rounds; ++round_num) {
        for (int i = 0; i < sz(monkeys); ++i) {
            while (!monkeys[i].q.empty()) {
                const auto x = monkeys[i].q.front();
                monkeys[i].q.pop();
                ++result[i];

                const auto x_ = monkeys[i].op(x);
                const auto j = monkeys[i].route(x_);
                monkeys[j].q.push(x_);
            }
        }
    }

    return result;
}

template <typename T> ostream &operator<<(ostream &os, const vector<T> &xs) {
    os << '[';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << ']';
    return os;
}

int main() {
    vector<Monkey> monkeys;
    for (;;) {
        monkeys.push_back(read_monkey());
        string line;
        if (!getline(cin, line)) break;
    }

    auto inspections = simulate_counting_inspections(move(monkeys), 20);
    cerr << inspections << endl;

    sort(rbegin(inspections), rend(inspections));
    cout << (1LL * inspections[0] * inspections[1]) << '\n';
    return 0;
}
