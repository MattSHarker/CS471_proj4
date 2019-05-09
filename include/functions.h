
#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

using namespace std;

// 1 Schwefel's formula
double schwefel(double*, int);

// 2 De Jong's formula
double dejong(double*, int);

// 3 Rosenbrok
double rosenbrok(double*, int);

// 4 Rastrigin
double rastrigin(double*, int);

// 5 Griewank
double griewank(double*, int);

// 6 Sine Evelope Sine Wave
double sinEnvlSinWave(double*, int);

// 7 Stretched V Sine Wave
double stretchVSinWave(double*, int);

// 8 Ackley's One
double ackleyOne(double*, int);

// 9 Ackley's Two
double ackleyTwo(double*, int);

// 10 Egg Holder
double eggholder(double*, int);

// 11 Rana
double rana(double*, int);

// 12 Pathological
double pathological(double*, int);

// 13 Michalewicz
double michalewicz(double*, int);

// 14 Masters Cosine Wave
double mastersCosWave(double*, int);

// 15 Quartic
double quartic(double*, int);

// 16 Levy
double w(double*, int);  // helper for levy
double levy(double*, int);

// 17 Step
double step(double*, int);

// 18 Alpine
double alpine(double*, int);

#endif