//
// Created by misha on 17.11.2021.
//
#include <vector>
#include "OptMethod.h"
#include <random>
#include "iostream"
using namespace std;

double RandomSearch::optimize(Function *f, StopCrit *sc, Area *a, std::vector<double> start) {
    int counter = 0, dim = f->getDim();
    vector<double> current_point;
    vector<vector<double>> points;
    double x, y, delta_ = delta;
    bool near = false;
    points.push_back(start);
    mt19937 generator (122);
    uniform_real_distribution<double> dis(0.0, 1.0);
    if (a->getDim() != dim){
        return 0;
    }
    current_point.reserve(dim);
    for (int i = 0; i < dim; ++i){
        current_point.push_back(a->getArea()[i * 2] + dis(generator) * (a->getArea()[i * 2 + 1] - a->getArea()[i * 2]));
    }
    cout << f->eval(points[points.size() - 1][0], points[points.size() - 1][1], 0, 0) << endl;
    cout << f->eval(current_point[0], current_point[1], 0, 0) << endl;
    cout << f->derivative(points[points.size() - 1][0], points[points.size() - 1][1], 0, 0) << endl;
    cout << f->derivative(current_point[0], current_point[1], 0, 0) << endl;
    while (!sc->stop(counter,
                     points[points.size() - 1],
                     current_point,
                     f->eval(points[points.size() - 1][0], points[points.size() - 1][1], 0, 0),
                     f->eval(current_point[0], current_point[1], 0, 0),
                     f->derivative(points[points.size() - 1][0], points[points.size() - 1][1], 0, 0)))
    {
        if (f->eval(points[points.size() - 1][0], points[points.size() - 1][1], 0, 0)
                > f->eval(current_point[0], current_point[1], 0, 0)) {
            points.push_back(current_point);
            if (near) {
                delta_ *= alpha;
            }
            else{
                delta_ = delta;
            }
            cout << "counter = " << counter << ": ";
            cout << "x = " << current_point[0] << ", y = " << current_point[1] <<
                ", f = " << f->eval(current_point[0], current_point[1], 0, 0) << endl;
        }
        current_point.clear();
        if (dis(generator) > p) {
            for (int i = 0; i < dim; ++i) {
                current_point.push_back(
                        a->getArea()[i * 2] + dis(generator) * (a->getArea()[i * 2 + 1] - a->getArea()[i * 2]));
            }
            near = false;
        }
        else{
            x = dis(generator);
            y = dis(generator);
            while (pow(x, 2) + pow(y, 2) > 1){
                x = dis(generator);
                y = dis(generator);
            }
            current_point.push_back(points[points.size() - 1][0] + x * delta_);
            current_point.push_back(points[points.size() - 1][1] + y * delta_);
            near = true;
        }
        counter++;
    }
    cout << "Counter = " << counter << endl;
    cout << "Points = " << points.size() << endl;
    cout << "Function val = " << f->eval(points[points.size() - 1][0], points[points.size() - 1][1], 0, 0) << endl;
    cout << "x = " << points[points.size() - 1][0] << endl;
    cout << "y = " << points[points.size() - 1][1] << endl;
    return f->eval(points[points.size() - 1][0], points[points.size() - 1][1], 0, 0);
}

RandomSearch::RandomSearch(double p1, double delta1, double alpha1) : p(p1), delta(delta1), alpha(alpha1) {}

double Newton::optimize(Function *f, StopCrit *sc, Area *a, std::vector<double> start) {
    return 0;
}

std::vector<double> Newton::nextPoint(std::vector<double> a, Function *f) {
    vector<vector<double>> G;
    G.reserve(a.size());
    for (int i = 0; i < a.size(); ++i){
        G[i].reserve(a.size());
    }
    for (int i = 0; i < a.size(); ++i){
        for (int j = 0; j < a.size(); ++j){
            G[i][j] = f->derivative2(a[0], a[1], a[2], a[3], i, j);
            G[j][i] = G[i][j];
        }
    }
}

Newton::Newton() = default;

double Newton::det(vector<vector<double>> a) {
    if (a.size() == 1) return a[0][0];
    double sum = 0;
    vector<vector<double>> arr;
    vector<double> m;
    int b = 1;
    for (int i = 0; i < a.size(); ++i){
        arr.clear();
        arr.reserve(a.size() - 1);
        m.reserve(a.size() - 1);
        for (int k = 0; k < a.size(); ++k) {
            for (int j = 0; j < a[i].size(); ++j) {
                if ((i != j) and (i != k))
                    m.push_back(a[k][j]);
            }
            arr.push_back(m);
        }
        sum += b * det(arr);
        b *= -1;
    }
    return sum;
};
