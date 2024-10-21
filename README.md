<h1> Reflection 05 , MPI I: Scatter and Gather </h1>

Winston Shi

<h2> Summary </h2>

Implement the following tasks using MPI Scatter and Gather:
Generate a random array of numbers on the root process (process 0).
Scatter the numbers to all processes, giving each process an equal amount of numbers.
Each process computes the average of their subset of the numbers.
Gather all averages to the root process. The root process then computes the average of these numbers to get the final average
The Root process outputs average value.
Analysis. Demonstrate results using 1 Processor Per Node across 1 to 10 Nodes using a vector of 200,000 random values for averaging. You must record the total time taken for each trial. Your final submission must include the appropriate analysis to compare raw MPI. All trials must be run 10 times and average values must be reported.

<h2> Table of Contents </h2>

[TOC]

## Key Notes & Code Snippet



## How to Run Locally

1. Clone Repository
```
git clone git@gitlab.com:Winston.Shi.BGSU/cs4170_fa2024_a01_shi.git reflection_05
```

2. Change directory
```
cd reflection_05
```

3. Run bash script
```
sh run.sh
```

run.sh: 
```
docker run --rm -v ${PWD}:/tmp -w /tmp/Default rgreen13/alpine-mpi-boost make all
docker run --rm -v ${PWD}:/tmp -w /tmp/Default rgreen13/alpine-mpi-boost mpiexec --allow-run-as-root -n X MPI
```
where `X` is the number of nodes

## How to Run on OSC

1. Login into Ohio Super Computer
```
ssh USERNAME@owens.osc.edu
```

2. Load the Git module
```
module load git
```

3. Clear the SSH_ASKPASS environment variable
```
unset SSH_ASKPASS
```

4. Clone Repository
```
git clone git@gitlab.com:Winston.Shi.BGSU/cs4170_fa2024_a01_shi.git reflection_05
```

5. Change directory to repository
```
cd reflection_05
```

6. Change directory to 'Default'
```
cd Default
```

7. Clean make
```
make clean
```

8. Load MPI Modules
```
module load boost
module load intel
```

9. Use make
```
make OSC
```

10. Submit Jobscript
```
qsub jobScript
```

## Speedup

<img src="Results/speedup.jpeg" alt="speedup">



## Efficiency

<img src="Results/efficiency.jpeg" alt="efficiency">



## Karp-Flatt Metric

<img src="Results/karp-flatt.jpeg" alt="karp-flatt">



## Reflection

How much time did you spend on this reflection? How much time did you spending coding? Writing? Testing? Analyzing?