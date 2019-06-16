#include <math.h>
#include <stdio.h>
#include <time.h>
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
    long long testNumber, Count = 0;
    clock_t begin, end;
    printf("Please input a number to test(required > 0): ");
    scanf("%lld", &testNumber);
    begin = clock();
    for (long long i = 1; i <= testNumber; i++)
    {
        Count += isPrime(i);
    }
    end = clock();
    printf("Result: testNumber: %lld,thread: %d, Primes Count: %lld, time: %0.6lfs\n", testNumber, 1, Count, (double)(end - begin) / CLOCKS_PER_SEC);
    return 0;
}