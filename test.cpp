#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

#define VARIATE_BIT_NUM 20

#define M 10

#define SUM 1

int main(){
    srand((unsigned int) time(0));
    double a[M];
    bool success = false;
    size_t count = 0;
    while(!success){
        count ++;
        double pre_sum = 0.0;
        for(size_t i =0; i< M - 1;i++){
            a[i] = rand() * 1.0 / RAND_MAX * 2.0 +-0.5;
            pre_sum += a[i];
        }
        if(SUM - pre_sum > -0.5 && SUM - pre_sum < 1.5 ){
            a[M-1] = SUM -pre_sum;
            success = true;
        }
    }
    cout << "count :" << count<< endl;
    for(size_t i =0; i < M ; i++ ) cout << a[i]<<endl;


}