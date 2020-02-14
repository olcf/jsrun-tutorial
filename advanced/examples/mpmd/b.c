#define _GNU_SOURCE
#include <stdio.h>
#include <mpi.h>
#include <sched.h>
 
int main(int argc, char * argv[])
{
   int rank, size;
   int hwthread;
   char node_id[MPI_MAX_PROCESSOR_NAME];
   int result_length;
 
   MPI_Init(&argc, &argv);

   MPI_Get_processor_name(node_id, &result_length);

   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
 
   hwthread = sched_getcpu();
 
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);

   printf("MPI rank %02d of %02d on HW Thread %03d of Node %s - (Code b)\n", rank, size, hwthread, node_id);
 
   MPI_Finalize();
 
   return 0;
}

