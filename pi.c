#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<math.h>

void main() {
    float pi=0;

    float thread[4];
   #pragma omp parallel for num_threads(4)
    for(int i=0;i<1000000;i++) {
        int t= omp_get_thread_num();
        thread[t] += pow(-1,i)/(2*i+1);
      //  pi+=pow(-1,i)/(2*i+1);
    }
    for(int i=0;i<4;i++) {
        pi += thread[i];
    }
    pi*=4;

    printf("%f",pi);
}