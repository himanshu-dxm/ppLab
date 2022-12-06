#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

int fib(int n) {
    int a = 0, b = 1, c;
    #pragma omp parallel for schedule(static,2)
    for(int i=0;i<n;i++) {
        #pragma omp critical
        {
            c = a+b;
            a = b;
            b = c;
        }
    }
    return a;
}
void main() {
    int n = 20;
    double start = omp_get_wtime();
    #pragma omp parallel for
    for(int i=0;i<n;i++) {
        int t = omp_get_thread_num();
        printf("Thread: %d fib(%d) = %d\n",t,i,fib(i));
    }
    double end = omp_get_wtime();
    printf("Time Taken is : %f\n",end-start);
}