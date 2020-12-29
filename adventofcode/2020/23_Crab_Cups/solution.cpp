#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int N_MAX = 1e6;
constexpr int MOVES = 1e7;

template <typename T> constexpr ll llof(const T x) {
    return static_cast<ll>(x);
}

constexpr int cyc_dec(const int x) { return x - 1 ? x - 1 : N_MAX; }

int destination(const int current, const array<int, 3> &stash) {
    set<int> abc(cbegin(stash), cend(stash));

    int ans = cyc_dec(current);
    while (abc.count(ans)) ans = cyc_dec(ans);
    return ans;
}

struct Node final {
    Node(const int x) : value{x}, next{nullptr} {}
    const int value;
    Node *next;
};

struct State final {
    State(const array<int, 9> &xs)
        : head{nullptr}, tail{nullptr}, idx(N_MAX + 1, nullptr) {
        for (const int x : xs) append(x);
        for (int i = 10; i <= N_MAX; ++i) append(i);
    }

    ~State() {
        auto p = head;
        while (p) {
            auto q = p->next;
            delete p;
            p = q;
        }
    }

    void append(const int x) {
        if (!head) {
            head = new Node(x);
            tail = head;
            return;
        }

        const auto n = new Node(x);
        tail->next = n;
        idx[x] = tail;
        tail = n;
    }

    ll answer() {
        rotate_to(1);
        return llof(head->next->value) * llof(head->next->next->value);
    }

    void new_second_element(const int x) {
        auto pre_a = idx[x];
        auto a = pre_a->next;
        auto post_a = a->next;

        if (post_a) {
            idx[post_a->value] = pre_a;
        } else {
            tail = pre_a;
        }

        pre_a->next = post_a;

        idx[x] = head;
        a->next = head->next;
        head->next = a;
        idx[a->next->value] = a;
    }

    void make_move() {
        const auto current = head->value;

        const auto a = head->next;
        const auto b = a->next;
        const auto c = b->next;
        const auto d = destination(head->value, {a->value, b->value, c->value});
        rotate_to(d);

        for (const auto x : {a, b, c}) {
            new_second_element(x->value);
            if (x != c) rotate_to(x->value);
        }

        rotate_to(current);
        rotate_to(head->next->value);
    }

    void rotate_to(const int t) {
        if (t == head->value) return;

        auto new_tail = idx[t];
        auto new_head = idx[t]->next;
        new_tail->next = nullptr;
        tail->next = head;

        idx[t] = nullptr;
        idx[head->value] = tail;
        head = new_head;
        tail = new_tail;
    }

    Node *head;
    Node *tail;
    vector<Node *> idx;
};

int main() {
    string s;
    cin >> s;

    array<int, 9> xs;
    transform(cbegin(s), cend(s), begin(xs),
              [](const char d) { return d - '0'; });

    State st(xs);
    for (int i = 0; i < MOVES; ++i) st.make_move();
    cout << st.answer() << '\n';
    return 0;
}
