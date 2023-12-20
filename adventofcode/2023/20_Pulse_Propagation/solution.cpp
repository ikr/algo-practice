#include <bits/stdc++.h>
using namespace std;

using ll = long long;
enum class MType { Plain, FlipFlop, Conjunction };
enum class Pulse { Lo, Hi };
enum class FfState { Off, On };
using Signal = tuple<string, string, Pulse>;

static constexpr ll PressesLimit = 50'000;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

constexpr FfState opposite(const FfState ffs) {
    return ffs == FfState::Off ? FfState::On : FfState::Off;
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
    map<string, MType> module_types;
    map<string, vector<string>> g;
    map<string, vector<string>> g_;

    map<string, map<string, Pulse>> conj_ram;
    map<string, FfState> ff_states;

    for (string line; getline(cin, line);) {
        const auto parts = split(" -> ", line);
        const auto source = parts[0];
        const auto tokens = split(", ", parts[1]);

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

        const auto mtype = module_types[v];
        if (mtype == MType::FlipFlop) {
            handle_flip_flop_signal(v, p);
        } else if (mtype == MType::Conjunction) {
            handle_conjunction_signal(u, v, p);
        }
    };

    const auto press_button = [&]() -> void {
        for (const auto &id : g["broadcaster"]) q.emplace("", id, Pulse::Lo);
    };

    const auto button_press_nums_causing_signal =
        [&](const Signal &expected) -> vector<ll> {
        vector<ll> result;
        q = {};

        for (int k = 1; k <= PressesLimit; ++k) {
            press_button();

            while (!empty(q)) {
                const auto s = q.front();
                q.pop();
                if (s == expected) result.push_back(k);
                handle_signal(s);
            }
        }

        return result;
    };

    ll result{1};

    for (const auto &src : {"dr", "vn", "zx", "ln"}) {
        const auto presses =
            button_press_nums_causing_signal(Signal{src, "kj", Pulse::Hi});
        cerr << presses << endl;

        vector<int> diffs(sz(presses));
        adjacent_difference(cbegin(presses), cend(presses), begin(diffs));
        cerr << diffs << endl << endl;

        result = lcm(result, diffs.back());
    }

    cout << result << '\n';
    return 0;
}
