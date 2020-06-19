#include <iostream>
#include <vector>
#include <map>

#define bucket_state pair<int, int>

using namespace std;

map<bucket_state, bool> m;


vector<bucket_state > path;


// dfs with limitations
bool search(bucket_state state, int jug_1, int jug_2, int target, int depth) {
    m[state] = true;
    path.emplace_back(state);

    int current_jug_1 = state.first;
    int current_jug_2 = state.second;

    printf("<%d,%d>\n", current_jug_1, current_jug_2);


    if (target == current_jug_1 || target == current_jug_2) {
        printf("Solution <%d,%d> found!\n", current_jug_1, current_jug_2);

        int counter = 1;
        for (bucket_state s: path) {
            printf("%d) <%d,%d>\n ", counter, s.first, s.second);
            counter++;
        }
        return true;
    }

    if (depth == 0) {
        path.pop_back();
        return false;
    }


    vector<bucket_state > available_nodes;
    if (current_jug_1 != 0)
        available_nodes.emplace_back(bucket_state{0, current_jug_2});
    if (current_jug_2 != 0)
        available_nodes.emplace_back(bucket_state{current_jug_1, 0});
    if (current_jug_1 != jug_1)
        available_nodes.emplace_back(bucket_state{jug_1, current_jug_2});
    if (current_jug_2 != jug_2)
        available_nodes.emplace_back(bucket_state{current_jug_1, jug_2});

    // from jug_1 to jug_2
    if (current_jug_1 > 0) {
        int max_diff_b = jug_2 - current_jug_2;
        if (current_jug_1 > max_diff_b) {
            // full jug_2
            available_nodes.emplace_back(bucket_state{current_jug_1 - max_diff_b, jug_2});
        } else {
            // empty jug_1
            available_nodes.emplace_back(bucket_state{0, current_jug_2 + current_jug_1});
        }
    }

    // from jug_2 to jug_1
    if (current_jug_2 > 0) {
        int max_diff_a = jug_1 - current_jug_1;
        if (current_jug_2 > max_diff_a) {
            // full jug_1
            available_nodes.emplace_back(bucket_state{jug_1, current_jug_2 - max_diff_a});
        } else {
            // empty jug_2
            available_nodes.emplace_back(bucket_state{current_jug_1 + current_jug_2, 0});
        }
    }

    for (bucket_state s: available_nodes)
        if (!m[s]) {
            bool found = search(s, jug_1, jug_2, target, depth - 1);
            if (found) {
                return true;
            }
        }
    cout << "No solution found" << endl;
    return false;
}

int main() {
    int jug_1 = 5, jug_2 = 9, target = 3;
    printf("Jug 1 has capacity %d\nJug 2 has capacity %d\nTarget: %d\n", jug_1, jug_2, target);
    bucket_state initial_state = {0, 0};
    search(initial_state, jug_1, jug_2, target, 11);
    return 0;
}
