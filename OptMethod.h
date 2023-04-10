//
// Created by misha on 17.11.2021.
//

#ifndef BIGPROJECTFUNCOPTIMIZE_OPTMETHOD_H
#define BIGPROJECTFUNCOPTIMIZE_OPTMETHOD_H
#include "Function.h"
#include "Area.h"
#include "StopCrit.h"

class OptMethod {

public:
    virtual double optimize(Function *f, StopCrit *sc, Area *a, std::vector<double> start) = 0;
};

class RandomSearch : public OptMethod {
    double p{}, delta{}, alpha{};
public:
    explicit RandomSearch(double p1 = 0.7, double delta1 = 0.01, double alpha = 0.5);
    double optimize(Function *f, StopCrit *sc, Area *a, std::vector<double> start) override;
};

class Newton : public OptMethod {
    double p{}, delta{}, alpha{};
public:
    Newton();
    double optimize(Function *f, StopCrit *sc, Area *a, std::vector<double> start) override;
    double det(std::vector<std::vector<double>> a);
    std::vector<double> nextPoint(std::vector<double> a, Function *f);
};


#endif //BIGPROJECTFUNCOPTIMIZE_OPTMETHOD_H
