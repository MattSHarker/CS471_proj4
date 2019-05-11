
/**
 * @file functions.cpp
 * @author Matthew Harker
 * @brief   This file contains the various functions being
 *          used to test optimization
 * 
 * @version 1.0
 * @date 2019-04-05
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <cmath>

#include "functions.h"

using namespace std;

// #1
/**
 * @brief Schwefel's Function.
 * 
 * @param vec       The vector of values the function will process.
 * @param n         The size of the vector.
 * @return double    The result of the function.
 */
double schwefel(double* vec, int n)
{
    double sum = (418.9829 * n);

    for (int i = 0; i < n; ++i)
        sum -= (-1 * vec[i]) * sin(sqrt(std::abs(vec[i])));

    return sum;
}


// #2  1st De Jong's function
/**
 * @brief De Jong's first function.
 * 
 * @param vec       The vector of values the function will process.
 * @param n         The size of the vector.
 * @return double    The result of the function.
 */
double dejong(double* vec, int n)
{
    double sum = 0.0;

    for (int i = 0; i < n; ++i)
    {
        sum += pow(vec[i], 2.0);
    }

    return sum;
}


// #3
/**
 * @brief Rosenbrok's function.
 * 
 * @param vec       The vector of values the function will process.
 * @param n         The size of the vector.
 * @return double   The result of the function.
 */
double rosenbrok(double* vec, int n)
{
    double sum = 0.0;

    for (int i = 0; i < n-1; ++i)
    {
        sum += 100 * pow(pow(vec[i], 2.0) - vec[i+1], 2.0) + pow(1 - vec[i], 2.0);
    }

    return sum;
}


// #4
/**
 * @brief Rastrigin's function.
 * 
 * @param vec       The vector of values the function will process.
 * @param n         The size of the vector.
 * @return double   The result of the function.
 */
double rastrigin(double* vec, int n)
{
    double sum = 0.0;

    for (int i = 0; i < n; ++i)
    {
        sum += pow(vec[i], 2.0) - (10 * cos(2 * M_PI * vec[i]));
    }

    return 10.0 * n * sum;
}


// #5
/**
 * @brief Griewank's function.
 * 
 * @param vec       The vector of values the function will process.
 * @param n         The size of the vector.
 * @return double   The result of the function.
 */
double griewank(double* vec, int n)
{
    double sum = 0.0;
    double product = 1.0;

    for (int i = 0; i < n; ++i)
    {
        sum += pow(vec[i], 2.0) / 4000.0;
        product *= cos(vec[i] / sqrt(i+1));
    }

    return 1.0 + sum - product;
}


// #6
/**
 * @brief Sine Envelope Sine Wave function.
 * 
 * @param vec       The vector of values the function will process.
 * @param n         The size of the vector.
 * @return double   The result of the function.
 */
double sinEnvlSinWave(double* vec, int n)
{
    double sum = 0.0;
    double temp;
    
    for (int i = 0; i < n-1; ++i)
    {
        temp = pow(sin(pow(vec[i], 2.0) + pow(vec[i+1], 2.0) - 0.5), 2.0);
        temp *= pow((1.0 + 0.001*(pow(vec[i], 2.0) + pow(vec[i+1], 2.0))), -2.0);
        sum -= 0.5 + temp;
    }

    return sum;
}


// #7
/**
 * @brief Stretched V Sine Wave function.
 * 
 * @param vec       The vector of values the function will process.
 * @param n         The size of the vector.
 * @return double   The result of the function.
 */
double stretchVSinWave(double* vec, int n)
{
    double sum = 0.0;
    double temp;

    for (int i = 0; i < n-1; ++i)
    {
        temp = pow(pow(vec[i], 2.0) + pow(vec[i+1], 2.0), 0.25);
        temp *= sin(pow(50 * pow(pow(vec[i], 2.0) + pow(vec[i+1], 2.0), 0.1), 2.0));
        sum += temp + 1.0;
    }

    return sum;
}


// #8
/**
 * @brief Ackley's first function.
 * 
 * @param vec       The vector of values the function will process.
 * @param n         The size of the vector.
 * @return double   The result of the function.
 */
double ackleyOne(double* vec, int n)
{
    double sum = 0.0;
    double temp;

    for (int i = 0; i < n-1; ++i)
    {
        temp = 1/(exp(0.2)) * sqrt(pow(vec[i], 2.0) + pow(vec[i+1], 2.0));
        temp += 3*(cos(2 * vec[i]) + sin(2*vec[i+1]));
        sum += temp;
    }

    return sum;
}


// #9
/**
 * @brief Ackley's second function.
 * 
 * @param vec       The vector of values the function will process.
 * @param n         The size of the vector.
 * @return double   The result of the function.
 */
double ackleyTwo(double* vec, int n)
{
    double sum = 0.0;
    double temp;

    for (int i = 0; i < n-1;++i)
    {
        temp = -1*(20/exp(pow(0.5*(pow(vec[i], 2.0) + pow(vec[i+1], 2.0)), 0.2)));
        temp -= exp(0.5 *(cos(2*M_PI*vec[i])+cos(2*M_PI*vec[i+1])));
        sum += temp + 20 + exp(1.0);
    }

    return sum;
}


// #10
/**
 * @brief Eggholder function.
 * 
 * @param vec       The vector of values the function will process.
 * @param n         The size of the vector.
 * @return double   The result of the function.
 */
double eggholder(double* vec, int n)
{
    double sum = 0.0;
    double temp;

    for (int i = 0; i < n-1; ++i)
    {
        temp = -1*(vec[i]) * sin(sqrt(std::abs(vec[i] - vec[i+1] - 47)));
        temp -= (vec[i+1] + 47) * sin(sqrt(std::abs(vec[i+1] + 47 + (vec[i]*0.5))));
        sum += temp;
    }

    return sum;
}


// #11
/**
 * @brief Rana's function.
 * 
 * @param vec       The vector of values the function will process.
 * @param n         The size of the vector.
 * @return double   The result of the function.
 */
double rana(double* vec, int n)
{
    double sum = 0.0;
    double temp;

    for (int i = 0; i < n-1;++i)
    {
        temp = vec[i] * sin(sqrt(std::abs(vec[i+1] - vec[i] + 1)))
                * cos(sqrt(std::abs(vec[i+1] + vec[i] + 1)));

        temp += (vec[i+1] + 1) * cos(sqrt(std::abs(vec[i+1] - vec[i] +1)))
                * sin(sqrt(std::abs(vec[i+1] + vec[i] + 1)));
        
        sum += temp;
    }

    return sum;
}


// #12
/**
 * @brief Pathological function.
 * 
 * @param vec       The vector of values the function will process.
 * @param n         The size of the vector.
 * @return double   The result of the function.
 */
double pathological(double* vec, int n)
{
    double sum = 0.0;
    double temp;

    for (int i = 0; i < n-1; ++i)
    {
        temp = sin(pow(sqrt(100*pow(vec[i] + pow(vec[i+1], 2.0), 2.0)) , 2.0)) - 0.5;
        temp /= 1 + 0.001*pow(pow(vec[i], 2.0) - (2*vec[i]) * vec[i+1] + pow(vec[i+1], 2.0), 2.0);
        sum += 0.5 + temp;
    }

    return sum;
}


// #13
/**
 * @brief Machalewicz's function.
 * 
 * @param vec       The vector of values the function will process.
 * @param n         The size of the vector.
 * @return double   The result of the function.
 */
double michalewicz(double* vec, int n)
{
    double sum = 0.0;

    for (int i = 0; i < n; ++i)
    {
        sum -= sin(vec[i]) * pow(sin(((i+1) * pow(vec[i], 2.0))/M_PI), 20.0);
    }

    return sum;
}


// #14
/**
 * @brief Master's Cosine Wave function.
 * 
 * @param vec       The vector of values the function will process.
 * @param n         The size of the vector.
 * @return double   The result of the function.
 */
double mastersCosWave(double* vec, int n)
{
    double sum = 0.0;
    double temp;

    for (int i = 0; i < n-1; ++i)
    {
        temp = exp(-0.125 * (pow(vec[i], 2.0) + pow(vec[i+1], 2.0) + (0.5*vec[i+1]*vec[i]) ));
        temp *= cos(pow( pow(vec[i], 2.0) + pow(vec[i+1], 2.0) + (0.5 * vec[i] * vec[i+1]), 0.25));
        sum -= temp;
    }

    return sum;
}


// #15
/**
 * @brief Quartic function.
 * 
 * @param vec       The vector of values the function will process.
 * @param n         The size of the vector.
 * @return double   The result of the function.
 */
double quartic(double* vec, int n)
{
    double sum = 0.0;

    for (int i = 0; i < n; ++i)
    {
        sum += ((i+1) * pow(vec[i], 4.0));
    }

    return sum;
}


/**
 * @brief W: A helper function for Levy's function.
 * 
 * @param vec       The vector of values the function will process.
 * @param i         The value of the vector to use
 * @return double   The result of the helper function.
 */
double w(double* vec, int n)
{
    return 1+((vec[n]-1)*0.25);
}


// #16
/**
 * @brief Levy's function.
 * 
 * @param vec       The vector of values the function will process.
 * @param n         The size of the vector.
 * @return double   The result of the function.
 */

double levy(double* vec, int n)
{
    double sum = pow(sin(M_PI * w(vec, 0)), 2.0);
    double temp;

    for (int i = 0; i < n-1; ++i)
    {
        temp = pow(w(vec, i)-1 , 2.0) * (1+10*pow(sin(M_PI*w(vec, 1)+1), 2.0));
        temp += pow(w(vec, n-1)-1, 2.0) * (1 + pow(sin(2*M_PI*w(vec, n-1)), 2.0));
        sum += temp;
    }

    return sum;
}


// #17
/**
 * @brief Step function.
 * 
 * @param vec       The vector of values the function will process.
 * @param n         The size of the vector.
 * @return double   The result of the function.
 */
double step(double* vec, int n)
{
    double sum = 0.0;

    for (int i = 0; i < n; ++i)
    {
        sum += pow(std::abs(vec[i]) + 0.5, 2.0);
    }

    return sum;
}


// #18
/**
 * @brief Alpine function.
 * 
 * @param vec       The vector of values the function will process.
 * @param n         The size of the vector.
 * @return double   The result of the function.
 */
double alpine(double* vec, int n)
{
    double sum = 0.0;

    for (int i = 0; i < n; ++i)
    {
        sum += std::abs(vec[i] * sin(vec[i]) + (0.1 * vec[i]));
    }

    return sum;
}
