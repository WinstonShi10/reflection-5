docker run --rm -v ${PWD}:/tmp -w /tmp/Default rgreen13/alpine-mpi-boost make all

# use 1 through 10 nodes
docker run --rm -v ${PWD}:/tmp -w /tmp/Default rgreen13/alpine-mpi-boost mpiexec --allow-run-as-root -n 1 MPI
docker run --rm -v ${PWD}:/tmp -w /tmp/Default rgreen13/alpine-mpi-boost mpiexec --allow-run-as-root -n 2 MPI
docker run --rm -v ${PWD}:/tmp -w /tmp/Default rgreen13/alpine-mpi-boost mpiexec --allow-run-as-root -n 3 MPI
docker run --rm -v ${PWD}:/tmp -w /tmp/Default rgreen13/alpine-mpi-boost mpiexec --allow-run-as-root -n 4 MPI
docker run --rm -v ${PWD}:/tmp -w /tmp/Default rgreen13/alpine-mpi-boost mpiexec --allow-run-as-root -n 5 MPI
docker run --rm -v ${PWD}:/tmp -w /tmp/Default rgreen13/alpine-mpi-boost mpiexec --allow-run-as-root -n 6 MPI
docker run --rm -v ${PWD}:/tmp -w /tmp/Default rgreen13/alpine-mpi-boost mpiexec --allow-run-as-root -n 7 MPI
docker run --rm -v ${PWD}:/tmp -w /tmp/Default rgreen13/alpine-mpi-boost mpiexec --allow-run-as-root -n 8 MPI