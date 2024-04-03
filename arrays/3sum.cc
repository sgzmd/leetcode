#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> results;
        stable_sort(nums.begin(), nums.end());

        for (auto i = 0; i < nums.size();) {
            // pair of other elements must add up to this number
            int target = -nums[i];

            for (int j = i + 1, k = nums.size() - 1;
                 j < nums.size() && k > j;) {
                auto s = nums[j] + nums[k];
                if (s > target) {
                    --k;
                } else if (s < target) {
                    ++j;
                } else {
                    // emit result, incrementing current low and high pointers
                    results.push_back(
                            vector<int>({nums[i], nums[j++], nums[k--]}));

                    // eliminate all equals from the high side
                    for (; k >= j && nums[k] == nums[k + 1]; --k) {
                    }
                    // we have now either reached the point
                    // where equality no longer holds or k < j
                }
            }

            ++i; // moving to the next pivot element
            for (; i < nums.size() && nums[i - 1] == nums[i]; ++i) {
            }
        }

        return results;
    }
};

// Function to compare and check if two sets of triplets are equal
bool compareTriplets(std::vector<std::vector<int>>& expected, std::vector<std::vector<int>>& actual) {
    if (expected.size() != actual.size()) return false;

    // Sort inner vectors to ignore order within triplets
    for (auto& triplet : expected) {
        std::sort(triplet.begin(), triplet.end());
    }
    for (auto& triplet : actual) {
        std::sort(triplet.begin(), triplet.end());
    }

    // Sort outer vector to ignore order of triplets
    std::sort(expected.begin(), expected.end());
    std::sort(actual.begin(), actual.end());

    return expected == actual;
}

// Custom checkResult function to print test results
void checkResult(const std::string& testName, std::vector<std::vector<int>>& expected, std::vector<int>& nums) {
    Solution solution;
    auto actual = solution.threeSum(nums);
    if (!compareTriplets(expected, actual)) {
        std::cerr << "Test '" << testName << "' FAILED." << std::endl
                  << "Expected: ";
        for (const auto& vec : expected) {
            std::cout << "[ ";
            for (int num : vec) std::cout << num << " ";
            std::cout << "] ";
        }
        std::cout << std::endl << "Actual: ";
        for (const auto& vec : actual) {
            std::cout << "[ ";
            for (int num : vec) std::cout << num << " ";
            std::cout << "] ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Test '" << testName << "' passed." << std::endl;
    }
}

void testThreeSum() {
    std::vector<int> nums1 = {-1, 0, 1, 2, -1, -4};
    std::vector<std::vector<int>> expected1 = {{-1, -1, 2}, {-1, 0, 1}};
    checkResult("Example 1", expected1, nums1);

    std::vector<int> nums2 = {0, 1, 1};
    std::vector<std::vector<int>> expected2 = {};
    checkResult("Example 2", expected2, nums2);

    std::vector<int> nums3 = {0, 0, 0};
    std::vector<std::vector<int>> expected3 = {{0, 0, 0}};
    checkResult("Example 3", expected3, nums3);

    // Add more test cases as needed
}

int main() {
    testThreeSum();
    return 0;
}
