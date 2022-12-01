#include <bits/stdc++.h>
using namespace std;

enum class Opcode {
    ADD = 1,
    MUL = 2,
    INP = 3,
    OUT = 4,
    JPT = 5,
    JPF = 6,
    LSS = 7,
    EQL = 8,
    HLT = 99
};

enum class Mode { POS = 0, IMM = 1 };

template <typename T> constexpr int inof(const T x) {
    return static_cast<int>(x);
}

template <typename T> constexpr int sz(const T &xs) { return inof(xs.size()); }

vector<string> split(const string &delim_regex, const string &s) {
    regex r(delim_regex);
    return vector<string>(sregex_token_iterator(cbegin(s), cend(s), r, -1),
                          sregex_token_iterator{});
}

tuple<Opcode, Mode, Mode> parse_op(const int op) {
    return {static_cast<Opcode>(op % 100), static_cast<Mode>((op / 100) % 10),
            static_cast<Mode>((op / 1000) % 10)};
}

struct State final {
    vector<int> xs;
    int i;
    queue<int> inq;
};

optional<int> intcode_run(State &st) {
    const auto deref = [&](const Mode m, const int p) -> int {
        return m == Mode::POS ? st.xs[p] : p;
    };

    const auto input = [&]() -> int {
        const auto x = st.inq.front();
        st.inq.pop();
        return x;
    };

    int result = INT_MIN;

    while (st.i < sz(st.xs)) {
        const auto [oc, m1, m2] = parse_op(st.xs[st.i++]);

        if (oc == Opcode::ADD) {
            const auto p1 = st.xs[st.i++];
            const auto p2 = st.xs[st.i++];
            const auto p3 = st.xs[st.i++];
            st.xs[p3] = deref(m1, p1) + deref(m2, p2);
        } else if (oc == Opcode::MUL) {
            const auto p1 = st.xs[st.i++];
            const auto p2 = st.xs[st.i++];
            const auto p3 = st.xs[st.i++];
            st.xs[p3] = deref(m1, p1) * deref(m2, p2);
        } else if (oc == Opcode::INP) {
            st.xs[st.xs[st.i++]] = input();
        } else if (oc == Opcode::OUT) {
            const auto p1 = st.xs[st.i++];
            return deref(m1, p1);
        } else if (oc == Opcode::JPT) {
            const auto p1 = st.xs[st.i++];
            const auto p2 = st.xs[st.i++];
            if (deref(m1, p1)) st.i = deref(m2, p2);
            continue;
        } else if (oc == Opcode::JPF) {
            const auto p1 = st.xs[st.i++];
            const auto p2 = st.xs[st.i++];
            if (!deref(m1, p1)) st.i = deref(m2, p2);
        } else if (oc == Opcode::LSS) {
            const auto p1 = st.xs[st.i++];
            const auto p2 = st.xs[st.i++];
            const auto p3 = st.xs[st.i++];
            st.xs[p3] = deref(m1, p1) < deref(m2, p2);
        } else if (oc == Opcode::EQL) {
            const auto p1 = st.xs[st.i++];
            const auto p2 = st.xs[st.i++];
            const auto p3 = st.xs[st.i++];
            st.xs[p3] = deref(m1, p1) == deref(m2, p2);
        } else if (oc == Opcode::HLT) {
            break;
        } else {
            assert(false && "Invalid opcode");
        }
    }

    return nullopt;
}

queue<int> q_of(const vector<int> &xs) {
    queue<int> result;
    for (const auto x : xs) result.push(x);
    return result;
}

int highest_output_signal(const vector<int> &xs) {
    int result = INT_MIN;
    array<int, 5> phases{5, 6, 7, 8, 9};

    do {
        int cur{};
        array<State, 5> states;
        for (int i = 0; i < 5; ++i) {
            auto inq = i ? q_of({phases[i]}) : q_of({cur, phases[i]});
            states[i] = State{xs, 0, inq};
        }

        result = max(result, cur);
    } while (next_permutation(begin(phases), end(phases)));

    return result;
}

int main() {
    string line;
    cin >> line;

    const auto tokens = split(",", line);
    vector<int> xs(sz(tokens));
    transform(cbegin(tokens), cend(tokens), begin(xs),
              [](const auto &x) { return stoi(x); });
    cout << highest_output_signal(xs) << '\n';
    return 0;
}
