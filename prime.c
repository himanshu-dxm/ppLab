#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

int isPrime(int n) {
    for(int i=2;i<=n/2;i++) {
        if(n%i==0) return 0;
    }
    return 1;
}
void main() {
    int n=1000;
    int primes[100000];
    int x =2,i=0;
    double start = omp_get_wtime();
    #pragma omp parallel
    while(i<=n) {
        if(isPrime(x)) {
            primes[i]=x;
            /*
            The omp atomic directive allows access 
            of a specific memory location atomically. 
            It ensures that race conditions are avoided 
            through direct control of concurrent threads that 
            might read or write to or from the particular memory location
            */
            #pragma omp atomic
            i++;
        }
        #pragma omp atomic 
        x++;
    }
    double end = omp_get_wtime();
    printf("\nFor Parallel : ");
    printf("\n Execution time: %f",(end-start));

    start = omp_get_wtime();
    x=2;
    i=0;
    // #pragma omp parallel for
    while(i<=n) {
        if(isPrime(x)) {
            primes[i]=x;
            // #pragma omp atomic
            i++;
        }
        // #pragma omp atomic 
        x++;
    }
    end = omp_get_wtime();
    printf("\nFor Serial : ");
    printf("\n Execution time: %f",(end-start));
}