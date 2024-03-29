#include <stdio.h>
#include "mpi.h"
#include "dmumps_c.h"

int main(int argc, char** argv){
    MUMPS_INT n = 5;
    MUMPS_INT8 nnz;
    int rank;
    DMUMPS_STRUC_C id;
    int NELT = 2;
    int NVAR = 6;
    int ELTPTR[3] = {1,4,7};
    int ELTVAR[6] = {1,2,3,3,4,5};
    double A_ELT[18] = {-1, 2, 1, 2, 1, 1, 3, 1, 1, 2, 1, 3, -1, 2, 2, 3, -1, 1};
    double rhs[5] = {0,0,0,0,0};
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    id.par = 1; id.sym = 0;
    id.job = -1;
    dmumps_c(&id);

    if(rank == 0){
        id.n = n; id.nelt = NELT; id.rhs = rhs; id.eltvar = ELTVAR;
        id.eltptr = ELTPTR; id.a_elt = A_ELT;
    }

    #define ICNTL(I) icntl[(I)-1]
    id.ICNTL(5) = 1; id.ICNTL(18) = 0;

    id.job = 6;

    if(id.infog[0] < 0){
        printf("(PROC %d) ERROR RETURN: \tINFOG(1)= %d\n\t\t\t\tINFOG(2)= %d\n", rank, id.infog[0],id.infog[1]);
    }

    id.job = -2;
    dmumps_c(&id);
    for(size_t c=0; c < n; c++){
        printf("%f\n",rhs[c]);
    }

    // if (rank == 0){
    //     printf("Hi");
    // }


    MPI_Finalize();
    return 0;
}