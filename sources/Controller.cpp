
#include "../headers/Controller.h"
#include <algorithm>
#include <queue>
#include <iostream>



string Controller::solveProblem(Mode mode) {
    if(problem.bfs())
        return problem.getPrintable(problem.getSolution());
    else
        return "No solution found, at" + problem.getPrintable(problem.getSolution());;
}

Controller::Controller() {
    problem = Problem{};
}
