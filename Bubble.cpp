#include<iostream>
#include<stdlib.h>
#include<omp.h>
using namespace std;

void bubble(int *, int);
void swap(int &, int &);

void bubble(int *a, int n)
{
	omp_set_num_threads(4);
	for(  int i = 0;  i < n;  i++ )
     	{  	 
   	 	int first = i % 2; 	 
//It determines whether the inner loop starts at index 0 or 1, effectively dividing the array into two 
halves to be sorted concurrently.		

   	 	#pragma omp parallel for shared(a,first)
		//This ensures that each thread has access to the array and the 
		current value of first.

   	 	for(  int j = first;  j < n-1;  j += 2  )
   	   	{  	 
   			if(  a[ j ]  >  a[ j+1 ]  )
   		  	{  	 
     			 	swap(  a[ j ],  a[ j+1 ]  );
   		  	}  	 
   		}  	 
	}
}


void swap(int &a, int &b)
{
	int test;
    	test=a;
    	a=b;
    	b=test;
}

int main()
{
	/*
	int *a,n;
    	cout<<"\n enter total no of elements=>";
    	cin>>n;
    	a=new int[n];
    	cout<<"\n enter elements=>";
    	for(int i=0;i<n;i++)
    	{
   	 	cin>>a[i];
    	}
	*/
	
	int SIZE =500;
	int i,j;
    	int a[SIZE];
    
    	for(i=0;i<SIZE;i++)
    	{
        		a[i]=rand()%SIZE;
    	}
    
    	int n = SIZE;
    	double start,end;
    	start=omp_get_wtime();    
    	bubble(a,n);
	end=omp_get_wtime();
    
    	cout<<"\n sorted array is=>";
    	for(int i=0;i<n;i++)
    	{
   	 	cout<<a[i]<<”  ”;	
    	}

	printf("\n-------------------------\n Time Parallel= %f",(end-start));

	return 0;
}
