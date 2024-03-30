// #include <stdio.h>
// #include "mpi.h"
// #include "dmumps_c.h"

// int main(int argc, char** argv){
//     MUMPS_INT n = 5;
//     MUMPS_INT8 nnz;
//     int rank;
//     DMUMPS_STRUC_C id;
//     int NELT = 2;
//     int NVAR = 6;
//     int ELTPTR[3] = {1,4,7};
//     int ELTVAR[6] = {1,2,3,3,4,5};
//     double A_ELT[18] = {-1, 2, 1, 2, 1, 1, 3, 1, 1, 2, 1, 3, -1, 2, 2, 3, -1, 1};
//     double rhs[5] = {0,0,0,0,0};
    
//     MPI_Init(&argc, &argv);
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);

//     id.par = 1; id.sym = 0;
//     id.job = -1;
//     dmumps_c(&id);

//     if(rank == 0){
//         id.n = n; id.nelt = NELT; id.rhs = rhs; id.eltvar = ELTVAR;
//         id.eltptr = ELTPTR; id.a_elt = A_ELT;
//     }

//     #define ICNTL(I) icntl[(I)-1]
//     id.ICNTL(5) = 1; id.ICNTL(18) = 0;

//     id.job = 6;

//     if(id.infog[0] < 0){
//         printf("(PROC %d) ERROR RETURN: \tINFOG(1)= %d\n\t\t\t\tINFOG(2)= %d\n", rank, id.infog[0],id.infog[1]);
//     }

//     id.job = -2;
//     dmumps_c(&id);
//     for(size_t c=0; c < n; c++){
//         printf("%f\n",rhs[c]);
//     }

//     // if (rank == 0){
//     //     printf("Hi");
//     // }


//     MPI_Finalize();
//     return 0;
// }


#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {
  // Initialisation
  int rank, size;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  int* sendbuf; int s;
  if (rank == 0){
    s = 1;
    sendbuf = new int[s];
    sendbuf[0] = 0; 
  }
  if (rank == 1){
    s = 2;
    sendbuf = new int[s];
    sendbuf[0] = 1; sendbuf[1] = 1;
  }
  if (rank == 2){
    s = 3;
    sendbuf = new int[s];
    sendbuf[0] = 2; sendbuf[1] = 2; sendbuf[2] = 2;
  }
  if (rank == 3){
    s = 4;
    sendbuf = new int[s];
    sendbuf[0] = 3; sendbuf[1] = 3; sendbuf[2] = 3; sendbuf[3] = 3;
  }
  int* recvbuf;
  if (rank == 0){
    recvbuf = new int[10];
  }
  int displs[4];
  if (rank == 0){
    displs[0] = 0; displs[1] = 1; displs[2] = 3; displs[3] = 6;
  }
  int recvcount[4];
  if (rank == 0){
    recvcount[0] = 1; recvcount[1] = 2; recvcount[2] = 3; recvcount[3] = 4;
  }

  MPI_Gatherv(sendbuf, s, MPI_INT, recvbuf, recvcount, displs, MPI_INT, 0, MPI_COMM_WORLD);
  // if(rank == 0){
  //   for(int i = 0; i < 10; i++){
  //     std::cout<<"Send buf:"<<recvbuf[i]<<"\n"<<"END\n"; 
  //   }
  // }

  if(rank == 0){
    for(int i = 0; i < 10; i++){
      std::cout<<recvbuf[i]<<"\n";
    }
  }

delete [] sendbuf;
if(rand == 0){
  delete [] recvbuf;
}

  // std::cout << "Hello world, from process #"<<rank << std::endl;
  
  // Finalisation
  MPI_Finalize();


  return 0;
}