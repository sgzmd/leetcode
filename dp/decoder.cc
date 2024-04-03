#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
private:
    unordered_map<int, int> memo;
public:
    int decode(string_view sv, int right) {
        auto it = memo.find(right);
        if (it != memo.end()) {
            return it->second;
        }

        if (right == 0) {
            return 1;
        } else if (right == 1) {
            char  c = sv[0];
            if (c < '0' || c > '9') {
                // this string cannot be decoded
                return 0;
            } else {
                return 1;
            }
        }
        int result = 0;
        auto s = sv[right-1];
        if (s != '0') {
            result += decode(sv, right-1);
        }

        if (right > 1) {
            auto twodigit = sv.substr(right-2, 2);
            if (twodigit[0] == '0') {
                // can't start with zero
                return result;
            } else {
                auto number = atoi(string(twodigit).c_str());
                if (number > 26) {
                    // cannot decode
                    return result;
                } else {
                    result += decode(sv, right - 2);
                }
            }
        }

        memo[right] = result;

        return result;
    }

    int numDecodings(string s) {
        memo[0] = 1;
        if (s.size() > 0 && s[0] == '0') {
            return 0;
        }
        memo.clear();
        return decode(s, s.size());
    }
};

// Test runner function
void runTest(string testID, string input, int expected) {
    Solution sol;
    int result = sol.numDecodings(input);
    if (result != expected) {
        cerr << "Test " << testID << " Failed. Expected: " << expected << ", Got: " << result << endl;
    } else {
        cout << "Test " << testID << " Passed." << endl;
    }
}

int main() {
    // Test cases
    runTest("Test 1", "12", 2); // Normal case
    runTest("Test 2", "226", 3); // Normal case
    runTest("Test 3", "06", 0); // Edge case with leading zero
    runTest("Test 4", "0", 0); // Single character edge case
    runTest("Test 5", "1", 1); // Single character normal case
    runTest("Test 6", "111", 3); // Multiple decodings
    runTest("Test 7", "101", 1); // Zero within the string
    runTest("Test 8", "27", 1); // Just above boundary condition
    runTest("Test 9", "999", 1); // No valid two-digit decodings
    runTest("Test 10", "1001", 0); // Zeros not allowing decoding
    runTest("Test 11", "2101", 1);

    // Feel free to add more test cases as needed
    return 0;
}
