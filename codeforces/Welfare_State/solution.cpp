#include <bits/stdc++.h>

using namespace std;

using ui_t = unsigned int;
using BalPer = pair<ui_t, ui_t>;

enum class EventType { RECEIPT = 1, PAYOFF = 2 };

void handle_receipt(vector<ui_t> &balances_by_person,
                    multiset<BalPer> &persons_by_balance,
                    const BalPer receipt) {}

void handle_payoff(vector<ui_t> &balances_by_person,
                   multiset<BalPer> &persons_by_balance, const ui_t threshold) {
}

int main() {
    ui_t n;
    cin >> n;

    vector<ui_t> balances_by_person(n + 1, 0);
    multiset<BalPer> persons_by_balance;

    for (ui_t i = 1; i <= n; ++i) {
        cin >> balances_by_person[i];
        persons_by_balance.insert(BalPer{balances_by_person[i], i});
    }

    ui_t events_count;
    cin >> events_count;

    for (ui_t i = 0; i != events_count; ++i) {
        ui_t event_type;
        cin >> event_type;

        if (event_type == static_cast<ui_t>(EventType::RECEIPT)) {
            ui_t person;
            ui_t new_balance;
            cin >> person >> new_balance;

            handle_receipt(balances_by_person, persons_by_balance,
                           {new_balance, person});
        } else {
            ui_t threshold;
            cin >> threshold;

            handle_payoff(balances_by_person, persons_by_balance, threshold);
        }
    }

    for (ui_t i = 1; i <= n; ++i) {
        if (i > 1) cout << ' ';
        cout << balances_by_person[i];
    }
    cout << '\n';
}
