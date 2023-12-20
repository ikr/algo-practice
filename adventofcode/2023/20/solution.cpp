#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

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
enum class FfState { Off, On };
using Signal = tuple<string, string, Pulse>;

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

ostream &operator<<(ostream &os, const FfState ffs) {
    if (ffs == FfState::On) {
        os << "ON";
    } else {
        assert(ffs == FfState::Off);
        os << "OFF";
    }
    return os;
}

constexpr FfState opposite(const FfState ffs) {
    return ffs == FfState::Off ? FfState::On : FfState::Off;
}

int main() {
    map<string, MType> module_types;
    map<string, vector<string>> g;
    map<string, vector<string>> g_;

    map<string, map<string, Pulse>> conj_ram;
    map<string, FfState> ff_states;

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
        if (mtype == MType::Conjunction) {
            for (const auto &v : g_.at(u)) {
                conj_ram[u][v] = Pulse::Lo;
            }
        } else if (mtype == MType::FlipFlop) {
            ff_states[u] = FfState::Off;
        }
    }

    cerr << "types: " << module_types << endl;
    cerr << "g: " << g << endl << "g_:" << g_ << endl;
    cerr << "initial conj_ram: " << conj_ram << endl;
    cerr << "initial ff_states: " << ff_states << endl;

    int num_hi{};
    int num_lo{};
    queue<Signal> q;

    const auto handle_flip_flop_signal = [&](const string &id,
                                             const Pulse p) -> void {
        if (p == Pulse::Hi) return;

        const auto current_state = ff_states.at(id);
        const auto pulse_to_send =
            current_state == FfState::Off ? Pulse::Hi : Pulse::Lo;

        for (const auto &v : g.at(id)) q.emplace(id, v, pulse_to_send);
        ff_states[id] = opposite(current_state);
    };

    const auto handle_conjunction_signal =
        [&](const string &from_id, const string &id, const Pulse p) -> void {
        conj_ram[id][from_id] = p;

        const auto pulse_to_send =
            ranges::all_of(
                conj_ram[id],
                [](const auto &kv) { return kv.second == Pulse::Hi; })
                ? Pulse::Lo
                : Pulse::Hi;

        for (const auto &v : g.at(id)) q.emplace(id, v, pulse_to_send);
    };

    const auto handle_signal = [&](const Signal &s) -> void {
        const auto [u, v, p] = s;
        if (p == Pulse::Lo) {
            ++num_lo;
        } else {
            ++num_hi;
        }

        const auto mtype = module_types[v];
        if (mtype == MType::FlipFlop) {
            handle_flip_flop_signal(v, p);
        } else if (mtype == MType::Conjunction) {
            handle_conjunction_signal(u, v, p);
        }
    };

    const auto push_button = [&]() -> void {
        ++num_lo;
        for (const auto &id : g["broadcaster"]) q.emplace("", id, Pulse::Lo);
    };

    for (int k = 1; k <= 1000; ++k) {
        push_button();
        while (!empty(q)) {
            const auto s = q.front();
            q.pop();
            handle_signal(s);
        }
    }

    cerr << "num_lo:" << num_lo << " num_hi:" << num_hi << endl;
    cout << llof(num_hi) * llof(num_lo) << '\n';
    return 0;
}
