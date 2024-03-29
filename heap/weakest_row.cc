#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

using namespace std;

// Custom comparator for the priority queue.
struct Compare {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        // First compare the number of soldiers
        if (a.first != b.first) return a.first > b.first;
        // If there's a tie, compare the indices
        return a.second > b.second;
    }
};

// The priority queue to hold pairs of <number of soldiers, row index>
using MinHeap = priority_queue<pair<int, int>, vector<pair<int, int>>, Compare>;

class Solution {
   private:
    MinHeap mh;
    size_t count_soldiers(const vector<int>& row) {
        return std::count(row.begin(), row.end(), 1);
    }

   public:
    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        for (auto i = 0; i < mat.size(); ++i) {
            pair<int, int> row = {count_soldiers(mat[i]), i};
            mh.push(row);
        }

        vector<int> result;
        for (; k > 0; --k) {
            result.push_back(mh.top().second);
            mh.pop();
        }

        return result;
    }
};

void runTests() {
    Solution solution;
    vector<vector<int>> mat;
    vector<int> result;

    // Test case 1: Provided example 1
    mat = {{1, 1, 0, 0, 0},
           {1, 1, 1, 1, 0},
           {1, 0, 0, 0, 0},
           {1, 1, 0, 0, 0},
           {1, 1, 1, 1, 1}};
    result = solution.kWeakestRows(mat, 3);
    assert((result == vector<int>{2, 0, 3}));

    // Test case 2: All rows have the same number of soldiers
    mat = {{1, 1}, {1, 1}, {1, 1}};
    result = solution.kWeakestRows(mat, 2);
    assert((result == vector<int>{0, 1}));

    // Test case 3: Each row has more soldiers
    mat = {{1, 0}, {1, 1}, {1, 1, 1}};
    result = solution.kWeakestRows(mat, 2);
    assert((result == vector<int>{0, 1}));

    // Test case 4: Each row has fewer soldiers
    mat = {{1, 1, 1}, {1, 1}, {1}};
    result = solution.kWeakestRows(mat, 2);
    assert((result == vector<int>{2, 1}));

    // Test case 5: One row with soldiers, others with none
    mat = {{1}, {0}, {0}};
    result = solution.kWeakestRows(mat, 2);
    assert((result == vector<int>{1, 2}));

    // Test case 6: All civilians
    mat = {{0, 0}, {0, 0}};
    result = solution.kWeakestRows(mat, 1);
    assert((result == vector<int>{0}));

    // Test case 7: Large matrix with max constraints
    mat = vector<vector<int>>(100, vector<int>(100, 1));
    result = solution.kWeakestRows(mat, 50);
    // Expected is first 50 indices from 0 to 49
    vector<int> expected(50);
    iota(expected.begin(), expected.end(), 0);  // Fills with 0, 1, ..., 49
    assert((result == expected));

    // Test case 8: k equals 1 and k equals m
    mat = {{1, 1}, {1, 0}, {1, 0}};
    result = solution.kWeakestRows(mat, 1);
    assert((result == vector<int>{1}));
    result = solution.kWeakestRows(mat, 3);
    assert((result == vector<int>{1, 2, 0}));

    // Test case 9: Alternating strong and weak rows
    mat = {{1, 1}, {0, 0}, {1, 1}, {0, 0}};
    result = solution.kWeakestRows(mat, 3);
    assert((result == vector<int>{1, 3, 0}));

    cout << "All test cases passed!" << endl;
}

int main() {
    runTests();
    return 0;
}
