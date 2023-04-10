//
// Created by misha on 17.11.2021.
//

#include <vector>
#include "StopCrit.h"
#include <cmath>

bool StopCritN::stop(int n, std::vector<double> x1, std::vector<double> x2, double fx1, double fx2, double grad) {
    return this->getN() < n;
}

StopCritN::StopCritN(int n) : StopCrit(n, 0, 'n') {}

int StopCrit::getN() const {
    return n;
}

StopCrit::StopCrit(int n_, double eps_, char t) : eps(eps_), n(n_), type(t) {}

double StopCrit::getEps() const {
    return eps;
}

StopCritGrad::StopCritGrad(int n, double eps, char t) : StopCrit(0, eps, 'g') {}

bool StopCritGrad::stop(int n, std::vector<double> x1, std::vector<double> x2, double fx1, double fx2, double grad) {
    double sum = 0;
    for (int i = 0; i < std::min(x1.size(), x2.size()); ++i)
        sum += pow(x1[i] - x2[i], 2);
    return sum > pow(grad, 2);
}