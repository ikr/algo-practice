#include <bits/stdc++.h>

using namespace std;

using ui_t = unsigned int;

enum class Answer { A = 'A', B = 'B', C = 'C', D = 'D', E = 'E' };

vector<Answer> answers_domain() {
    return {Answer::A, Answer::B, Answer::C, Answer::D, Answer::E};
}

Answer to_answer(const char c) {
    assert('A' <= c && c <= 'E');
    return static_cast<Answer>(c);
}

Answer guess_correct_answer(const multiset<Answer> &stat) {
    map<ui_t, Answer> answers_by_count;

    for (const auto a : answers_domain()) {
        answers_by_count[stat.count(a)] = a;
    }

    return answers_by_count.crbegin()->second;
}

vector<Answer> guess_correct_answers(const vector<multiset<Answer>> &stats) {
    vector<Answer> result(stats.size());

    transform(stats.cbegin(), stats.cend(), result.begin(),
              guess_correct_answer);

    return result;
}

int main() {
    ui_t n;
    ui_t m;
    cin >> n >> m;

    vector<vector<Answer>> submissions(n);
    vector<multiset<Answer>> stats(m);

    for (ui_t i = 0U; i != n; ++i) {
        string submission_buffer;
        cin >> submission_buffer;

        vector<Answer> submission(m);
        transform(submission_buffer.cbegin(), submission_buffer.cend(),
                  submission.begin(), to_answer);

        submissions[i] = submission;

        for (ui_t j = 0U; j != m; ++j) stats[j].insert(submission[j]);
    }

    vector<ui_t> grades(m);
    for (auto &g : grades) {
        cin >> g;
    }

    vector<Answer> co_corrects = guess_correct_answers(stats);
    ui_t result{0U};

    for (ui_t i = 0U; i != n; ++i)
        for (ui_t j = 0U; j != m; ++j)
            if (submissions[i][j] == co_corrects[j]) result += grades[j];

    cout << result << '\n';
    return 0;
}
