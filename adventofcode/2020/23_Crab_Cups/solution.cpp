#include <bits/stdc++.h>
using namespace std;
constexpr int N_MAX = 9;

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

    void make_move() {
        auto a = head->next;
        auto b = a->next->next;
        rotate_to(
            destination(head->value, {a->value, a->next->value, b->value}));
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

void debug(const State &st) {
    cout << "(";

    auto p = st.head;
    while (p) {
        if (p != st.head) cout << " ";
        cout << p->value;
        p = p->next;
    }

    cout << ")\n";
}

list<int> rotate_to(const list<int> &xs, const int t) {
    const auto it = find(cbegin(xs), cend(xs), t);
    list<int> ans;
    ans.insert(cend(ans), it, cend(xs));
    ans.insert(cend(ans), cbegin(xs), it);
    return ans;
}

vector<int> copy_to_stash(const list<int> &xs) {
    const auto first = next(cbegin(xs));
    auto last = first;
    advance(last, 3U);

    vector<int> ans(first, last);
    assert(ans.size() == 3U);
    return ans;
}

list<int> erase_stash(list<int> xs) {
    const auto first = next(cbegin(xs));
    auto last = first;
    advance(last, 3U);
    assert(distance(first, last) == 3U);

    xs.erase(first, last);
    return xs;
}

list<int> make_move(const list<int> &xs) {
    const auto stash = copy_to_stash(xs);
    auto ys = erase_stash(xs);
    const int dest = destination(xs.front(), stash);

    const auto dest_it = find(cbegin(ys), cend(ys), dest);
    ys.insert(next(dest_it), cbegin(stash), cend(stash));
    return rotate_to(ys, *next(cbegin(ys)));
}

list<int> poke_one(const list<int> &xs) {
    auto ans = rotate_to(xs, 1);
    ans.pop_front();
    return ans;
}

string join(const list<int> &xs) {
    return accumulate(cbegin(xs), cend(xs), string{},
                      [](string agg, const int x) {
                          agg += to_string(x);
                          return agg;
                      });
}

string solve(list<int> xs) {
    for (int i = 0; i < 100; ++i) {
        xs = make_move(xs);
    }

    return join(poke_one(xs));
}

int main() {
    string s;
    cin >> s;

    array<int, 9> xs;
    transform(cbegin(s), cend(s), begin(xs),
              [](const char d) { return d - '0'; });

    State st(xs);

    return 0;
}
