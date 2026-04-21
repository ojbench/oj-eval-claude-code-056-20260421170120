#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct Interval {
    int l, r;
    bool operator<(const Interval& other) const {
        if (r != other.r) return r < other.r;
        return l < other.l;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    set<Interval> intervals;

    while (n--) {
        char op;
        cin >> op;
        if (op == 'A') {
            int l, r;
            cin >> l >> r;
            Interval new_int = {l, r};

            int removed_count = 0;
            // Find all intervals that overlap with [l, r]
            // An interval [L, R] overlaps with [l, r] if L <= r and R >= l

            // We search for intervals where R >= l.
            // set::lower_bound(r=l, l=-infinity) gives the first interval with R >= l.
            auto it = intervals.lower_bound({-1, l});

            while (it != intervals.end() && it->l <= r) {
                // it->r >= l is guaranteed by lower_bound
                // We check if it->l <= r to see if they overlap
                it = intervals.erase(it);
                removed_count++;
            }

            intervals.insert(new_int);
            cout << removed_count << "\n";
        } else if (op == 'B') {
            cout << intervals.size() << "\n";
        }
    }

    return 0;
}
