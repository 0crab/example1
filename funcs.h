#ifndef EXAMPLE1_FUNCS_H
#define EXAMPLE1_FUNCS_H

using namespace std;

double get_rand_double(double L, double R){
    double ret = rand() * 1.0 / RAND_MAX * (R - L) + L;
    return  ret;
}

void generate_a_vector(vector<double> & a){
    for(size_t i =0; i< M-1 ;i++){
        a.push_back( rand() * 1.0 / RAND_MAX * (A_UPPER_BOUND - A_LOWER_BOUND) + A_LOWER_BOUND );
    }
    double tol = 0.0;
    for(auto & i : a) tol += i;
    a.push_back(1.0-tol);
}

inline bool  in_domain_of_definition(Individual & in,Domain_of_Definition & domain_of_definition){
    for(size_t i = 0; i < DIMENSION; i++ ){
        if(in.X[i] < domain_of_definition.first[i]  ||
                in.X[i] > domain_of_definition.second[i])
            return false;
    }
    return true;
}


//A is the new individual
bool individual_better(Individual & A , Individual & B, Domain_of_Definition & domain_of_definition){
    assert(in_domain_of_definition(B,domain_of_definition));
    if(!in_domain_of_definition(A,domain_of_definition)) return false;
    return A.adaptive_value > B.adaptive_value;
}

bool my_compare_func(const Individual & x ,const  Individual & y){
    //TODO  not take constrain condition into consideration
    return x.adaptive_value > y.adaptive_value;
}

void simply_sort(Population & p){
    sort(p.begin(),p.end(),my_compare_func);
}

//after sort
void  multiparent_hybridization_iteration(Population &p,Domain_of_Definition & domain_of_definition){
    assert(M < POPULATION_QUANTITY);
    vector<size_t> parent_index_v;
    vector<double> a_v;
    for(size_t i = 0; i < M; i++) {
        parent_index_v.push_back(rand() % POPULATION_QUANTITY);
    }
    generate_a_vector(a_v);

    //cout<<"finish generate a "<<endl;
    Individual son;
    son.init_with_zero();
    for(size_t i = 0; i< M; i++) {
        son = son + p[parent_index_v[i]] * a_v[i];
    }
    son.cal_adaptive_value();

    //cout<<"finish generate son"<<endl;
    if(individual_better(son,p.back(),domain_of_definition)){
        p.back() = son;
    }

    simply_sort(p);
}

void elite_multiparent_hybridization_iteration(Population & p,Domain_of_Definition & domain_of_definition){

    vector<double> a_v;
    generate_a_vector(a_v);

    //cout<<"finish generate a "<<endl;
    Individual son;
    son.init_with_zero();
    for(size_t i = 0; i< M1; i++) {
        son = son + p[i] * a_v[i];
    }
    son.cal_adaptive_value();

    //cout<<"finish generate son"<<endl;
    if(individual_better(son,p.back(),domain_of_definition)){
        p.back() = son;
    }

    simply_sort(p);
}

Individual elite_multiparent_hybridization(Population & p,Domain_of_Definition & domain_of_definition){
    size_t round = 0;
    while( ++round < sub_gen && p.back().adaptive_value < p.begin()->adaptive_value){
        elite_multiparent_hybridization_iteration(p,domain_of_definition);
    }
   // cout<< "sub round: "<<round<<endl;
    return *p.begin();
}


inline double cal_euclidean_distance(Individual &x,Individual &y){
    double ans = 0.0;
    for(size_t i = 0; i < DIMENSION; i++)
        ans += (x.X[i] - y.X[i]) * (x.X[i] - y.X[i]);
    return sqrt(ans);
}

double generate_p_vector(Population & source_population, Population & p_list){
    bool finish = false;
    double e = Epsilon;
    while(!finish){
        Population tmp_pool;
        //randomly choose an individual
        tmp_pool.push_back(source_population[rand() % source_population.size()]);
        for(size_t i =0; i< source_population.size();i++){

            bool fit =true;
            for(size_t j =0; j < tmp_pool.size(); j++){
                if(cal_euclidean_distance(source_population[i],tmp_pool[j]) < e){
                    fit = false;
                    break;
                }
            }
            if(fit)
                tmp_pool.push_back(source_population[i]);
        }

        if(tmp_pool.size() >= P_MIN_NUM && tmp_pool.size() <= P_MAX_NUM){
                p_list.swap(tmp_pool);
                finish = true;
        }else if(tmp_pool.size() > P_MAX_NUM){
            e *= (1 + EXPAND_FACTOR);
        }else{
            e *= 1.0 / ( 1+ EXPAND_FACTOR);
        }
    }
    return e;
}



void show_info(Population p){
    for(size_t i =0; i < p.size() ; i++){
        cout <<i<<":\t"<<p[i].adaptive_value<<endl<<"-------------------------------X:";
        for(size_t j =0; j < DIMENSION; j++){
            cout<<setiosflags(ios::fixed)<<setprecision(8) <<p[i].X[j]<<"   ";
        }
        cout<<endl;
    }
}

#endif //EXAMPLE1_FUNCS_H
