#include <vector>
#include <climits>
#include <queue>
#include <cassert>
#include <iostream>
#include <functional>

using namespace std;

class Solution {
public:
    
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        priority_queue<int, vector<int>> pq;
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix.size(); ++j) {
                pq.push(matrix[i][j]);
                if (pq.size() > k) {
                    pq.pop();
                }
            }
        }

        return pq.top();
    }
};


int main() {
    Solution solution;
    vector<vector<int>> matrix;
    int k;
    int expected;
    int result;

    // Example 1:
    matrix = {{1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
    k = 8;
    expected = 13;
    result = solution.kthSmallest(matrix, k);
    assert(result == expected);
    cout << "Test case 1 passed!" << std::endl;

    // Example 2:
    matrix = {{-5}};
    k = 1;
    expected = -5;
    result = solution.kthSmallest(matrix, k);
    assert(result == expected);
    cout << "Test case 2 passed!" << endl;

    cout << "All test cases passed!" << endl;
    return 0;
}