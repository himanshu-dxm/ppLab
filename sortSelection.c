#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>

void main() {
    int n=100;
    int a[100];

    srand ( time(NULL) );
    for(int i=0;i<n;i++) {
        a[i]=rand()%100+1;
    }

    printf("\nBefore Sorting\n");
    for(int i=0;i<n;i++) {
        printf("%d ",a[i]);
    }

    // Do not put pragma here cz we need the same 
    // a[i] value for all the thread operating
    // we can parallelize only inner one
    double start,end;
    start = omp_get_wtime();
	for(int i=0;i<n-1;i++) 
	{
        #pragma omp parallel for
		for(int j=i+1;j<n;j++){
            if(a[i]>a[j]) {
                int t=a[i];
                a[i]=a[j];
                a[j]=t;
            }			
		}
	}
    end = omp_get_wtime();
    printf("\n\nTime taken:%f\n",(end-start) );

    printf("\nAfter Sorting\n");
    for(int i=0;i<n;i++) {
        printf("%d ",a[i]);
    }
}