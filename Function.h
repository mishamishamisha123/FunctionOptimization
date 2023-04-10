//
// Created by misha on 17.11.2021.
//

#ifndef BIGPROJECTFUNCOPTIMIZE_FUNCTION_H
#define BIGPROJECTFUNCOPTIMIZE_FUNCTION_H

class Function {
    int dim = 4;
public:
    virtual double eval(double x, double y, double z, double w) = 0;
    double derivative(double x, double y, double z, double w, double eps = 1e-5);
    double derivative2(double x, double y, double z, double w, int i, int j, double eps = 1e-5);
    int getDim() const;
    Function();
};

class Func2d : public Function {
public:
    double eval(double x, double y, double z, double w) override;
    Func2d();
};

class Func2d1 : public Function {
public:
    Func2d1();
    double eval(double x, double y, double z, double w) override;
};

#endif //BIGPROJECTFUNCOPTIMIZE_FUNCTION_H
