#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using ti = tuple<int, int, int>;

struct Book final {
    int reading_time;
    bool liked_by_alice;
    bool liked_by_bob;
};

tuple<vi, vi, vi> reading_times_by_reader(const vector<Book> &books) {
    vi ab_reading_times, a_reading_times, b_reading_times;

    for (const auto &b : books) {
        if (b.liked_by_alice && b.liked_by_bob) {
            ab_reading_times.push_back(b.reading_time);
        } else if (b.liked_by_alice) {
            a_reading_times.push_back(b.reading_time);
        } else if (b.liked_by_bob) {
            b_reading_times.push_back(b.reading_time);
        }
    }

    return {ab_reading_times, a_reading_times, b_reading_times};
}

int sum_up_answer(const tuple<vi, vi, vi> &by_reader, const ti &counts) {
    const auto &[ab_reading_times, a_reading_times, b_reading_times] =
        by_reader;

    const auto [ab_num, a_num, b_num] = counts;

    return accumulate(ab_reading_times.cbegin(),
                      ab_reading_times.cbegin() + ab_num, 0) +
           accumulate(a_reading_times.cbegin(),
                      a_reading_times.cbegin() + a_num, 0) +
           accumulate(b_reading_times.cbegin(),
                      b_reading_times.cbegin() + b_num, 0);
}

int min_total_reading_time(vector<Book> books, const int k) {
    sort(books.begin(), books.end(), [](const auto &lhs, const auto &rhs) {
        return lhs.reading_time < rhs.reading_time;
    });

    const auto by_reader = reading_times_by_reader(books);
    const auto &[ab_reading_times, a_reading_times, b_reading_times] =
        by_reader;

    vector<ti> dp(k + 1, {0, 0, 0});

    const auto ans = sum_up_answer(by_reader, dp.back());
    return ans ? ans : -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int sz, k;
    cin >> sz >> k;
    vector<Book> books(sz, {0, false, false});
    for (auto &b : books) {
        cin >> b.reading_time >> b.liked_by_alice >> b.liked_by_bob;
    }

    cout << min_total_reading_time(books, k) << '\n';

    return 0;
}
