#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    enum Color {
        NONE = 0,
        RED = 1,
        BLUE = 2
    };

    Color opposite(Color c) {
        return (c == BLUE) ? RED : BLUE;
    }

    bool isBipartite(vector<vector<int>> &graph) {
        /*
         * Taking elements from graph, and if it's not coloured, doing BFS from that element.
         * If this is the first element, then we should reach all connected components from that element
         * If it's not and it's coloured, we've already seen it
         * If it's not and it's not coloured, we found a disconnected partition
         */
        vector<Color> colors(graph.size(), Color::NONE);
        for (auto i = 0; i < graph.size(); ++i) {
            cout << __LINE__ << ": " << "Processing graph element " << i << endl;
            if (colors[i] == Color::NONE) {
                // Let's BFS it.
                queue<pair<size_t, Color>> q;
                q.push({i, Color::BLUE});

                while (!q.empty()) {
                    auto [node, color] = q.front(); q.pop();
                    colors[node] = color;

                    auto notcolor = opposite(color);
                    auto adj = graph[node];
                    for (auto adjn : adj) {
                        if (colors[adjn] == Color::NONE) {
                            q.push({adjn, notcolor});
                        } else if (colors[adjn] != notcolor) {
                            return false;
                        }
                    }
                }
            }
        }

        return true;
    }
};

// Helper function to print test results
void printTestResult(int testNum, vector<vector<int>> &graph, bool expected) {
    Solution solution;
    bool result = solution.isBipartite(graph);
    cout << "Test Case " << testNum << ": " << (result == expected ? "Passed" : "Failed") << endl;
}

int main() {
    // Test Case 1: Minimum graph size
    vector<vector<int>> test1 = {{}};
    printTestResult(1, test1, true); // Adjust expected result based on your interpretation

    // Test Case 2: Provided example where graph is bipartite
    vector<vector<int>> test2 = {{1, 3},
                                 {0, 2},
                                 {1, 3},
                                 {0, 2}};
    printTestResult(2, test2, true);

    // Test Case 3: Provided example where graph is not bipartite
    vector<vector<int>> test3 = {{1, 2, 3},
                                 {0, 2},
                                 {0, 1, 3},
                                 {0, 2}};
    printTestResult(3, test3, false);

    // Test Case 4: Graph with multiple disconnected components
    vector<vector<int>> test4 = {{1},
                                 {0, 2, 3},
                                 {1},
                                 {1},
                                 {5},
                                 {4}};
    printTestResult(4, test4, false);

    // Test Case 5: A fully connected graph - not bipartite
    vector<vector<int>> test5 = {{1, 2, 3},
                                 {0, 2, 3},
                                 {0, 1, 3},
                                 {0, 1, 2}};
    printTestResult(5, test5, false);

    // Test Case 6: A linear chain - bipartite
    vector<vector<int>> test6 = {{1},
                                 {0, 2},
                                 {1, 3},
                                 {2}};
    printTestResult(6, test6, true);

    // Test Case 7: A single cycle of even length - bipartite
    vector<vector<int>> test7 = {{1, 3},
                                 {0, 2},
                                 {1, 3},
                                 {0, 2}};
    printTestResult(7, test7, true);

// Test Case 9: Complex graph with specific structure and expected to be not bipartite
    vector<vector<int>> test9 = {{},
                                 {2, 4, 6},
                                 {1, 4, 8, 9},
                                 {7, 8},
                                 {1, 2, 8, 9},
                                 {6, 9},
                                 {1, 5, 7, 8, 9},
                                 {3, 6, 9},
                                 {2, 3, 4, 6, 9},
                                 {2, 4, 5, 6, 7, 8}};
    printTestResult(9, test9, false);

    // Test Case 10: Graph with specific structure expected to be bipartite
    vector<vector<int>> test10 = {{4},
                                  {},
                                  {4},
                                  {4},
                                  {0, 2, 3}};
    printTestResult(10, test10, true);


    return 0;
}
