
/**
 * @file    runFuncs.cpp
 * @author  Matthew Harker
 * @brief   Passes a solution vector through a function
 *          and returns the resulting value
 * 
 * @version 3.0
 * @date 2019-05-03
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <iostream>

#include "functions.h"
#include "runFuncs.h"

using namespace std;


/**
 * @brief Runs one solution vector through a function
 * 
 * @param solVec    The solution vector
 * @param size      The size of the vector
 * @param func      Which function to run the vector through
 * @return double   The resulting value
 */
double runSolution(double* solVec, const int size, const int func)
{
    // pass the vector through an algorithm and record it to matrix.results
    switch(func)
    {
        case 0:  return schwefel        (solVec, size);
        case 1:  return dejong          (solVec, size);
        case 2:  return rosenbrok       (solVec, size);
        case 3:  return rastrigin       (solVec, size);
        case 4:  return griewank        (solVec, size);
        case 5:  return sinEnvlSinWave  (solVec, size);
        case 6:  return stretchVSinWave (solVec, size);
        case 7:  return ackleyOne       (solVec, size);
        case 8:  return ackleyTwo       (solVec, size);
        case 9:  return eggholder       (solVec, size);
        case 10: return rana            (solVec, size);
        case 11: return pathological    (solVec, size);
        case 12: return michalewicz     (solVec, size);
        case 13: return mastersCosWave  (solVec, size);
        case 14: return quartic         (solVec, size);
        case 15: return levy            (solVec, size);
        case 16: return step            (solVec, size);
        case 17: return alpine          (solVec, size);
        default:
            cout << "Trying to access a function which does not exist\n";
            exit(EXIT_FAILURE);
    }
}
