#ifndef EXAMPLE1_DEF_H
#define EXAMPLE1_DEF_H
#include <vector>

#define DIMENSION 2

#if (DIMENSION == 1)
#define q 3

#define N 100
#define M 10

#define global_gen 2000
#define sub_gen 5000

#define P_MAX_NUM 5
#define P_MIN_NUM 1


#define A_LOWER_BOUND -0.5
#define A_UPPER_BOUND 1.5

#define Epsilon 0.5
#define EXPAND_FACTOR 0.2

#define N1 100
#define M1 10

#define POPULATION_QUANTITY N


#define LOWER_BOUND -10.0
#define UPPER_BOUND 10.0

#elif (DIMENSION == 2)
#define q 9

#define N 100
#define M 10

#define global_gen 2000
#define sub_gen 5000

#define P_MAX_NUM 10
#define P_MIN_NUM 3

#define A_LOWER_BOUND -0.5
#define A_UPPER_BOUND 1.5

#define Epsilon 0.5
#define EXPAND_FACTOR 0.2

#define N1 100
#define M1 10

#define POPULATION_QUANTITY N


#define LOWER_BOUND -10.0
#define UPPER_BOUND 10.0


#elif (DIMENSION == 3)
#define q 27

#define N 100
#define M 10

#define global_gen 5000
#define sub_gen 20000

#define P_MAX_NUM 10
#define P_MIN_NUM 4

#define A_LOWER_BOUND -0.5
#define A_UPPER_BOUND 1.5

#define Epsilon 0.5
#define EXPAND_FACTOR 0.2

#define N1 100
#define M1 10

#define POPULATION_QUANTITY N


#define LOWER_BOUND -10.0
#define UPPER_BOUND 10.0

#elif (DIMENSION == 4)

#define q 81

#define N 250
#define M 10

#define global_gen 50000
#define sub_gen 100000

#define P_MAX_NUM 10
#define P_MIN_NUM 5

#define A_LOWER_BOUND -0.5
#define A_UPPER_BOUND 1.5

#define Epsilon 0.005
#define EXPAND_FACTOR 0.05

#define N1 150
#define M1 10

#define POPULATION_QUANTITY N


#define LOWER_BOUND -10.0
#define UPPER_BOUND 10.0

#endif

typedef  std::pair<std::vector<double>,std::vector<double>> Domain_of_Definition;

#endif //EXAMPLE1_DEF_H
