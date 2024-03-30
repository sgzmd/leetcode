#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.empty()) {
            return 0;
        }

        const int n = s.size();
        int right = 0, left = 0, max_length = 0;
        unordered_map<char, int> idxs;

        for (; right < n; ++right) {
            auto c = s[right];
            auto it = idxs.find(c);

            if (it != idxs.end()) {
                // It's possible we have some old value in the map
                // and we are past that part of the string
                auto prev_idx = max(it->second, left);

                // Let's estimate the max length we got so far
                // It will be from [prev_idx to right)
                max_length = max(max_length, right - prev_idx);
                if (s[prev_idx] == c) {
                    left = prev_idx + 1;
                }
            }

            idxs[c] = right;
            max_length = max(max_length, right - left + 1);
        }

        max_length = max(max_length, right - left);

        return max_length;
    }
};

void runTests() {
    vector<pair<string, int>> testCases = {
            {"tmmzuxt",     5},
            {"abcabcbb",    3},
            {"bbbbb",       1},
            {"pwwkew",      3},
            {"",            0},
            {"abcdef",      6},
            {"a b c d e f", 3},
            {"a1b2c3d4",    8},
            {"abcdabcd",    4},
            {"!@#$%^&*()",  10},
            {"aA1Bb2",      6},
            {"cdd",         2},
    };

    Solution solution;
    bool allTestsPassed = true;
    for (auto &[testInput, expectedOutput]: testCases) {
        int result = solution.lengthOfLongestSubstring(testInput);
        if (result != expectedOutput) {
            allTestsPassed = false;
            cout << "Test Failed for Input: \"" << testInput << "\" Expected: " << expectedOutput << ", Got: " << result
                 << endl;
        } else {
            cout << "Test passed for Input: " << testInput << endl;
        }
    }

    if (allTestsPassed) {
        cout << "All tests passed!" << endl;
    } else {
        cout << "Some tests failed. Check your implementation." << endl;
    }
}

int main() {
    runTests();
    return 0;
}
