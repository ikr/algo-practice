#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

template <typename T> ostream &operator<<(ostream &os, const optional<T> o) {
    if (!o) {
        os << "nullopt";
    } else {
        os << *o;
    }
    return os;
}

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &x) {
    os << '(' << x.first << ' ' << x.second << ')';
    return os;
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

template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &xss) {
    for (const auto &xs : xss) os << xs << '\n';
    return os;
}

template <typename T> ostream &operator<<(ostream &os, const set<T> &xs) {
    os << '{';
    for (auto i = xs.cbegin(); i != xs.cend(); ++i) {
        if (i != xs.cbegin()) os << ' ';
        os << *i;
    }
    os << '}';
    return os;
}

template <typename K, typename V>
ostream &operator<<(ostream &os, const map<K, V> &m) {
    os << '{';
    for (auto i = m.cbegin(); i != m.cend(); ++i) {
        if (i != m.cbegin()) os << ' ';
        os << '(' << i->first << ' ' << i->second << ')';
    }
    os << '}';
    return os;
}

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

enum class MType { Plain, FlipFlop, Conjunction };
enum class Pulse { Lo, Hi };

ostream &operator<<(ostream &os, const MType mt) {
    switch (mt) {
    case MType::FlipFlop:
        os << '%';
        break;
    case MType::Conjunction:
        os << '&';
        break;
    default:
        os << '-';
    }
    return os;
}

ostream &operator<<(ostream &os, const Pulse p) {
    if (p == Pulse::Hi) {
        os << "HI";
    } else {
        assert(p == Pulse::Lo);
        os << "LO";
    }
    return os;
}

int main() {
    map<string, MType> module_types;
    map<string, vector<string>> g;
    map<string, vector<string>> g_;

    map<string, map<string, Pulse>> conj_ram;

    for (string line; getline(cin, line);) {
        const auto parts = split(" -> ", line);
        const auto source = parts[0];

        const auto tokens = split(", ", parts[1]);
        cerr << source << " -> " << tokens << endl;

        const auto mtype = [&]() -> MType {
            switch (source[0]) {
            case '%':
                return MType::FlipFlop;
            case '&':
                return MType::Conjunction;
            default:
                return MType::Plain;
            }
        }();

        const auto u = mtype == MType::Plain ? source : source.substr(1);
        module_types[u] = mtype;

        g[u] = tokens;
        for (const auto &v : tokens) g_[v].push_back(u);
    }

    for (const auto &[u, mtype] : module_types) {
        if (mtype != MType::Conjunction) continue;
        for (const auto &v : g_.at(u)) {
            conj_ram[u][v] = Pulse::Lo;
        }
    }

    cerr << "types: " << module_types << endl;
    cerr << "g: " << g << endl << "g_:" << g_ << endl;
    cerr << "initial conj_ram: " << conj_ram << endl;
    return 0;
}
