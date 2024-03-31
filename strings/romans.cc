#include <cassert>
#include <iostream>
#include <string>
#include <map>

class Solution {
public:
    int romanToInt(std::string s) {
        std::map<char, int> rim = {
                {'I', 1},
                {'V', 5},
                {'X', 10},
                {'L', 50},
                {'C', 100},
                {'D', 500},
                {'M', 1000}
        };

        int result = 0;
        int prev = 0, curr = 0;

        for (int i = s.size()-1; i >= 0; --i) {
            curr = rim[s[i]];
            if (curr < prev) {
                result -= curr;
            } else {
                result += curr;
            }
            prev = curr;
        }

        return result;
    }
};

void checkResult(const std::string& testName, int expected, const std::string& roman) {
    Solution solution;
    int actual = solution.romanToInt(roman);
    if (expected != actual) {
        std::cerr << "Test '" << testName << "' FAILED. Expected: " << expected << ", Actual: " << actual << ", Roman: " << roman << std::endl;
    } else {
        std::cout << "Test '" << testName << "' passed." << std::endl;
    }
}

void testRomanToInt() {
    // Test cases
    checkResult("Simple III", 3, "III");
    checkResult("Subtractive notation IV", 4, "IV");
    checkResult("Subtractive notation IX", 9, "IX");
    checkResult("Simple addition LVIII", 58, "LVIII");
    checkResult("Mixed subtractive MCMXCIV", 1994, "MCMXCIV");
    checkResult("Maximum valid roman numeral MMMCMXCIX", 3999, "MMMCMXCIX");
    checkResult("Single I", 1, "I");
    checkResult("Single V", 5, "V");
    checkResult("Single X", 10, "X");
    checkResult("Single L", 50, "L");
    checkResult("Single C", 100, "C");
    checkResult("Single D", 500, "D");
    checkResult("Single M", 1000, "M");
    checkResult("Subtractive notation XL", 40, "XL");
    checkResult("Subtractive notation XC", 90, "XC");
    checkResult("Subtractive notation CD", 400, "CD");
    checkResult("Subtractive notation CM", 900, "CM");

    // Add more test cases as needed
}

int main() {
    testRomanToInt();
    return 0;
}
