#include <iostream>
#include "OptMethod.h"

using namespace std;

int main() {

    OptMethod* om = new Newton();
    Function* func = new Func2d1();
    StopCrit* sc = new StopCritN(100); // Работает
    //StopCrit* sc = new StopCritGrow(); // Выдает ошибку "Требуется спецификатор типа"
    Area* area = new Area2d();
    vector<double> start = { 3, 3 };
    om->optimize(func, sc, area, start);

    return 0;
}
