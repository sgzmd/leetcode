#include <cassert>
#include <climits>
#include <iostream>
#include <string>

class Solution {
private:
    enum Sign {
        NONE,
        NEG,
        POS
    };
public:
    int myAtoi(std::string s) {

        const int INT_MAX_DIVIDED_BY_10 = INT_MAX / 10;
        const int INT_MIN_DIVIDED_BY_10 = INT_MIN / 10;

        size_t i = 0;
        for (; i < s.size() && s[i] == ' '; ++i);
        Sign sign = NONE;
        int result = 0;
        for ( ; i < s.size(); ++i) {
            auto c = s[i];
            if (c == '+') {
                if (sign == NONE) {
                    sign = POS;
                } else {
                    return 0;
                }
                // do nothing
            } else if (c == '-' ){
                if (sign == NONE) {
                    sign = NEG;
                } else {
                    return 0;
                }
            } else if (isdigit(c)) {
                int digit = c - '0';
                if (sign == NEG) {
                    if (result <= INT_MIN_DIVIDED_BY_10) {
                        return INT_MIN;
                    } else if (digit >= result * 10 - INT_MIN) {
                        return INT_MIN;
                    }
                    result = result * 10 - digit;
                } else {
                    if (sign == NONE) {
                        sign = POS;
                    }
                    if (result > INT_MAX_DIVIDED_BY_10) {
                        return INT_MAX;
                    } else if (digit >= INT_MAX - result * 10) {
                        return INT_MAX;
                    }
                    result = result * 10 + digit;
                }
            } else {
                return result;
            }
        }

        return result;
    }
};

void checkResult(const std::string& testName, int expected, int actual) {
    if (expected != actual) {
        std::cerr << "Test '" << testName << "' FAILED. Expected: " << expected << ", Actual: " << actual << std::endl;
    } else {
        std::cout << "Test '" << testName << "' passed." << std::endl;
    }
}

void testMyAtoi() {
    Solution solution;

    // Now using checkResult instead of assert
    checkResult("Near INT_MAX boundary", 2147483646, solution.myAtoi("2147483646"));
    checkResult("Clamp to INT_MAX on boundary", INT_MAX, solution.myAtoi("2147483648"));
    checkResult("Leading '+' and '-'", 0, solution.myAtoi("+-12"));
    checkResult("Leading whitespace", 42, solution.myAtoi("   42"));
    checkResult("Negative number", -42, solution.myAtoi("   -42"));
    checkResult("Positive sign", 42, solution.myAtoi("+42"));
    checkResult("Non-digit characters after number", 4193, solution.myAtoi("4193 with words"));
    checkResult("Non-digit characters after number 2", 42, solution.myAtoi("42abc"));
    checkResult("Digits after non-digit characters", 0, solution.myAtoi("words and 987"));
    checkResult("Clamp to INT_MIN", INT_MIN, solution.myAtoi("-91283472332"));
    checkResult("Clamp to INT_MAX", INT_MAX, solution.myAtoi("91283472332"));
    checkResult("Empty string", 0, solution.myAtoi(""));
    checkResult("Just a plus sign", 0, solution.myAtoi("+"));
    checkResult("Just a minus sign", 0, solution.myAtoi("-"));
    checkResult("Only whitespace", 0, solution.myAtoi("    "));
    checkResult("Zero with plus sign", 0, solution.myAtoi("+0"));
    checkResult("Zero with minus sign", 0, solution.myAtoi("-0"));
}

int main() {
    testMyAtoi();
    return 0;
}
