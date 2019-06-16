#include <stdio.h>
#include <math.h>
#include <mpi.h>
//test if a number is prime or not.
int isPrime(long long testNumber)
{
    int flag = 1;
    for (long long i = 2; i <= (long long)sqrt((double)testNumber * 1.0); i++)
    {
        if (testNumber % i == 0)
        {
            flag = 0;
            break;
        }
    }
    return flag;
}
int main(int argc, char *argv[])
{
    long long testNumber;
    int rank, size;
    long long partialCount, Count;
    double begin, end;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    partialCount = Count = 0;
    if (rank == 0)
    {
        printf("Please input a number to test(required > 0): ");
        scanf("%lld", &testNumber);
    }
    MPI_Bcast(&testNumber, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    begin = MPI_Wtime();
    for (long long i = rank + 1; i <= testNumber; i += size)
    {
        partialCount += isPrime(i);
    }
    MPI_Reduce(&partialCount, &Count, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();
    if (rank == 0)
    {
        printf("Result: testNumber: %lld,thread: %d, Primes Count: %lld, time: %0.6lfs\n", testNumber, size, Count, end - begin);
    }
    MPI_Finalize();
    return 0;
}