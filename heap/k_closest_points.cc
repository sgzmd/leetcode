#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

inline int eqd(const vector<int>& point) {
    auto x = point[0], y = point[1];
    return x * x + y * y;
}

class Solution {
   public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        // Using greater because min-heap
        auto cmp = [](const vector<int>& lhs, const vector<int>& rhs) {
            return eqd(lhs) > eqd(rhs);
        };\

        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);
        for (auto p : points) {
            pq.push(p);
        }

        vector<vector<int>> result;
        while (result.size() != (size_t) k) {
            result.push_back(pq.top());
            pq.pop();
        }
        
        return result;
    }
};

vector<vector<int>> testFunction(vector<vector<int>>& points, int k) {
    Solution solution;
    return solution.kClosest(points, k);
}

void testKClosestPoints() {
    vector<vector<int>> points;
    int k;
    vector<vector<int>> expected;
    vector<vector<int>> result;

    // Example 1:
    points = {{1, 3}, {-2, 2}};
    k = 1;
    expected = {{-2, 2}};
    result = testFunction(points, k);
    assert(result == expected);
    cout << "Test case 1 passed!" << endl;

    // Example 2:
    points = {{3, 3}, {5, -1}, {-2, 4}};
    k = 2;
    expected = {{3, 3},
                {-2, 4}};  // The function can return the points in any order
    result = testFunction(points, k);
    // Since the result can be in any order, we need to sort before comparing
    sort(result.begin(), result.end());
    sort(expected.begin(), expected.end());
    assert(result == expected);
    cout << "Test case 2 passed!" << endl;

    // Additional test cases can be added here

    cout << "All test cases passed!" << endl;
}

int main() {
    testKClosestPoints();
    return 0;
}
