#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(),
             [](const auto& lhs, const auto& rhs) {
                 return (lhs[0] == rhs[0]) ? lhs[1] < rhs[1] : lhs[0] < rhs[0];
             });

        priority_queue<int, vector<int>, greater<int>> end_times;  // min-heap

        int num_rooms = 0;
        for (auto interval : intervals) {
            if (end_times.empty()) {
                num_rooms++;
                end_times.push(interval[1]);
            } else {
                int min_end = end_times.top();
                if (min_end <= interval[0]) {
                    end_times.pop();
                    --num_rooms;
                }
                end_times.push(interval[1]);
                ++num_rooms;
            }
        }

        return num_rooms;
    }
};

void testMinMeetingRooms() {
    Solution solution;
    vector<vector<int>> intervals;
    int expected;
    int result;

    // Example 1:
    intervals = {{0, 30}, {5, 10}, {15, 20}};
    expected = 2;
    result = solution.minMeetingRooms(intervals);
    assert(result == expected);
    cout << "Test case 1 passed!" << endl;

    // Example 2:
    intervals = {{7, 10}, {2, 4}};
    expected = 1;
    result = solution.minMeetingRooms(intervals);
    assert(result == expected);
    cout << "Test case 2 passed!" << endl;

    // Additional test cases could be added here

    cout << "All test cases passed!" << endl;
}

int main() {
    testMinMeetingRooms();
    return 0;
}
