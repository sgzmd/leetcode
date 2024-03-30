#include <cassert>
#include <climits>
#include <iostream>
#include <string>

class Solution {
public:
    int myAtoi(std::string s) {
        // Implementation goes here
        return 0;
    }
};

void testMyAtoi() {
    Solution solution;

    // Test with leading whitespace
    assert(solution.myAtoi("   42") == 42);

    // Test with negative number
    assert(solution.myAtoi("   -42") == -42);

    // Test with positive sign
    assert(solution.myAtoi("+42") == 42);

    // Test with non-digit characters after the number
    assert(solution.myAtoi("4193 with words") == 4193);
    assert(solution.myAtoi("42abc") == 42);

    // Test with digits after non-digit characters (should ignore these characters and consider it as 0)
    assert(solution.myAtoi("words and 987") == 0);

    // Test clamping to 32-bit signed integer limits
    assert(solution.myAtoi("-91283472332") == INT_MIN); // Should clamp to INT_MIN
    assert(solution.myAtoi("91283472332") == INT_MAX); // Should clamp to INT_MAX

    // Edge cases
    assert(solution.myAtoi("") == 0); // Empty string
    assert(solution.myAtoi("+") == 0); // Just a plus sign
    assert(solution.myAtoi("-") == 0); // Just a minus sign
    assert(solution.myAtoi("    ") == 0); // Only whitespace
    assert(solution.myAtoi("+0") == 0); // Zero with plus sign
    assert(solution.myAtoi("-0") == 0); // Zero with minus sign

    std::cout << "All tests passed successfully." << std::endl;
}

int main() {
    testMyAtoi();
    return 0;
}
