#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

class KthLargest {
   private:
    size_t k;
    vector<int> nums;
    priority_queue<int, vector<int>, greater<int>> pq;

   public:
    KthLargest(size_t k, vector<int>& nums) : k(k), nums(nums) {
        for (auto n : nums) {
            add(n);
        }
    }

    int add(int val) {
        if (pq.size() < k) {
            pq.push(val);
        } else if (val > pq.top()) {
            pq.pop();
            pq.push(val);
        }

        return pq.top();
    }
};

void testKthLargest() {
    // Test case 1
    vector<int> nums1 = {4, 5, 8, 2};
    KthLargest kth1(3, nums1);
    assert(kth1.add(3) == 4);   // After adding 3, kth largest is 4
    assert(kth1.add(5) == 5);   // After adding 5, kth largest is 5
    assert(kth1.add(10) == 5);  // After adding 10, kth largest is 5
    assert(kth1.add(9) == 8);   // After adding 9, kth largest is 8
    assert(kth1.add(4) == 8);   // After adding 4, kth largest is 8

    // Test case 2
    vector<int> nums2 = {};
    KthLargest kth2(1, nums2);
    assert(kth2.add(-1) == -1);  // kth largest with only one element in stream
    assert(kth2.add(-2) == -1);  // still -1
    assert(kth2.add(-3) == -1);  // still -1
    assert(kth2.add(0) == 0);    // now it's 0
    assert(kth2.add(2) == 2);    // now it's 2

    // Test case 3
    vector<int> nums3 = {99, 99};
    KthLargest kth3(1, nums3);
    assert(kth3.add(100) == 100);  // 100 is the largest
    assert(kth3.add(50) == 100);   // 100 is still the largest

    // Test case 4 - Large numbers and k
    vector<int> nums4 = {1000000000, 1000000000, 1000000000, 1000000000};
    KthLargest kth4(4, nums4);
    assert(kth4.add(1000000000) == 1000000000);  // Test with large numbers

    cout << "All test cases passed!" << endl;
}

int main() {
    testKthLargest();
    return 0;
}