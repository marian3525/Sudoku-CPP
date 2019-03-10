//
// Created by marian on 3/2/19.
//

#include <iostream>
#include "../headers/State.h"

State::State() {

}

int State::getGapValue(int i, int j) {
    for(pair<int, pair<int, int>> v : state)
        if(i==v.second.first && j == v.second.second)
            return v.first;
}

vector<State*> State::expand() {
    vector<State*> expanded;
    auto current = this->state;

    if(current.size() == size) {
        // nothing to expand, vector complete
        return expanded;
    }

    int pos = 0;
    while(current[pos].first != -1 and pos < current.size()) {
        pos++;
    }

    State* aux;

    for(int i=1; i<=size; i++) {
        // if likely to be used?
        current[pos].first = i;

        aux = new State{current, size};
        expanded.push_back(aux);
    }
    return expanded;
}

void State::setValue(pair<int, int> position, int value) {
    state.emplace_back(value, position);
}

int State::getSize() {
    int size = 0;

    for(pair<int, pair<int, int>> p : this->state) {
        if(p.first != -1) {
            size++;
        }
    }
    return size;
}

vector<pair<int, pair<int, int>>>& State::getState() {
    return this->state;
}

State::~State() {

}
