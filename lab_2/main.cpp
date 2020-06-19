#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#define n 3

using namespace std;

#define problem_state vector<vector<int>>
#define problem_state_with_worth pair<problem_state, int>

map<problem_state, bool> m;

vector<problem_state_with_worth > path;


void locate_value_at_needed_place(int *x, int *y, int value) {
    if (value == 0) {
        *x = n / 2;
        *y = n / 2;
        return;
    }
    int counter = 1;
    for (int j = 0; j < n; ++j) {
        if (counter == value) {
            *x = 0;
            *y = j;
            return;
        };
        counter++;
    }
    for (int i = 1; i < n; ++i) {
        if (counter == value) {
            *x = i;
            *y = n - 1;
            return;
        };
        counter++;
    }
    for (int j = (n - 1) - 1; j >= 0; --j) {
        if (counter == value) {
            *x = n - 1;
            *y = j;
            return;
        };
        counter++;
    }
    for (int i = (n - 1) - 1; i >= 0; --i) {
        if (counter == value) {
            *x = i;
            *y = 0;
            return;
        };
        counter++;
    }
}

int manhattan_distance(problem_state matrix, int x, int y) {
    int current_value = matrix[x][y];
    int needed_x, needed_y;
    locate_value_at_needed_place(&needed_x, &needed_y, current_value);
    return abs(needed_x - x) + abs(needed_y - y);
}

int worth(problem_state matrix) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            sum += manhattan_distance(matrix, i, j);
        }
    }
    return sum;
}

bool is_solution(problem_state matrix) {
    return worth(matrix) == 0;
}

void print_matrix(problem_state matrix) {
    cout << "======" << endl << "Worth: " << worth(matrix) << endl;
    for (vector<int> v: matrix) {
        for (int i: v) {
            cout << i << " ";
        }
        cout << endl;
    }
    cout << "======" << endl;
}

bool problem_comparator(problem_state_with_worth i, problem_state_with_worth j) { return (i.second < j.second); }


bool rbfs(problem_state matrix) {
    m[matrix] = true;
    path.emplace_back(pair{matrix, worth(matrix)});

    if (is_solution(matrix)) {
        cout << "Solution found!" << endl;
        print_matrix(matrix);

        int counter = 1;
        for (auto s: path) {
            cout << counter << ")" << endl;
            print_matrix(s.first);
            counter++;
        }
        return true;
    }


    vector<problem_state_with_worth > available_nodes;
    if (matrix[0][0] == 0) {
        problem_state right_horizontal_matrix;
        right_horizontal_matrix.emplace_back(vector<int>{matrix[0][1], matrix[0][0], matrix[0][2]});
        right_horizontal_matrix.emplace_back(vector<int>(matrix[1]));
        right_horizontal_matrix.emplace_back(vector<int>(matrix[2]));
        available_nodes.emplace_back(pair{right_horizontal_matrix, worth(right_horizontal_matrix)});

        problem_state down_vertical_matrix;
        down_vertical_matrix.emplace_back(vector<int>{matrix[1][0], matrix[0][1], matrix[0][2]});
        down_vertical_matrix.emplace_back(vector<int>{matrix[0][0], matrix[1][1], matrix[1][2]});
        down_vertical_matrix.emplace_back(vector<int>(matrix[2]));
        available_nodes.emplace_back(pair{down_vertical_matrix, worth(down_vertical_matrix)});
    } else if (matrix[0][1] == 0) {
        problem_state right_horizontal_matrix;
        right_horizontal_matrix.emplace_back(vector<int>{matrix[0][0], matrix[0][2], matrix[0][1]});
        right_horizontal_matrix.emplace_back(vector<int>(matrix[1]));
        right_horizontal_matrix.emplace_back(vector<int>(matrix[2]));
        available_nodes.emplace_back(pair{right_horizontal_matrix, worth(right_horizontal_matrix)});

        problem_state left_horizontal_matrix;
        left_horizontal_matrix.emplace_back(vector<int>{matrix[0][1], matrix[0][0], matrix[0][2]});
        left_horizontal_matrix.emplace_back(vector<int>(matrix[1]));
        left_horizontal_matrix.emplace_back(vector<int>(matrix[2]));
        available_nodes.emplace_back(pair{left_horizontal_matrix, worth(left_horizontal_matrix)});

        problem_state down_vertical_matrix;
        down_vertical_matrix.emplace_back(vector<int>{matrix[0][0], matrix[1][1], matrix[0][2]});
        down_vertical_matrix.emplace_back(vector<int>{matrix[1][0], matrix[0][1], matrix[1][2]});
        down_vertical_matrix.emplace_back(vector<int>(matrix[2]));
        available_nodes.emplace_back(pair{down_vertical_matrix, worth(down_vertical_matrix)});
    } else if (matrix[0][2] == 0) {
        problem_state left_horizontal_matrix;
        left_horizontal_matrix.emplace_back(vector<int>{matrix[0][0], matrix[0][2], matrix[0][1]});
        left_horizontal_matrix.emplace_back(vector<int>(matrix[1]));
        left_horizontal_matrix.emplace_back(vector<int>(matrix[2]));
        available_nodes.emplace_back(pair{left_horizontal_matrix, worth(left_horizontal_matrix)});

        problem_state down_vertical_matrix;
        down_vertical_matrix.emplace_back(vector<int>{matrix[0][0], matrix[0][1], matrix[1][2]});
        down_vertical_matrix.emplace_back(vector<int>{matrix[1][0], matrix[1][1], matrix[0][2]});
        down_vertical_matrix.emplace_back(vector<int>(matrix[2]));
        available_nodes.emplace_back(pair{down_vertical_matrix, worth(down_vertical_matrix)});
    } else if (matrix[1][0] == 0) {
        problem_state up_horizontal_matrix;
        up_horizontal_matrix.emplace_back(vector<int>{matrix[1][0], matrix[0][1], matrix[0][2]});
        up_horizontal_matrix.emplace_back(vector<int>{matrix[0][0], matrix[1][1], matrix[1][2]});
        up_horizontal_matrix.emplace_back(vector<int>(matrix[2]));
        available_nodes.emplace_back(pair{up_horizontal_matrix, worth(up_horizontal_matrix)});

        problem_state right_horizontal_matrix;
        right_horizontal_matrix.emplace_back(vector<int>(matrix[0]));
        right_horizontal_matrix.emplace_back(vector<int>({matrix[1][1], matrix[1][0], matrix[1][2]}));
        right_horizontal_matrix.emplace_back(vector<int>(matrix[2]));
        available_nodes.emplace_back(pair{right_horizontal_matrix, worth(right_horizontal_matrix)});

        problem_state down_vertical_matrix;
        down_vertical_matrix.emplace_back(vector<int>(matrix[0]));
        down_vertical_matrix.emplace_back(vector<int>{matrix[2][0], matrix[1][1], matrix[1][2]});
        down_vertical_matrix.emplace_back(vector<int>{matrix[1][0], matrix[2][1], matrix[2][2]});
        available_nodes.emplace_back(pair{down_vertical_matrix, worth(down_vertical_matrix)});
    } else if (matrix[1][1] == 0) {
        problem_state up_horizontal_matrix;
        up_horizontal_matrix.emplace_back(vector<int>{matrix[0][0], matrix[1][1], matrix[0][2]});
        up_horizontal_matrix.emplace_back(vector<int>{matrix[1][0], matrix[0][1], matrix[1][2]});
        up_horizontal_matrix.emplace_back(vector<int>(matrix[2]));
        available_nodes.emplace_back(pair{up_horizontal_matrix, worth(up_horizontal_matrix)});

        problem_state left_horizontal_matrix;
        left_horizontal_matrix.emplace_back(vector<int>(matrix[0]));
        left_horizontal_matrix.emplace_back(vector<int>({matrix[1][1], matrix[1][0], matrix[1][2]}));
        left_horizontal_matrix.emplace_back(vector<int>(matrix[2]));
        available_nodes.emplace_back(pair{left_horizontal_matrix, worth(left_horizontal_matrix)});

        problem_state right_horizontal_matrix;
        right_horizontal_matrix.emplace_back(vector<int>(matrix[0]));
        right_horizontal_matrix.emplace_back(vector<int>({matrix[1][0], matrix[1][2], matrix[1][1]}));
        right_horizontal_matrix.emplace_back(vector<int>(matrix[2]));
        available_nodes.emplace_back(pair{right_horizontal_matrix, worth(right_horizontal_matrix)});

        problem_state down_vertical_matrix;
        down_vertical_matrix.emplace_back(vector<int>(matrix[0]));
        down_vertical_matrix.emplace_back(vector<int>{matrix[1][0], matrix[2][1], matrix[1][2]});
        down_vertical_matrix.emplace_back(vector<int>{matrix[2][0], matrix[1][1], matrix[2][2]});
        available_nodes.emplace_back(pair{down_vertical_matrix, worth(down_vertical_matrix)});
    } else if (matrix[1][2] == 0) {
        problem_state up_horizontal_matrix;
        up_horizontal_matrix.emplace_back(vector<int>{matrix[0][0], matrix[0][1], matrix[1][2]});
        up_horizontal_matrix.emplace_back(vector<int>{matrix[1][0], matrix[1][1], matrix[0][2]});
        up_horizontal_matrix.emplace_back(vector<int>(matrix[2]));
        available_nodes.emplace_back(pair{up_horizontal_matrix, worth(up_horizontal_matrix)});

        problem_state left_horizontal_matrix;
        left_horizontal_matrix.emplace_back(vector<int>(matrix[0]));
        left_horizontal_matrix.emplace_back(vector<int>({matrix[1][0], matrix[1][2], matrix[1][1]}));
        left_horizontal_matrix.emplace_back(vector<int>(matrix[2]));
        available_nodes.emplace_back(pair{left_horizontal_matrix, worth(left_horizontal_matrix)});

        problem_state down_vertical_matrix;
        down_vertical_matrix.emplace_back(vector<int>(matrix[0]));
        down_vertical_matrix.emplace_back(vector<int>{matrix[1][0], matrix[1][1], matrix[2][2]});
        down_vertical_matrix.emplace_back(vector<int>{matrix[2][0], matrix[2][1], matrix[1][2]});
        available_nodes.emplace_back(pair{down_vertical_matrix, worth(down_vertical_matrix)});
    } else if (matrix[2][0] == 0) {
        problem_state up_horizontal_matrix;
        up_horizontal_matrix.emplace_back(vector<int>(matrix[0]));
        up_horizontal_matrix.emplace_back(vector<int>{matrix[2][0], matrix[1][1], matrix[1][2]});
        up_horizontal_matrix.emplace_back(vector<int>{matrix[1][0], matrix[2][1], matrix[2][2]});
        available_nodes.emplace_back(pair{up_horizontal_matrix, worth(up_horizontal_matrix)});

        problem_state right_horizontal_matrix;
        right_horizontal_matrix.emplace_back(vector<int>(matrix[0]));
        right_horizontal_matrix.emplace_back(vector<int>(matrix[1]));
        right_horizontal_matrix.emplace_back(vector<int>({matrix[2][1], matrix[2][0], matrix[2][2]}));
        available_nodes.emplace_back(pair{right_horizontal_matrix, worth(right_horizontal_matrix)});
    } else if (matrix[2][1] == 0) {
        problem_state up_horizontal_matrix;
        up_horizontal_matrix.emplace_back(vector<int>(matrix[0]));
        up_horizontal_matrix.emplace_back(vector<int>{matrix[1][0], matrix[2][1], matrix[1][2]});
        up_horizontal_matrix.emplace_back(vector<int>{matrix[2][0], matrix[1][1], matrix[2][2]});
        available_nodes.emplace_back(pair{up_horizontal_matrix, worth(up_horizontal_matrix)});

        problem_state left_horizontal_matrix;
        left_horizontal_matrix.emplace_back(vector<int>(matrix[0]));
        left_horizontal_matrix.emplace_back(vector<int>(matrix[1]));
        left_horizontal_matrix.emplace_back(vector<int>({matrix[2][1], matrix[2][0], matrix[2][2]}));
        available_nodes.emplace_back(pair{left_horizontal_matrix, worth(left_horizontal_matrix)});

        problem_state right_vertical_matrix;
        right_vertical_matrix.emplace_back(vector<int>(matrix[0]));
        right_vertical_matrix.emplace_back(vector<int>(matrix[1]));
        right_vertical_matrix.emplace_back(vector<int>{matrix[2][0], matrix[2][2], matrix[2][1]});
        available_nodes.emplace_back(pair{right_vertical_matrix, worth(right_vertical_matrix)});
    } else if (matrix[2][2] == 0) {
        problem_state up_horizontal_matrix;
        up_horizontal_matrix.emplace_back(vector<int>(matrix[0]));
        up_horizontal_matrix.emplace_back(vector<int>{matrix[1][0], matrix[1][1], matrix[2][2]});
        up_horizontal_matrix.emplace_back(vector<int>{matrix[2][0], matrix[2][1], matrix[1][2]});
        available_nodes.emplace_back(pair{up_horizontal_matrix, worth(up_horizontal_matrix)});

        problem_state left_horizontal_matrix;
        left_horizontal_matrix.emplace_back(vector<int>(matrix[0]));
        left_horizontal_matrix.emplace_back(vector<int>(matrix[1]));
        left_horizontal_matrix.emplace_back(vector<int>({matrix[2][0], matrix[2][2], matrix[2][1]}));
        available_nodes.emplace_back(pair{left_horizontal_matrix, worth(left_horizontal_matrix)});
    }

    sort(available_nodes.begin(), available_nodes.end(), problem_comparator);

    for (problem_state_with_worth s_with_worth: available_nodes) {
        auto s = s_with_worth.first;
        if (!m[s]) {
            bool found = rbfs(s);
            if (found) {
                return true;
            }
        }
    }
    cout << "No solution found for this path, trying again" << endl;
    return false;
}

int main() {
    printf("Having %d^2 area\n", n);
    problem_state matrix;
    matrix.emplace_back(vector<int>{2, 8, 3});
    matrix.emplace_back(vector<int>{1, 6, 4});
    matrix.emplace_back(vector<int>{7, 0, 5});
    rbfs(matrix);
    return 0;
}
