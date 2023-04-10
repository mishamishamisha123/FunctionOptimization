//
// Created by misha on 17.11.2021.
//

#ifndef BIGPROJECTFUNCOPTIMIZE_AREA_H
#define BIGPROJECTFUNCOPTIMIZE_AREA_H

#include "vector"

class Area {
    std::vector<double> area;
public:
    unsigned long getDim();
    virtual std::vector<double> getArea();
    void setAria(std::vector<double> a);
};

class Area2d : public Area {
public:
    explicit Area2d(double x1 = -5, double x2 = 5, double x3 = -5, double x4 = 5);
};

class Area3d : public Area {
    std::vector<double> area = {-5, 5, -5, 5, -5, 5};
};

class Area4d : public Area {
    std::vector<double> area = {-5, 5, -5, 5, -5, 5, -5, 5};
};

#endif //BIGPROJECTFUNCOPTIMIZE_AREA_H
