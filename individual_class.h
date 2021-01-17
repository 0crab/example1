#ifndef EXAMPLE1_INDIVIDUAL_CLASS_H
#define EXAMPLE1_INDIVIDUAL_CLASS_H

#include <assert.h>
#include "def.h"

/*
 * 注意初始化步骤
 * */

using namespace  std;
class Individual {
public:
    Individual()  {};

    Individual &operator=(const Individual &other) noexcept {
        X.assign(other.X.begin(), other.X.end());
        adaptive_value = other.adaptive_value;
        return *this;
    }

    Individual operator+(const Individual & individual)  {
        assert(this->X.size() == individual.X.size());
        assert(this->X.size() == DIMENSION);
        Individual tmp;
        for(size_t i = 0;i < DIMENSION;i++) tmp.X.push_back(this->X[i] + individual.X[i]);
        tmp.cal_adaptive_value();
        return tmp;
    }

    Individual operator*(double a){
        Individual tmp;
        for(size_t i = 0;i < DIMENSION;i++) tmp.X.push_back(this->X[i] * a);
        tmp.cal_adaptive_value();
        return tmp;
    }

    void init_with_value(Domain_of_Definition & domain_of_definition){
        for(int i = 0; i < DIMENSION; i++)
            X.push_back(get_rand_double(domain_of_definition.first[i],domain_of_definition.second[i]));
        adaptive_value = adaptive_func(X);
    }

    void init_with_zero(){
        for(int i = 0; i < DIMENSION; i++)
            X.push_back(0.0);
    }

    void cal_adaptive_value(){ adaptive_value = adaptive_func(X);}

    double adaptive_value;

    std::vector<double> X;

private:
    double get_rand_double(double L, double R){ return rand() * 1.0 / RAND_MAX * (R - L) + L;}

    double adaptive_func(vector<double> & X);
};

double Individual::adaptive_func(vector<double> & X){
    assert(X.size() == DIMENSION);
    double ans = 1.0;
    for(size_t i = 0 ; i < X.size();i++){
        double t = 0.0;
        for(size_t j = 1; j <= 5;j++){
            t += j * cos( (j + 1) * X[i] + j);
        }
        ans *= t;
    }
    return -ans;
}

typedef vector<Individual> Population;

#endif //EXAMPLE1_INDIVIDUAL_CLASS_H
