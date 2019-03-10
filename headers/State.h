#include <utility>

#pragma once
#include <unordered_map>
#include <map>
#include <vector>

using namespace std;

class State {
public:
    State();
    State(vector<pair<int, pair<int, int>>> state, int n): state{std::move(state)}, size{n} {};
    ~State();

    vector<State*> expand();

    int getGapValue(int i, int j);
    void setValue(pair<int, int> position, int value);
    int getSize();
    vector<pair<int, pair<int, int>>>& getState();

private:
    vector<pair<int, pair<int, int>>> state;
    int size;

};
