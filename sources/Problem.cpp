//
// Created by marian on 3/2/19.
//

#include "../headers/Problem.h"
#include <fstream>
#include <queue>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iostream>

using namespace std;

Problem::Problem() {
    readFromFile();
    generateRegions();
}

float Problem::heuristic(const State &state1, const State &state2) {
    return 0.0;
}

void Problem::readFromFile() {
    ifstream file = ifstream{"/home/marian/Documents/CS/AI/lab1_C++/data4.in"};
    int n, aux;

    file >> n;

    size = n;

    vector<pair<int, pair<int, int>>> states;

    for (int i = 0; i < n; i++) {
        table.emplace_back();
        for (int j = 0; j < n; j++) {
            file >> aux;
            if (aux == -1) {
                states.push_back({-1, {i, j}});
                solutionSize += 1;
            }
            table[i].push_back(aux);
        }
    }

    this->initialState = State{states, this->size};
    this->root_size = int(sqrt(this->size));

    file.close();
}

bool Problem::isSolution(State* state) {
    /**
     * Check if the current state represents a solution.
     * Iterate through the table and take the values from state when a -1 is found in the table.
     * A line/column must have the sum 1+2+...+9=45
     * for a solution to be valid, check if each sub-region contains each element once
     */
    if (state->getSize() != solutionSize) {
        return false;
    }

    // gaps = state

    int lineSum = 0, colSum = 0, regionSum = 0;

    // check the line and column sum
    for (int i = 0; i < size; i++) {

        for (int j = 0; j < size; j++) {
            lineSum += (table[i][j] != -1 ? table[i][j] : state->getGapValue(i, j));

            colSum += (table[j][i] != -1 ? table[j][i] : state->getGapValue(j, i));
        }

        if (lineSum != this->lineSum or colSum != this->lineSum) {
            return false;
        }

        lineSum = 0;
        colSum = 0;
    }

    // check all regions for duplicates
    for (int ir = regions[0]; ir < regions[root_size]; ir += root_size) {
        for (int jr = regions[0]; jr < regions[root_size]; jr += root_size) {
            for (int i = ir; i < ir + root_size; i++) {
                for (int j = jr; j < jr + root_size; j++) {
                    // i and j are indexes in a region
                    int value = (table[i][j] != -1 ? table[i][j] : state->getGapValue(i, j));
                    regionSum += value;
                }
            }
            if(regionSum != this->lineSum) {
                return false;
            }
            else {
                // print if found
                for (int i = ir; i < ir + root_size; i++) {
                    for (int j = jr; j < jr + root_size; j++) {
                        // i and j are indexes in a region
                        int value = (table[i][j] != -1 ? table[i][j] : state->getGapValue(i, j));
                        cout<<value<<" ";
                    }
                    cout<<endl;
                }
                cout<<endl<<endl;
            }
            regionSum = 0;
        }
    }

    return true;
}

void Problem::gbfs() {

}

bool Problem::bfs() {
    queue<State*> todo;
    todo.push(&initialState);

    bool found = false;
    State* current;
    int loops = 0;

    while (!found and !todo.empty()) {
        loops++;

        current = todo.front();
        todo.pop();

        if (isSolution(current)) {
            found = true;
            solution = *current;
            cout << "steps: " << loops << endl;
            cout<<"max size: " << loops*3 << " elements of size "<< sizeof(*current) << "B for a memory footprint of "<<sizeof(State)*loops*3/1000000<<"MB"<<endl;
        } else {
            vector<State*> expanded = current->expand();

            for (State* s : expanded) {
                todo.push(s);
            }
        }
    }
    return found;
}

vector<State> Problem::orderStates(vector<State> unordered) {

}

State Problem::getSolution() {
    return solution;
}

string Problem::getPrintable(State state) {
    string output;

    for (int i = 0; i < table.size(); i++) {
        for (int j = 0; j < table.size(); j++)
            output += to_string(table[i][j] == -1 ? state.getGapValue(i, j) : table[i][j]) + " ";
        output += "\n";
    }
    return output;
}

void Problem::generateRegions() {
    regions.push_back(0);

    for (int i = 1; i < int(sqrt(size)) + 1; i++) {
        regions.push_back(i * this->root_size - 1);
    }

    for (int i = 1; i <= size; i++) {
        lineSum += i;
    }
}
