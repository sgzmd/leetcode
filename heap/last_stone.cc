#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    int lastStoneWeight(vector<int>& stones) {
        // heaviest two stones - means top must be greatest elements
        // this implies max heap

        priority_queue<int> pq;
        for (auto s : stones) {
            pq.push(s);
        }

        while (pq.size() > 1) {
            auto y = pq.top();
            pq.pop();
            auto x = pq.top();
            pq.pop();
            if (x != y) {
                pq.push(y - x);
            }
        }

        if (pq.empty()) {
            return 0;
        } else {
          return pq.top();
        }
    }
};

void runTests() {
    Solution solution;
    vector<int> stones;
    int result;

    // Test case 1: General case
    stones = {2, 7, 4, 1, 8, 1};
    result = solution.lastStoneWeight(stones);
    assert(result == 1);

    // Test case 2: Only one stone
    stones = {1};
    result = solution.lastStoneWeight(stones);
    assert(result == 1);

    // Test case 3: All stones equal
    stones = {4, 4, 4, 4};
    result = solution.lastStoneWeight(stones);
    assert(result == 0);

    // Test case 4: Stones where one is double the other
    stones = {1, 2};
    result = solution.lastStoneWeight(stones);
    assert(result == 1);

    // Test case 5: Descending order
    stones = {10, 8, 6, 4, 2};
    result = solution.lastStoneWeight(stones);
    assert(result == 2);

    // Test case 6: Maximum number and weight of stones
    stones = vector<int>(30, 1000);
    result = solution.lastStoneWeight(stones);
    assert(result == 0);

    // Add more cases as needed...

    cout << "All test cases passed!" << endl;
}

int main() {
    runTests();
    return 0;
}
