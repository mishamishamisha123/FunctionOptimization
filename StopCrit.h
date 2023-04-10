//
// Created by misha on 17.11.2021.
//

#ifndef BIGPROJECTFUNCOPTIMIZE_STOPCRIT_H
#define BIGPROJECTFUNCOPTIMIZE_STOPCRIT_H

class StopCrit {
    int n = 10000;
    double eps = 1e-5;
    char type;
public:
    virtual bool stop(int n, std::vector<double> x1, std::vector<double> x2, double fx1, double fx2, double grad) = 0;
    int getN() const;
    double getEps() const;
    explicit StopCrit(int n = 100000, double eps = 1e-5, char t = '0');
};

class StopCritN : public StopCrit {
public:
    explicit StopCritN(int n = 100000);
    bool stop(int n, std::vector<double> x1, std::vector<double> x2, double fx1, double fx2, double grad) override;
};

class StopCritGrad : public StopCrit {
public:
    explicit StopCritGrad(int n = 100000, double eps = 1e-5, char t = '0');
    bool stop(int n, std::vector<double> x1, std::vector<double> x2, double fx1, double fx2, double grad) override;
};


#endif //BIGPROJECTFUNCOPTIMIZE_STOPCRIT_H
