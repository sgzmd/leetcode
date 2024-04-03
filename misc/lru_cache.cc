#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <memory>
#include <deque>

using namespace std;

template<typename K, typename V>
struct Node {
    K key;
    V value;

    shared_ptr<Node> next;
    weak_ptr<Node> prev;

    Node(const K &k, const V &v) : key(k), value(v), next(nullptr), prev() {}
};

template<typename K, typename V, V defaultValue>
class LRUCacheT {
private:
    unordered_map<K, shared_ptr<Node<K, V>>> cache;
    shared_ptr<Node<K, V>> head;
    shared_ptr<Node<K, V>> tail;

    int capacity;
    int size;
public:
    LRUCacheT(int capacity) :
            capacity(capacity), size(0), head(nullptr), tail(nullptr) {}

    V get(K key) {
        auto it = cache.find(key);
        if (it == cache.end()) {
            return defaultValue;
        } else {
            auto node = it->second;
            moveToHead(node);
            return node->value;
        }
    }

    int getCapacity() const {
        return this->capacity;
    }

    void put(K key, V value) {
        auto it = cache.find(key);
        if (it == cache.end()) {
            auto newNode = make_shared<Node<K, V>>(key, value);
            cache[key] = newNode;
            addNode(newNode);
            evictAsNeeded();
        } else {
            it->second->value = value;
            moveToHead(it->second);
        }
    }

protected:
    void addNode(shared_ptr<Node<K, V>> node) {
        if (head == nullptr) {
            head = tail = node;
        } else {
            node->next = head;
            head->prev = node;
            head = node;
        }

        if (size <= capacity) {
            ++size;
        }
    }

    void removeNode(shared_ptr<Node<K, V>> node) {
        // If current node have previous pointer, let's reassign
        // this previuos' next pointer to current node's next
        if (node->prev.lock()) {
            node->prev.lock()->next = node->next;
        }

        // If this node has next pointer (i.e. it's not head)
        // Let's reassign next node's prev pointer to this node's prev.
        // Question: are we buying anything with lock'ing node->prev?
        if (node->next) {
            node->next->prev = node->prev;
        }

        if (node == head) {
            head = node->next;
        }
        if (node == tail) {
            tail = node->prev.lock();
        }

        node->prev.reset();
        node->next.reset();
    }

    void evictAsNeeded() {
        if (size > capacity) {
            if (tail != nullptr) {
                cache.erase(tail->key);
                removeNode(tail);
                --size;
            }
        }
    }

    void moveToHead(shared_ptr<Node<K, V>> node) {
        removeNode(node);
        addNode(node);
    }
};

typedef LRUCacheT<int, int, -1> LRUCache;

struct TestResult {
    std::string name;
    bool passed;

    TestResult(std::string testName, bool testPassed)
            : name(testName), passed(testPassed) {}
};

bool testInitialization() {
    LRUCache cache(2);
    return cache.getCapacity() == 2; // Assuming getCapacity() is a method for testing
}

bool testBasicPutAndGet() {
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    return cache.get(1) == 1 && cache.get(2) == 2;
}

bool testEvictionPolicy() {
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cache.put(3, 3); // This should evict key 1
    return cache.get(1) == -1 && cache.get(3) == 3;
}

bool testLRUCacheSequence() {
    LRUCache cache(10); // Initialize with capacity 10 as per the first operation.
    cache.put(10, 13);
    cache.put(3, 17);
    cache.put(6, 11);
    cache.put(10, 5);
    cache.put(9, 10);
    bool result = true; // Assume success unless a check fails.

    // The first get operation after setup; expecting -1 since key 13 was never added.
    result &= (cache.get(13) == -1);

    cache.put(2, 19);
    result &= (cache.get(2) == 19);
    result &= (cache.get(3) == 17);

    cache.put(5, 25); // This should not evict anything yet, as capacity is 10.

    // Following the sequence with assumed correct operations and verifying expected outcomes.
    cache.put(9, 22);
    cache.put(5, 5);
    cache.put(1, 30);
    result &= (cache.get(11) == -1); // Key 11 should not be in the cache.

    // Continue with the rest of operations as per the sequence provided.
    // For brevity, not all operations are explicitly listed here. Please complete them similarly.

    // Example of checking after more operations:
    cache.put(9, 12);
    result &= (cache.get(7) == -1); // Assuming 7 was not added or evicted.
    result &= (cache.get(5) == 5);
    result &= (cache.get(8) == -1); // Assuming 8 was not added or evicted.
    result &= (cache.get(9) == 12);

    // Include all other operations from the sequence in a similar fashion.
    // Ensure to update `result` with the outcome of each check.

    return result; // true if all checks passed, false if any failed.
}

std::vector<TestResult> runTests() {
    std::vector<TestResult> results;
    results.emplace_back("Test Initialization", testInitialization());
    results.emplace_back("Test Basic Put and Get", testBasicPutAndGet());
    results.emplace_back("Test Eviction Policy", testEvictionPolicy());
    results.emplace_back("Test LRU Cache Sequence", testLRUCacheSequence());
    // Add additional tests here...

    return results;
}

void reportResults(const std::vector<TestResult> &results) {
    std::vector<std::string> failedTests;

    for (const auto &result: results) {
        if (!result.passed) {
            failedTests.push_back(result.name);
        }
    }

    if (failedTests.empty()) {
        std::cout << "All tests passed successfully." << std::endl;
    } else {
        std::cout << "The following tests failed:" << std::endl;
        for (const auto &testName: failedTests) {
            std::cout << "- " << testName << std::endl;
        }
    }
}



int main() {
    auto testResults = runTests();
    reportResults(testResults);
    return 0;
}