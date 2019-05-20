
Matthew Harker
CS 471 - Optimization
Project 4
May 20, 2019

************** ABOUT ***************
This program will produce a series of values that are obtained by passing solution
vectors through three optimization functions: Particle Swarm, Firefly, and Harmony
Search.

************* PARAMETERS ***************
There are adjustable values for the algorithms, found in two different parameter files,
which are located in the parameters directory. The first file - functionParams/txt -
contains parameters that control aspects about the population. The two recommended value
to experiment with are the population size and number of experimentations, the first the
lines of the file. The second file - optimizationParams.txt - contains the values for the
constants the algorithms require. Any of these are allowed to be adjusted, and recommended 
ranges and value are provided as well.



******** BUILDING, RUNNING, AND CLEANING *************

How to generate the results:
    cd to the directory this readme is in
    $ ./build.sh
    $ ./run.sh

How to remove the build files:
    cd to the directory this readme is in
    $ ./clean.sh


*************** RESULTS ***************
The results will be printed to the results directory, in the appropriately labeled sub-directories.
Old results will be overwritten so if you want to keep old results, copy them to another directory.
