#include <vector>
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

/*

Given an integer array nums and an integer k, return true if nums has a good subarray or false otherwise.

A good subarray is a subarray where:

- its length is at least two, and
- the sum of the elements of the subarray is a multiple of k.

 Note that:

- A subarray is a contiguous part of the array.
- An integer x is a multiple of k if there exists an integer n such that x = n * k. 0 is always a multiple of k.

Example 1:

Input: nums = [23,2,4,6,7], k = 6
Output: true
Explanation: [2, 4] is a continuous subarray of size 2 whose elements sum up to 6.
Example 2:

Input: nums = [23,2,6,4,7], k = 6
Output: true
Explanation: [23, 2, 6, 4, 7] is an continuous subarray of size 5 whose elements sum up to 42.
42 is a multiple of 6 because 42 = 7 * 6 and 7 is an integer.
Example 3:

Input: nums = [23,2,6,4,7], k = 13
Output: false

 Let's start with bruteforce


 int max_len = 0;
 for (int i = 0; i < nums.size(); ++i) {
    int sum = 0;
   for (int j = i; j < nums.size(); ++j {
     sum += nums[j];

   if (sum % k == 0) {
     max_len = max(max_len, j-i);
   }

   }

}

say i = 0
sum += nums[0]
 sum += nums[1]
  sum += nums[2]
...



 */

class Solution {
public:
    bool checkSubarraySum(vector<int> &nums, int k) {
        unordered_map<int, size_t> rs;
        int running_sum = 0;
        for (size_t i = 0; i < nums.size(); ++i) {
            running_sum += nums[i];
            int r = running_sum % k;
            if (!r && i > 0) {
                return true;
            }
            auto it = rs.find(r);
            if (it != rs.end()) {
                if (i - it->second > 1) {
                    return true;
                }
            } else {
                rs[r] = i;
            }
        }
        return false;
    }
};

void runTest(std::vector<int> nums, int k, bool expected) {
    Solution solution;
    bool result = solution.checkSubarraySum(nums, k);
    if (result == expected) {
        std::cout << "Test passed." << std::endl;
    } else {
        std::cout << "Test failed." << std::endl;
    }
}

int main() {
    // Test 1: Example 1
    runTest({23, 2, 4, 6, 7}, 6, true);

    // Test 2: Example 2
    runTest({23, 2, 6, 4, 7}, 6, true);

    // Test 3: Example 3
    runTest({23, 2, 6, 4, 7}, 13, false);

    // Test 4: Subarray at the beginning
    runTest({6, 1, 2, 3}, 6, true);

    // Test 5: Single element array (should return false)
    runTest({6}, 6, false);

//    // Test 6: Zero is present in the array
//    runTest({0, 0}, 6, true);

    // Test 10: Edge case with k = 1
    runTest({1, 2, 3, 4, 5}, 1, true);

    runTest({23, 2, 4, 6, 6}, 7, true);

    return 0;
}
