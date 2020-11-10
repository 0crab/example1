#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <vector>
#include <thread>
#include <mutex>
#include "def.h"
#include "individual_class.h"
#include "tracer.h"

using namespace std;

#include "funcs.h"

Population ans_pool;

mutex mtx;

void process_sub_module(size_t qid, Domain_of_Definition  sub_domain_of_definition){

    Population population (POPULATION_QUANTITY);

    //initialize population
    for(auto & i : population)
        i.init_with_value(sub_domain_of_definition);

    //show_info(population);

    simply_sort(population);
    for(size_t i = 0; i < global_gen;  i++){
        //cout << "i : "<< i <<endl;
        multiparent_hybridization_iteration(population ,sub_domain_of_definition);
    }

    //show_info(population);

    //divide sub search domain
    Population p_vector;
    double e = generate_p_vector(population,p_vector);
    simply_sort(p_vector);
    //show_info(p_vector);

    //generate Di
    size_t sub_domain_num = p_vector.size();
    vector<Population> D(sub_domain_num);
    for(size_t i = 0 ; i < sub_domain_num; i ++ ){
        double D_range = e * (1 + i / (sub_domain_num - 1) / 2);
        while(D[i].size() < N1){
            Individual in;
            in.init_with_value(sub_domain_of_definition);
            if(cal_euclidean_distance(p_vector[i],in) <= D_range){
                D[i].push_back(in);
            }
        }
        simply_sort(D[i]);
    }

    //each sub_domain_num already sorted
    Population final_p;
    for(size_t i = 0; i < sub_domain_num; i++){
        Individual partial_optimal_in = elite_multiparent_hybridization(D[i],sub_domain_of_definition);
        bool fit = true;
        for(size_t i = 0; i < final_p.size();i++){
            if(cal_euclidean_distance(final_p[i],partial_optimal_in) < 0.1){
                fit = false;
                break;
            }
        }
        if(fit){
            final_p.push_back(partial_optimal_in);
        }
    }

//    simply_sort(final_p);
//    cout<<" q : "<<qid<<endl;
//    show_info(final_p);
    mtx.lock();
    ans_pool.insert(ans_pool.begin(),final_p.begin(),final_p.end());
    mtx.unlock();

}


int main() {

    srand((unsigned int)time(NULL));

    vector<Domain_of_Definition> Ds(q);

    for(size_t i=0; i < q; i++){
        Domain_of_Definition tmp;
        for(size_t j = 0; j < DIMENSION ; j++){
            if(j == 0){
                tmp.first.push_back((UPPER_BOUND - LOWER_BOUND) / q  * i + LOWER_BOUND);
                tmp.second.push_back((UPPER_BOUND - LOWER_BOUND) / q  * (i + 1) + LOWER_BOUND);
            }else{
                tmp.first.push_back(LOWER_BOUND);
                tmp.second.push_back(UPPER_BOUND);
            }

        }
        Ds[i] = tmp;
    }



    Tracer t;
    t.startTime();
    vector<thread> threads;
    for(size_t i = 0; i < q; i++){
        threads.push_back(thread(process_sub_module,i ,Ds[i]));
    }
    for(auto & i : threads)
        i.join();
    double runtime = t.getRunTime() * 1.0 / 1000000;

    simply_sort(ans_pool);
    double max_value = ans_pool.begin()->adaptive_value;
    size_t index = 0;
    while(max_value - ans_pool[index].adaptive_value <= 10 ) index ++;
    ans_pool.erase(ans_pool.begin() + index,ans_pool.end());

    show_info(ans_pool);
    cout<<"runtime : "<<runtime<<"s"<<endl;

    //generate_p_vector(population,p_vector);

    return 0;
}
