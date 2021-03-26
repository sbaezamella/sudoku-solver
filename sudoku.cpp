#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include <string>
#include <array>

#define N 9

using namespace std;

class State {
public:
    array<array<int, N>, N> board;

    friend ostream& operator<<(ostream& os, const State& s) {
        for (int x = 0; x < N; x++) {
            if (x == 3 || x == 6) {
                os << "-------------------" << endl;
            }
            for (int y = 0; y < N; y++) {
                os << s.board[x][y] << " ";
                if (y == 2 || y == 5) {
                    os << "|";
                }
            }
            os << '\n';
        }
        os << '\n';
        return os;
    }
};

class Action {
public:
    int col, row, value;
};

bool is_valid_state(State &state, int x, int y, int n) {
    int i, j, x0, y0;

    for (i = 0; i < N; i++) {
        if (state.board[x][i] == n) return false;
        if (state.board[i][y] == n) return false;
    }

    x0 = (x / 3) * 3;
    y0 = (y / 3) * 3;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (state.board[x0+i][y0+j] == n) return false;          
        }
    }

    return true;
}

State transition(State &state, Action &action) {
    State new_state = state;
    new_state.board[action.col][action.row] = action.value;
    return new_state;
}

list<Action> get_actions(State &state) {
    int x, y, n;
    list<Action> actions;

    for (x = 0; x < N; x++) {
        for (y = 0; y < N; y++) {
            if (state.board[x][y] == 0) {
                for (n = 1; n < 10; n++) {
                    if (is_valid_state(state, x, y, n)) {
                        Action action;
                        action.col = x;
                        action.row = y;
                        action.value = n;
                        actions.push_back(action);
                    }
                }
                return actions;
            }
        }
    }
    return actions;
}

bool is_final_state(State &state) {
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            if (state.board[x][y] == 0) return false;
        }
    }
    return true;
}

State DFS_solve(State &initial) {
    stack<State> S;
    S.push(initial);

    while (!S.empty()) {
        State state = S.top();        
        S.pop();
        
        if (is_final_state(state)) {
            return state;
        }

        list<Action> actions = get_actions(state);

        for (Action a : actions) {
            State result = transition(state, a);
            S.push(result);
        }
    }
}

int main() {
    State state;
    state.board = {{
        {5, 0, 0, 9, 0, 0, 0, 0, 6},
        {0, 8, 6, 1, 0, 0, 0, 0, 0},
        {3, 0, 0, 0, 0, 0, 0, 7, 0},
        {0, 0, 8, 2, 0, 0, 4, 0, 0},
        {0, 2, 0, 3, 0, 8, 0, 6, 0},
        {0, 0, 5, 0, 0, 6, 7, 0, 0},
        {0, 9, 0, 0, 0, 0, 0, 0, 5},
        {0, 0, 0, 0, 0, 1, 6, 3, 0},
        {7, 0, 0, 0, 0, 2, 0, 0, 8}}};

    // fstream sudoku_file;
    // sudoku_file.open("sudoku.txt", ios::in);

    // if (sudoku_file.is_open()) {
    //     string line;
    //     int line_number = 0;
    //     int x, y;
    //     while(getline(sudoku_file, line)){
    //         if (line_number % 10 != 0) {

    //             x = (line_number % 10) - 1;
    //             for (int i = 0; i < line.size(); i++) {
    //                 y = i;
    //                 state.board[x][y] = line[i] - '0';
    //             }
    //             cout << endl;
    //         } 

    //         if ((line_number % 10 == 0) && line_number > 0) {
    //             state.show();
    //             // State final_state = DFS_solve(state);
    //             // final_state.show();
    //         }
            
    //         line_number++;
    //     }
    //     sudoku_file.close();

    // }


    cout << "Estado inicial: " << endl;
    cout << state;

    State final_state = DFS_solve(state);

    cout << "Resultado final: " << endl;
    cout << final_state;

    return 0;
}
