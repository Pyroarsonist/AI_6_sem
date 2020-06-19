#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>

using namespace std;

#define capacity pair<int, int>
#define problem_state vector<capacity>

map<problem_state, bool> banned;


vector<problem_state > path;


bool is_solution(problem_state state, int solution) {
    for (int i = 0; i < state.size(); i++) {
        for (int j = 0; j < state.size(); j++) {
            if (i == j)
                continue;

            if (state[i].first == solution && state[j].first == solution)
                return true;
        }
    }

    return false;
}

void print_current_state(problem_state state) {
    for (capacity j: state)
        printf("<%d/%d> ", j.first, j.second);
    cout << endl;
}

problem_state copy_state(problem_state state) {
    problem_state ret_state;

    for (capacity j: state) {
        ret_state.emplace_back(capacity{j.first, j.second});
    }
    return ret_state;
}

int fitness(problem_state state, int target) {
    int c = 0;
    for (int i = 0; i < state.size(); i++) {
        if (state[i].first == target)
            c++;
    }
    return c;
}


void sort_problem_states(vector<problem_state > v, int target) {
    vector<int> v_f;
    v_f.reserve(v.size());
    for (int i = 0; i < v.size(); i++) {
        v_f.emplace_back(fitness(v[i], target));
    }

    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v.size(); j++) {
            if (i == j)
                continue;
            if (v_f[i] < v_f[j]) {
                auto temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
        }
    }
}

bool tabu(problem_state state, int target) {
    banned[state] = true;
    path.emplace_back(state);

    if (is_solution(state, target)) {
        cout << "Solution found!!!" << endl;

        int counter = 1;
        for (problem_state s: path) {
            printf("%d) ", counter);
            print_current_state(s);
            counter++;
        }
        return true;
    }


    vector<problem_state > available_nodes;

    for (int i = 0; i < state.size(); i++) {
        if (state[i].first != 0) {
            auto temp_state = copy_state(state);
            temp_state[i].first = 0;

            if (!banned[temp_state])
                available_nodes.emplace_back(temp_state);
        }
        if (state[i].first > 0) {
            for (int j = 0; j < state.size(); j++) {
                if (i == j)
                    continue;
                // state[i] -> state[j]
                int left = state[j].second - state[j].first;
                if (left > 0) {
                    int diff = left - state[i].first;
                    auto temp_state = copy_state(state);

                    if (diff >= 0) {
                        // state[j] not full
                        temp_state[j].first += temp_state[i].first;
                        temp_state[i].first = 0;
                        if (!banned[temp_state])
                            available_nodes.emplace_back(temp_state);
                    } else {
                        // state[j] full
                        temp_state[j].first = state[j].second;
                        temp_state[i].first = abs(diff);
                        if (!banned[temp_state])
                            available_nodes.emplace_back(temp_state);
                    }

                }
            }
        }
        if (state[i].first != state[i].second) {
            auto temp_state = copy_state(state);
            temp_state[i].first = state[i].second;
            if (!banned[temp_state])
                available_nodes.emplace_back(temp_state);
        }
    }

    sort_problem_states(available_nodes, target);

    for (problem_state s: available_nodes) {
        bool found = tabu(s, target);
        if (found) {
            return true;
        }
    }
    cout << "Dead end" << endl;
    return false;
}

int main() {
    capacity barrel = {0, 12};
    int jug_count = 5, jug_size = 7, target = 6;
    problem_state state;
    state.emplace_back(barrel);
    state.reserve(jug_count);
    for (int i = 0; i < jug_count; ++i) {
        state.emplace_back(0, jug_size);
    }
    printf("Barrel size: %d\nTarget: %d\nJug sizes: ", barrel.second, target);
    print_current_state(state);
    cout << endl << endl;
    tabu(state, target);

    return 0;
}
