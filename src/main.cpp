////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LIBRARIES
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
// DEPENDENCIES
#include <mpi.h>
#include <random>
#include "CStopWatch.h"

// RANDOM NUMBER GENERATOR
const int genMin = 1;
const int genMax = 100;
std::random_device rd;
std::mt19937 rng(rd());                          
std::uniform_int_distribution<int> uni(genMin, genMax);


// FUNCTION DECLARATION
std::vector<long long> GenerateVector(int size);


// Vector size
const int vectorSize = 200000;

// MAIN FUNCTION
int main(){
    // Tell MPI to start
    MPI_Init(NULL, NULL); 

    // Synchronize all processes and get the start time
    double totalTime;
    MPI_Barrier(MPI_COMM_WORLD);
    double start = MPI_Wtime();

    // Get process rank and size
    int myRank, mySize;
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &mySize);

    // Create vector to hold process data
    std::vector<long long> processVector((vectorSize / mySize) + 1);

    ////////////////////////////////////////////////////////////////////////////////
    /* GENERATE A RANDOM ARRAY OF NUMBERS ON THE ROOT PROCESS (PROCESS 0)         */
    ////////////////////////////////////////////////////////////////////////////////
    std::vector<long long> rootVector;
    if (myRank == 0) {
        rootVector = GenerateVector(vectorSize);
    }

    ////////////////////////////////////////////////////////////////////////////////
    /* SCATTER THE NUMBERS TO ALL PROCESSES, GIVING EACH PROCESS AN EQUAL AMOUNT  */
    /* OF NUMBERS                                                                 */
    ////////////////////////////////////////////////////////////////////////////////
    MPI_Scatter(rootVector.data(),          // Root process scatters data, non-root process ignore
                (vectorSize / mySize) + 1,  // Amount of elements per process, non-root process ignore
                MPI_LONG_LONG,                    // Type of one send vector element, non-root process ignore
                processVector.data(),       // Vector to store scattered data
                processVector.size(),       // Size of the receive vector
                MPI_LONG_LONG,                    // Type of one receive vector element
                0,                          // Rank of the root process, will output data to scatter
                MPI_COMM_WORLD);            // Communicator for the MPI_Scatter

    // Remove zeros and reduce vector size
    processVector.erase(std::remove(processVector.begin(), processVector.end(), 0), processVector.end());

    ////////////////////////////////////////////////////////////////////////////////
    /* EACH PROCESS COMPUTES THE AVERAGE OF THEIR SUBSET OF THE NUMBERS           */
    ////////////////////////////////////////////////////////////////////////////////
    long long mySum = std::accumulate(processVector.begin(), processVector.end(), 0);
    std::vector<long long> localAverageVector(1);
    localAverageVector[0] = mySum / processVector.size();

    // Initialize vector to store each processes average
    std::vector<long long> globalAverageVector(mySize);

    ////////////////////////////////////////////////////////////////////////////////
    /* GATHER ALL AVERAGES TO THE ROOT PROCESS. THE ROOT PROCESS THEN COMPUTES    */
    /* THE AVERGAGE OF THESE NUMBERS TO GET THE FINAL AVERAGE                     */
    ////////////////////////////////////////////////////////////////////////////////
    MPI_Gather(localAverageVector.data(), 
               1, 
               MPI_LONG_LONG,
               globalAverageVector.data(), 
               1, 
               MPI_LONG_LONG, 
               0, 
               MPI_COMM_WORLD);

    if (myRank == 0) {
        // Calculate sum of all processes averages
        long long globalSum     = std::accumulate(globalAverageVector.begin(), globalAverageVector.end(), 0);

        // Divided sum by numbe of processes to get average
        long long globalAverage = globalSum / globalAverageVector.size();

        ////////////////////////////////////////////////////////////////////////////////
        /* THE ROOT PROCESS OUTPUTS AVERAGE VALUE                                     */
        ////////////////////////////////////////////////////////////////////////////////
        std::cout << "The average for a vector of "<< vectorSize <<" of numbers between "<< genMin << " - " << genMax << " is " << globalAverage << "." << std::endl;
    }

    // Get the end time
    double end = MPI_Wtime();
    // Get elapsed time
    double elapsed = end - start;

    // Combine all process times to get total time
    MPI_Reduce(&elapsed, &totalTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    // Output total time once
    if (myRank == 0) {
        std::cout << mySize << " processes time to complete: " << totalTime << std::endl << std::endl;
    }


    // Tell MPI to end
    MPI_Finalize(); 

    return 0;
}


// FUNCTIONS
std::vector<long long> GenerateVector(int size) {
    std::vector<long long> tempVector(size);        // Create temporary vector
    for(int i = 0; i < size; i++) {                 // Go through vector
        tempVector[i] = uni(rng);                   // Fill vector with number from 0 to 1000
    }
    return tempVector;                              // Return vector
}