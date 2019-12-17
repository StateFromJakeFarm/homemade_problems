#include <set>
#include <vector>
#include <climits>
#include <utility>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    // Read number of intervals
    int n;
    cin >> n;

    // (time, end time) --> end time of INT_MAX means this is an end time
    vector< pair<int, int> > intervals;

    // Read in all starting and ending times
    int start, end;
    for (int i=0; i<n; i++) {
        cin >> start >> end;

        intervals.emplace_back(start, end);
        intervals.emplace_back(end, INT_MAX);
    }

    // Sort our list by start time
    sort(intervals.begin(), intervals.end());

    // Maintain a lookup table of intervals we are "in" as we iterate over the
    // list
    set<int> inside_rn;
    int total = 0;
    int time, end_time;
    for (auto cur_interval : intervals) {
        time = cur_interval.first;
        end_time = cur_interval.second;

        if (end_time != INT_MAX) {
            // If we're inside of any intervals, the current interval must
            // overlap with them
            for (int inside_end : inside_rn) {
                total += min(inside_end, end_time) - time + 1;
            }

            // Log end time of interval we just entered
            inside_rn.insert(end_time);
        } else {
            inside_rn.erase(time);
        }
    }

    cout << total << endl;

    return 0;
}
