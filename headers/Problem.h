
#pragma once
#include "State.h"
#include <vector>
using namespace std;

class Problem {
public:
    Problem();
    bool bfs();
    void gbfs();
    State getSolution();
    string getPrintable(State state);
    void readFromFile();

private:
    static vector<State> orderStates(vector<State> unorderedStates);
    float heuristic(const State& state1, const State& state2);

    void generateRegions();
    bool isSolution(State* state);
    vector<vector<int>> table;
    int size;
    int solutionSize=0;

    int lineSum = 0;
    vector<int> regions;

    int root_size;
    State initialState;
    State solution;     // in this case solution is a state, may be a list of states or something else
};
