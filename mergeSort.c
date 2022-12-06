#include<stdio.h>
#include<omp.h>
#include<stdlib.h>
#include<time.h>

void merge(int arr[],int l,int m,int h) {
    
    int i,j,k;
    int n1=m-l+1;
    int n2=h-m;

    int L[n1],R[n2];

    for(i=0;i<n1;i++) {
        L[i]=arr[l+i];
    }
    for(i=0;i<n2;i++) {
        R[i]=arr[m+1+i];
    }
    i=0,j=0,k=l;
    while(i<n1 && j<n2) {
        if(L[i]<R[j]) {
            arr[k++]=L[i++];
        } else {
            arr[k++]=R[j++];
        }
    }
    while(i<n1) {
        arr[k++]=L[i++];
    }
    while(j<n2) {
        arr[k++]=R[j++];
    }
}
void mergeSort(int a[],int l,int h) {
    if(l<h) {
        int mid = l + (h-l)/2;
        
        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSort(a,l,mid);

            #pragma omp section
            mergeSort(a,mid+1,h);
        }
        merge(a,l,mid,h);
    }
}

void main() {
    int n=10;
    int a[10],i;
    // this is for taking different random values on each execution
    srand ( time(NULL) );
    
    printf("\nBefore Sorting\n");
    for(int i=0;i<n;i++) {
        a[i]=rand()%100+1;
        printf("%d ",a[i]);
    }
    double start=omp_get_wtime();

    mergeSort(a,0,n-1);
    
    double end=omp_get_wtime();

    printf("\n\nTime taken:%f\n",(end-start) );

    printf("\nAfter Sorting\n");
    for(int i=0;i<n;i++) {
        printf("%d ",a[i]);
    }
}