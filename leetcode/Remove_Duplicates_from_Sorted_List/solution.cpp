#include "lest.hpp"
#include <bits/stdc++.h>

using namespace std;

struct ListNode final {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// MEMORY LEAKS!
// Non-production contest code. No proper memory management here.
//
struct Solution final {
    ListNode *deleteDuplicates(ListNode *head) const {
        if (!head) return nullptr;
        auto next = head->next;

        while (next && next->val == head->val) next = next->next;

        if (!next) {
            head->next = nullptr;
            return head;
        }

        head->next = deleteDuplicates(next);
        return head;
    }
};

ListNode *lst(const vector<int> &xs) {
    ListNode *head{nullptr};
    ListNode *tail{nullptr};

    for (const int x : xs) {
        ListNode *n = new ListNode(x);

        if (!head) {
            head = n;
            tail = n;
        } else {
            tail->next = n;
            tail = n;
        }
    }

    return head;
}

vector<int> vec(ListNode *head) {
    vector<int> result;

    ListNode *n = head;

    while (n) {
        result.push_back(n->val);
        n = n->next;
    }

    return result;
}

// clang-format off
const lest::test tests[] = {
    CASE("vec") {
        ListNode *a = new ListNode(1);
        ListNode *b = new ListNode(2);
        ListNode *c = new ListNode(3);
        a->next = b;
        b->next = c;
        const auto actual = vec(a);
        const auto expected = vector<int>{1, 2, 3};
        EXPECT(actual == expected);
    },
    CASE("vec ° lst") {
        const auto actual = vec(lst({1, 2, 3, 4}));
        const auto expected = vector<int>{1, 2, 3, 4};
        EXPECT(actual == expected);
    },
    CASE("()") {
        const auto actual = vec(Solution().deleteDuplicates(lst({})));
        const auto expected = vector<int>{};
        EXPECT(actual == expected);
    },
    CASE("(1)") {
        const auto actual = vec(Solution().deleteDuplicates(lst({1})));
        const auto expected = vector<int>{1};
        EXPECT(actual == expected);
    },
    CASE("(1 2 3)") {
        const auto actual = vec(Solution().deleteDuplicates(lst({1,2,3})));
        const auto expected = vector<int>{1,2,3};
        EXPECT(actual == expected);
    },
    CASE("(1 1)") {
        const auto actual = vec(Solution().deleteDuplicates(lst({1,1})));
        const auto expected = vector<int>{1};
        EXPECT(actual == expected);
    },
    CASE("(1 1 2 2)") {
        const auto actual = vec(Solution().deleteDuplicates(lst({1,1,2,2})));
        const auto expected = vector<int>{1,2};
        EXPECT(actual == expected);
    },
};
// clang-format on

int main(int argc, char **argv) { return lest::run(tests, argc, argv); }
