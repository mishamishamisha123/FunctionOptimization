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
    int last_improve = 0;
    if (a->getDim() != dim){
        return 0;
    }
    current_point.reserve(dim);
    for (int i = 0; i < dim; ++i){
        current_point.push_back(a->getArea()[i * 2] + dis(generator) * (a->getArea()[i * 2 + 1] - a->getArea()[i * 2]));
    }
    std::cout << f->eval(points[points.size() - 1]) << endl;
    std::cout << f->eval(current_point) << endl;
    std::cout << f->derivative(points[points.size() - 1]) << endl;
    std::cout << f->derivative(current_point) << endl;

    while (!sc->stop(counter,
        points[points.size() - 1],
        points[points.size() - 1],
        1,
        1,
        1,
        last_improve)
    ) 
    {
        if (f->eval(points[points.size() - 1]) > f->eval(current_point)) {
            last_improve = 0;
            points.push_back(current_point);
            if (near) {
                delta_ *= alpha;
            }
            else {
                delta_ = delta;
            }
            std::cout << "counter = " << counter << ". Координаты: ";
            for (int i = 0; i < dim; ++i) {
                std::cout << current_point[i] << " ";
            }
            std::cout << " f = " << f->eval(current_point) << endl;
        }
        current_point.clear();
        if (dis(generator) > p) {
            for (int i = 0; i < dim; ++i) {
                current_point.push_back(
                    a->getArea()[i * 2] + dis(generator) * (a->getArea()[i * 2 + 1] - a->getArea()[i * 2]));
            }
            near = false;
        }
        else {
            vector<double> pts;
            double sum = 0;
            for (int i = 0; i < dim; ++i) {
                pts.push_back(dis(generator));
                sum += pow(pts[i], 2);
            }

            while (sum > 1) {
                sum = 0;
                pts.clear();
                for (int i = 0; i < dim; ++i) {
                    pts.push_back(dis(generator));
                    sum += pow(pts[i], 2);
                }
            }
            for (int i = 0; i < dim; ++i) {
                current_point.push_back(points[points.size() - 1][i] + pts[i] * delta_);
            }
            near = true;
        }
        counter++;
        last_improve++;
    }
    
    std::cout << "\n---------\nCounter = " << counter << endl;
    std::cout << "Points = " << points.size() << endl;
    std::cout << "Function val = " << f->eval(points[points.size() - 1]) << endl;
    return f->eval(points[points.size() - 1]);
}

/*
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
    cout << f->eval(points[points.size() - 1]) << endl;
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
*/

RandomSearch::RandomSearch(double p1, double delta1, double alpha1) : p(p1), delta(delta1), alpha(alpha1) {}

double Newton::optimize(Function *f, StopCrit *sc, Area *a, std::vector<double> start) {
    int counter = 0, dim = f->getDim();
    vector<vector<double>> points;
    if (a->getDim() != dim) {
        std::cout << "Dims error" << endl;
        std::cout << "a->getDim() " << a->getDim() << endl;
        std::cout << "f->getDim() " << dim << endl;
        return 0;
    }

    vector<double> current_point = start;
    points.push_back(start);
    do {
        current_point = nextPoint(current_point, f);
        points.push_back(current_point);
        counter++;
        std::cout << "counter = " << counter << ". Координаты: ";
        for (int i = 0; i < dim; ++i) {
            std::cout << current_point[i] << " ";
        }
        std::cout << " f = " << f->eval(current_point) << " grad = " << f->derivative(points[points.size() - 1]) << endl;
    } while (!sc->stop(counter,
        points[points.size() - 2],
        points[points.size() - 1],
        f->eval(points[points.size() - 2]),
        f->eval(points[points.size() - 1]),
        f->derivative(points[points.size() - 1]),
        1));
    
    std::cout << "\n---------\nCounter = " << counter << endl;
    std::cout << "Grad = " << f->derivative(points[points.size() - 1]) << endl;
    std::cout << "Points = " << points.size() << endl;
    std::cout << "Function val = " << f->eval(points[points.size() - 1]) << endl;
    return f->eval(points[points.size() - 1]);
}

std::vector<double> Newton::nextPoint(std::vector<double> a, Function *f) {
    vector<vector<double>> G(a.size(), vector<double>(a.size(), 0.0));
    vector<double> dx(a.size(), 0);

    for (int i = 0; i < a.size(); ++i){
        for (int j = 0; j < a.size(); ++j){
            G[i][j] = f->derivative2(a, i, j);
            G[j][i] = G[i][j];
        }
    }

    /*std::cout << "a : " << endl;
    for (int j = 0; j < a.size(); ++j) {
        std::cout << a[j] << " ";
    }
    std::cout << endl;

    for (int i = 0; i < a.size(); ++i) {
        std::cout << "\nG[" << i << "]: ";
        for (int j = 0; j < a.size(); ++j) {
            std::cout << G[i][j] << " ";
        }
    }
    */

    G = inverse_matrix(G);
    /*
    for (int i = 0; i < a.size(); ++i) {
        std::cout << "\nG[" << i << "]: ";
        for (int j = 0; j < a.size(); ++j) {
            std::cout << G[i][j] << " ";
        }
    }*/

    for (int i = 0; i < a.size(); ++i) {
        double tmp = 0;
        for (int j = 0; j < a.size(); ++j) {
            tmp += -G[i][j] * f->derivative(a, j);
        }
        dx[i] = tmp;
    }
    
    transform(a.begin(), a.end(), dx.begin(), a.begin(), plus<double>());
    return a;
    }

Newton::Newton() = default;

vector<vector<double>> Newton::inverse_matrix(vector<vector<double>> matrix) {
    int n = matrix.size();
    vector<vector<double>> aug(n, vector<double>(2 * n));

    // Создаем расширенную матрицу из исходной матрицы и единичной матрицы
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            aug[i][j] = matrix[i][j];
        }
        aug[i][n + i] = 1;
    }

    // Применяем элементарные преобразования строк до тех пор, пока левая часть не станет единичной матрицей
    for (int i = 0; i < n; i++) {
        if (aug[i][i] == 0) {
            // Если на диагонали ноль, меняем местами строки, чтобы взять ненулевой элемент
            for (int k = i + 1; k < n; k++) {
                if (aug[k][i] != 0) {
                    swap(aug[i], aug[k]);
                    break;
                }
            }
        }
        double pivot = aug[i][i];
        for (int j = i; j < 2 * n; j++) {
            // Делим всю строку на pivot, чтобы получить на диагонали единицу
            aug[i][j] /= pivot;
        }
        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = aug[k][i];
                for (int j = i; j < 2 * n; j++) {
                    // Вычитаем из k-й строки i-ю, умноженную на factor,
                    // чтобы получить в k-й строке ноль в i-м столбце
                    aug[k][j] -= factor * aug[i][j];
                }
            }
        }
    }

    // Извлекаем правую часть (обратную матрицу)
    vector<vector<double>> inv(n, vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inv[i][j] = aug[i][n + j];
        }
    }

    return inv;
}
